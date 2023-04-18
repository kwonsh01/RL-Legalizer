#include "RLDP.h"
#include <string>
#include <vector>
#include <random>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_polygon.hpp>

using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;

using namespace opendp;
using namespace RL_LEGALIZER;

bool Gcell_density_order(truffle &a, truffle &b) {
  if(a.Gcell_density > b.Gcell_density)
    return true;
  else
    return false;
}

RLDP::RLDP() : placed_cell(0), placed_Gcell(0), placement_fail(false), total_cell(0), Gcell_grid(1), opendp::circuit() {}

void RLDP::read_files(string argv, int Gcell_grid_num) {
  Gcell_grid = Gcell_grid_num;
  vector<string> lefStor;
  string defLoc = "";
  std::stringstream str(argv);
  str.str(argv);
  string temp;

  string cpu, constraints, size;
  string out_def = "output";

  if(argv.size() < 1) {
    print_usage();
    exit(1);
  }

  while(str >> temp){
    if(temp == "-lef"){
      str >> temp;
      lefStor.push_back( temp );
    }
    else if(temp == "-def"){
      str >> temp;
      defLoc = temp;
    }
    else if(temp == "-cpu"){
      str >> temp;
      cpu = temp.c_str();
    }
    else if(temp == "-placement_constraints"){
      str >> temp;
      constraints = temp.c_str();
    }
    else if(temp == "-output_def"){
      str >> temp;
      out_def = temp.c_str();
    }
    else if(temp == "-group_ignore"){
      GROUP_IGNORE = true;
    }
  }

  if(lefStor.size() == 0 || defLoc == "") {
    print_usage();
    exit(1);
  }

  string tech_str, cell_lef_str, lef_str;
  string constraints_str;

  // Below should be modified!!
  /*
  if( lefStor.size() == 1 ) {
    read_lef(lefStor[0]);
  }
  else {
    read_tech_lef(lefStor[0]);
    read_cell_lef(lefStor[1]);
  }
  */

  ReadLef(lefStor);

  if(constraints.size()) constraints_str = constraints;

  in_def_name = defLoc;
  size_t def_found = defLoc.find_last_of("/\\");
  string dir_bench = defLoc.substr(0, def_found);
  string dir = dir_bench.substr(0, dir_bench.find_last_of("/\\"));
  string bench = dir_bench.substr(dir_bench.find_last_of("/\\") + 1);
  benchmark = bench;

  if(!out_def.size())
    out_def_name = "./" + bench + "_lg.def";
  else
    out_def_name = out_def;

  cout << endl;
  cout << "-------------------- INPUT FILES ----------------------------------"
       << endl;
  cout << " benchmark name    : " << bench << endl;
  cout << " directory         : " << dir << endl;

  for(auto& curLefLoc : lefStor) {
    cout << " lef               : " << curLefLoc << endl;
  }
  cout << " def               : " << defLoc << endl;

  if(constraints.size())
    cout << " constraints       : " << constraints_str << endl;
  cout << "-------------------------------------------------------------------"
       << endl;

//  read_def shuld after read_lef
//  read_def(defLoc, INIT);

  ReadDef(defLoc );
//  exit(1);

  if(size.size()) {
    string size_file = size;
    read_def_size(size_file);
  }
  power_mapping();

  if(constraints.size()) read_constraints(constraints_str);

  // summary of benchmark
  calc_design_area_stats();

  // dummy cell generation
  dummy_cell.name = "FIXED_DUMMY";
  dummy_cell.isFixed = true;
  dummy_cell.isPlaced = true;

  // calc row / site offset
  int row_offset = rows[0].origY;
  int site_offset = rows[0].origX;

  // construct pixel grid
  int row_num = ty / rowHeight;
  int col = rx / wsite;
  grid = new pixel*[row_num];
  for(int i = 0; i < row_num; i++) {
    grid[i] = new pixel[col];
  }

  for(int i = 0; i < row_num; i++) {
    for(int j = 0; j < col; j++) {
      grid[i][j].name = "pixel_" + to_string(i) + "_" + to_string(j);
      grid[i][j].y_pos = i;
      grid[i][j].x_pos = j;
      grid[i][j].linked_cell = NULL;
      grid[i][j].isValid = false;
    }
  }

  // Fragmented Row Handling
  for(auto& curFragRow : prevrows) {
    int x_start = IntConvert((1.0*curFragRow.origX - core.xLL) / wsite);
    int y_start = IntConvert((1.0*curFragRow.origY - core.yLL) / rowHeight);

    int x_end = x_start + curFragRow.numSites;
    int y_end = y_start + 1;

//    cout << "x_start: " << x_start << endl;
//    cout << "y_start: " << y_start << endl;
//    cout << "x_end: " << x_end << endl;
//    cout << "y_end: " << y_end << endl;
    for(int i=x_start; i<x_end; i++) {
      for(int j=y_start; j<y_end; j++) {
        grid[j][i].isValid = true;
      }
    }
  }

  /*
  for(int i = 0; i < rows.size(); i++) {
    // original rows : Fragmented ROWS
    row* myRow = &rows[i];

    int col_size = myRow->numSites;
    for(int j = 0; j < col_size; j++) {
      int y_pos = (myRow->origY-core.yLL) / rowHeight;
      int x_pos = j + (myRow->origX-core.xLL) / wsite;
      grid[y_pos][x_pos].isValid = true;
    }
  }
  */

  // fixed cell marking
  fixed_cell_assign();
  // group id mapping & x_axis dummycell insertion
  group_pixel_assign_2();
  // y axis dummycell insertion
  group_pixel_assign();

  init_large_cell_stor();
  return;
}

void RLDP::copy_data(const RLDP& copied) {
  rowHeight = copied.rowHeight;
  rx = copied.rx;
  ty = copied.ty;
  core = copied.core;
  wsite = copied.wsite;

  cells = copied.cells;

  prevrows = copied.prevrows;

  int row_num = this->ty / this->rowHeight;
  int col = this->rx / this->wsite;

  for(int i = 0; i < row_num; i++) {
    for(int j = 0; j < col; j++) {
      this->grid[i][j].name = copied.grid[i][j].name;
      this->grid[i][j].y_pos = copied.grid[i][j].y_pos;
      this->grid[i][j].x_pos = copied.grid[i][j].x_pos;
      this->grid[i][j].linked_cell = copied.grid[i][j].linked_cell;
      this->grid[i][j].isValid = copied.grid[i][j].isValid;
    }
  }

  for(Instance& theCell : cell_list){
    theCell.moveTry = false;
  }

}

void RLDP::copy_allocate(double ty, double rowHeight, double rx, int wsite) {
  this->ty = ty;
  this->rowHeight = rowHeight;
  this->rx = rx;
  this->wsite = wsite;

  int row_num = this->ty / this->rowHeight;
  int col = this->rx / this->wsite;

  this->grid = new pixel*[row_num];
  for(int i = 0; i < row_num; i++) {
    this->grid[i] = new pixel[col];
  }
}

void RLDP::copy_delete() {
  int row_num = this->ty / this->rowHeight;

  for(int i = 0; i < row_num; i++) {
    delete[] this->grid[i];
  }
  delete[] this->grid;
}

void RLDP::Cell_init() {
  int x, y, gcell_id;
  int row = int(this->ty) / Gcell_grid;
  int col = int(this->rx) / Gcell_grid;

  total_cell = 0;

  for(int i = 0; i < cells.size(); i++) {
    if(cells[i].isFixed || cells[i].inGroup || cells[i].isPlaced){
      gcell_id = -1;
    }
    else{
      x = cells[i].init_x_coord / col;
      y = cells[i].init_y_coord / row;
      gcell_id = x + y * Gcell_grid;
      total_cell++;
    }
    cell_list.emplace_back(&(cells[i]), gcell_id);
  }
}

void RLDP::net_assign_to_cell() {
  for(int i = 0; i < nets.size(); i++) {
    net* theNet = &nets[i];
    pin* source = &pins[theNet->source];

    // cout << "net number: "<< i << endl << source->owner << endl;
    if(source->owner >= 0 && source->owner < cell_list.size()){
      cell_list[source->owner].cell_nets.push_back(theNet);
    }

    for(int j = 0; j < theNet->sinks.size(); j++) {
      pin* sink = &pins[theNet->sinks[j]];
      // cout << "net sink number: "<< j << endl << sink->owner << endl;
      if(sink->owner >= 0 && sink->owner < cell_list.size()){
        cell_list[sink->owner].cell_nets.push_back(theNet);
      }
    }
  }
}

vector< vector<Instance*> >& RLDP::get_Cell() {
  this->Cell_init();
  this->net_assign_to_cell();

  for(int i = 0; i < Gcell_grid * Gcell_grid; i++){
    vector<Instance*> temp;
    Gcell_cell_list.push_back(temp);
  }

  for(Instance& instance : cell_list) {
    if(instance.cell->isFixed || instance.cell->inGroup || instance.cell->isPlaced) continue;
    Gcell_cell_list[instance.Gcell_id].push_back(&instance);
  }

  return Gcell_cell_list;
}

void RLDP::Gcell_init() {
  int gcell_id = 0;

  for(std::vector<Instance*>& instance_vector : Gcell_cell_list){
    Gcell_density.emplace_back(gcell_id++, instance_vector.size(), 0);
  }

}

std::vector<truffle> RLDP::get_Gcell() {
  Gcell_init();

  int row = int(this->ty) / Gcell_grid;
  int col = int(this->rx) / Gcell_grid;

  int *cell_density = new int[Gcell_grid * Gcell_grid];
  int *macro_density = new int[Gcell_grid * Gcell_grid];

  boost::polygon::rectangle_data<int> gcell_rect;
  boost::polygon::rectangle_data<int> macro_rect;
  boost::polygon::rectangle_data<int> ovl;

  for(int i = 0; i < Gcell_grid * Gcell_grid; i++){
    cell_density[i] = 0;
    macro_density[i] = 0;
  }

  //density by macros
  for(int i = 0; i < Gcell_grid; i++){
    for(int j = 0; j < Gcell_grid; j++){
      gcell_rect = boost::polygon::construct<boost::polygon::rectangle_data<int>>(j * col, i * row, (j + 1) * col, (i + 1) * row);
      for(macro instance : macros){
        macro_rect = boost::polygon::construct<boost::polygon::rectangle_data<int>>(instance.xOrig, instance.yOrig, instance.xOrig + instance.width, instance.yOrig + instance.height);
        if(boost::geometry::overlaps(gcell_rect, macro_rect)){
          ovl = boost::polygon::construct<boost::polygon::rectangle_data<int>>
              (std::max(double(j * col), instance.xOrig), std::max(double(i * row), instance.yOrig), std::min(double((j + 1) * col), instance.xOrig + instance.width), std::min(double((i + 1) * row), instance.yOrig + instance.height));
          macro_density[i * Gcell_grid + j] += boost::geometry::area(ovl);
        }
      }
    }
  }

  //density by cells
  for(int i = 0; i < Gcell_grid * Gcell_grid; i++){
    for(Instance *Instance : Gcell_cell_list[i]){
      if(Instance->Gcell_id == i){
        cell_density[i] += int(Instance->cell->height) * int(Instance->cell->width);
      }
    }
  }

  for(int i = 0; i < Gcell_grid * Gcell_grid; i++){
    Gcell_density[i].Gcell_density = (macro_density[i] + cell_density[i])/1000;
  }

  delete[] cell_density;
  delete[] macro_density;

  sort(Gcell_density.begin(), Gcell_density.end(), Gcell_density_order);
  return Gcell_density;
}

void RLDP::pre_placement() {
  if(groups.size() > 0) {
    // group_cell -> region assign
    group_cell_region_assign();
//    cout << " group_cell_region_assign done .." << endl;
  }
  // non group cell -> sub region gen & assign
  non_group_cell_region_assign();
//  cout << " non_group_cell_region_assign done .." << endl;
//  cout << " - - - - - - - - - - - - - - - - - - - - - - - - " << endl;

  // pre placement out border ( Need region assign function previously )
  if(groups.size() > 0) {
    group_cell_pre_placement();
//    cout << " group_cell_pre_placement done .." << endl;
    non_group_cell_pre_placement();
//    cout << " non_group_cell_pre_placement done .." << endl;
//    cout << " - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
  }

  // naive method placement ( Multi -> single )
  if(groups.size() > 0) {
    group_cell_placement("init_coord");
    cout << " group_cell_placement done .. " << endl;
    for(int i = 0; i < groups.size(); i++) {
      group* theGroup = &groups[i];
      for(int j = 0; j < 3; j++) {
        int count_a = group_refine(theGroup);
        int count_b = group_annealing(theGroup);
        if(count_a < 10 || count_b < 100) break;
      }
    }
  }
}

bool RLDP::place_oneCell(int gcell_id, int cell_idx) {
  bool success = true;
  Instance *theinstance = Gcell_cell_list[gcell_id][cell_idx];
  cell* thecell = Gcell_cell_list[gcell_id][cell_idx]->cell;

  if(!theinstance->moveTry){
    placed_cell++;
    placed_Gcell++;
    theinstance->moveTry = true;
  }

  if(!thecell->isPlaced){
    if(!map_move(thecell, "init_coord")) {
      if(!shift_move(thecell, "init_coord")) {
        success = false;
        cout << thecell->name << " -> move failed!" << endl;
      }
    }
  }
  thecell->disp = abs(thecell->init_x_coord - thecell->x_coord) + abs(thecell->init_y_coord - thecell->y_coord);
  cout << Gcell_cell_list[gcell_id][cell_idx]->cell->id << "'s cell_placement done .. " << endl;
  // cout << " - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
  return success;
}

void RLDP::place_oneCell(int cell_idx) {
  cell* thecell = &this->cells[cell_idx];

  if(!thecell->isPlaced){
    if(!map_move(thecell, "init_coord")) {
      if(!shift_move(thecell, "init_coord")) {
        cout << thecell->name << " -> move failed!" << endl;
      }
    }
    thecell->disp = abs(thecell->init_x_coord - thecell->x_coord) + abs(thecell->init_y_coord - thecell->y_coord);
  }

}

double RLDP::calc_HPWL() {
  double hpwl = 0;

  double x_coord = 0;
  double y_coord = 0;

  for(int i = 0; i < nets.size(); i++) {
    rect box;
    net* theNet = &nets[i];
    // cout << " net name : " << theNet->name << endl;
    pin* source = &pins[theNet->source];

    if(source->type == NONPIO_PIN) {
      cell* theCell = &cells[source->owner];
      if(!theCell->isPlaced) {
        x_coord = theCell->init_x_coord;
        y_coord = theCell->init_y_coord;
      }
      else {
        x_coord = theCell->x_coord;
        y_coord = theCell->y_coord;
      }
      box.xLL = box.xUR = x_coord + source->x_offset * DEFdist2Microns;
      box.yLL = box.yUR = y_coord + source->y_offset * DEFdist2Microns;
    }
    else {
      box.xLL = box.xUR = source->x_coord;
      box.yLL = box.yUR = source->y_coord;
    }

    for(int j = 0; j < theNet->sinks.size(); j++) {
      pin* sink = &pins[theNet->sinks[j]];
      // cout << " sink name : " << sink->name << endl;
      if(sink->type == NONPIO_PIN) {
        cell* theCell = &cells[sink->owner];
        // if(!theCell->moveTry) {
        if(!theCell->isPlaced) {
          x_coord = theCell->init_x_coord;
          y_coord = theCell->init_y_coord;
        }
        else {
          x_coord = theCell->x_coord;
          y_coord = theCell->y_coord;
        }
        box.xLL = std::min(box.xLL, x_coord + sink->x_offset * DEFdist2Microns);
        box.xUR = std::max(box.xUR, x_coord + sink->x_offset * DEFdist2Microns);
        box.yLL = std::min(box.yLL, y_coord + sink->y_offset * DEFdist2Microns);
        box.yUR = std::max(box.yUR, y_coord + sink->y_offset * DEFdist2Microns);
      }
      else {
        box.xLL = std::min(box.xLL, sink->x_coord);
        box.xUR = std::max(box.xUR, sink->x_coord);
        box.yLL = std::min(box.yLL, sink->y_coord);
        box.yUR = std::max(box.yUR, sink->y_coord);
      }
    }

    double box_boundary = (box.xUR - box.xLL + box.yUR - box.yLL);

    hpwl += box_boundary;
  }
  return hpwl / static_cast< double >(DEFdist2Microns);
}

double RLDP::calc_HPWL(int gcell_id, int cell_idx) {
  double hpwl = 0;

  double x_coord = 0;
  double y_coord = 0;

  std::vector<net*>& theNet_lst = Gcell_cell_list[gcell_id][cell_idx]->cell_nets;

  for(int i = 0; i < theNet_lst.size(); i++) {
    rect box;
    net* theNet = theNet_lst[i];
    // cout << " net name : " << theNet->name << endl;
    pin* source = &pins[theNet->source];

    if(source->type == NONPIO_PIN) {
      cell* theCell = &cells[source->owner];
      if(!theCell->isPlaced) {
        x_coord = theCell->init_x_coord;
        y_coord = theCell->init_y_coord;
      }
      else {
        x_coord = theCell->x_coord;
        y_coord = theCell->y_coord;
      }
      box.xLL = box.xUR = x_coord + source->x_offset * DEFdist2Microns;
      box.yLL = box.yUR = y_coord + source->y_offset * DEFdist2Microns;
    }
    else {
      box.xLL = box.xUR = source->x_coord;
      box.yLL = box.yUR = source->y_coord;
    }

    for(int j = 0; j < theNet->sinks.size(); j++) {
      pin* sink = &pins[theNet->sinks[j]];
      // cout << " sink name : " << sink->name << endl;
      if(sink->type == NONPIO_PIN) {
        cell* theCell = &cells[sink->owner];
        // if(!theCell->moveTry) {
        if(!theCell->isPlaced) {
          x_coord = theCell->init_x_coord;
          y_coord = theCell->init_y_coord;
        }
        else {
          x_coord = theCell->x_coord;
          y_coord = theCell->y_coord;
        }
        box.xLL = std::min(box.xLL, x_coord + sink->x_offset * DEFdist2Microns);
        box.xUR = std::max(box.xUR, x_coord + sink->x_offset * DEFdist2Microns);
        box.yLL = std::min(box.yLL, y_coord + sink->y_offset * DEFdist2Microns);
        box.yUR = std::max(box.yUR, y_coord + sink->y_offset * DEFdist2Microns);
      }
      else {
        box.xLL = std::min(box.xLL, sink->x_coord);
        box.xUR = std::max(box.xUR, sink->x_coord);
        box.yLL = std::min(box.yLL, sink->y_coord);
        box.yUR = std::max(box.yUR, sink->y_coord);
      }
    }

    double box_boundary = (box.xUR - box.xLL + box.yUR - box.yLL);

    hpwl += box_boundary;
  }
  return hpwl / static_cast< double >(DEFdist2Microns);
}

double RLDP::calc_avg_disp() {
  double avg_disp = 0;
  int count_displacement = 0;

  for(std::vector<Instance*> theCells : Gcell_cell_list){
    for(Instance *theCell : theCells){
      if(theCell->cell->isPlaced){
        avg_disp += theCell->cell->disp;
        count_displacement++;
      }
    }
  }

  avg_disp /= count_displacement;

  return avg_disp;
}

bool RLDP::calc_done() {
  if(total_cell == placed_cell){
    placed_cell = 0;
    return true;
  }
  return false;
}

bool RLDP::calc_Gcell_done(int runtime_gcell) {
  if(Gcell_density[runtime_gcell].stdcell_num == placed_Gcell){
    placed_Gcell = 0;
    return true;
  }
  return false;
}

void RLDP::SA(const RLDP& copied, std::vector<int> action_list, int Iter) {
  int i, j;
  double temp_rand = 1.0;
  double before_hpwl = 0.0, after_hpwl = 0.0;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> prob_int(0, total_cell - 1);
  std::uniform_real_distribution<double> prob_double(0.0, 1.0);

  before_hpwl = this->calc_HPWL();
  after_hpwl = before_hpwl;

  for(int iter = 0; iter < Iter; iter++){
    cout << "Iter: " << iter << endl;
    cout << " HPWL: " << after_hpwl << endl;

    before_hpwl = after_hpwl;

    this->copy_data(copied);

    i = prob_int(gen);
    j = prob_int(gen);

    int temp = action_list[i];
    action_list[i] = action_list[j];
    action_list[j] = temp;

    for(int a : action_list){
      this->place_oneCell(a);
    }

    after_hpwl = this->calc_HPWL();

    if (after_hpwl > before_hpwl) {
      double delta = 500 * (after_hpwl-before_hpwl) / before_hpwl;

      if(prob_double(gen) < exp(-delta/temp_rand)) continue;
      else{
        temp = action_list[i];
        action_list[i] = action_list[j];
        action_list[j] = temp;
        after_hpwl = before_hpwl;
      }
    }

    if(temp_rand > 0.01)
      temp_rand -= 0.01;
  }
  this->calc_density_factor(4);
  this->evaluation();
  this->check_legality();
}