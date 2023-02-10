#include "RLDP.h"
#include <string>
#include <vector>

using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;

using namespace opendp;
using namespace RL_LEGALIZER;

void circuit::read_files(std::string argv, int Gcell_grid_num) {
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

  // read_def shuld after read_lef
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

void RLDP::copy_data(const circuit& copied){
  // *this = copied;//need to fix, except to copy cell_list_isnotFixed

  GROUP_IGNORE = copied.GROUP_IGNORE;

  macro2id = copied.macro2id;
  cell2id = copied.cell2id;
  pin2id = copied.pin2id;
  net2id = copied.net2id;
  row2id = copied.row2id;
  site2id = copied.site2id;
  layer2id = copied.layer2id;

  via2id = copied.via2id;
  edge_spacing = copied.edge_spacing;

  group2id = copied.group2id;

  design_util = copied.design_util;
  sum_displacement = copied.sum_displacement;

  num_fixed_nodes = copied.num_fixed_nodes;
  total_mArea = copied.total_mArea;
  total_fArea = copied.total_fArea;
  designArea = copied.designArea;
  rowHeight = copied.rowHeight;
  lx = copied.lx;
  rx = copied.rx;
  by = copied.by;
  ty = copied.ty;
  die = copied.die;
  core = copied.core;

  minVddCoordiY = copied.minVddCoordiY;
  initial_power = copied.initial_power;

  max_utilization = copied.max_utilization;
  displacement = copied.displacement;
  max_disp_const = copied.max_disp_const;
  wsite = copied.wsite;
  max_cell_height = copied.max_cell_height;
  num_cpu = copied.num_cpu;

  out_def_name = copied.out_def_name;
  in_def_name = copied.in_def_name;

  benchmark = copied.benchmark;

  grid = copied.grid;
  dummy_cell = copied.dummy_cell;
  sub_regions = copied.sub_regions;
  tracks = copied.tracks;

  LEFVersion = copied.LEFVersion;
  LEFNamesCaseSensitive = copied.LEFNamesCaseSensitive;
  LEFDelimiter = copied.LEFDelimiter;
  LEFBusCharacters = copied.LEFBusCharacters;
  LEFManufacturingGrid = copied.LEFManufacturingGrid;

  MAXVIASTACK = copied.MAXVIASTACK;
  minLayer = copied.minLayer;
  maxLayer = copied.maxLayer;

  DEFVersion = copied.DEFVersion;
  DEFDelimiter = copied.DEFDelimiter;
  DEFBusCharacters = copied.DEFBusCharacters;
  design_name = copied.design_name;
  DEFdist2Microns = copied.DEFdist2Microns;
  dieArea = copied.dieArea;

  sites = copied.sites;
  layers = copied.layers;
  macros = copied.macros;
  cells = copied.cells;
  nets = copied.nets;
  pins = copied.pins;

  prevrows = copied.prevrows;
  rows = copied.rows;

  vias = copied.vias;
  viaRules = copied.viaRules;
  groups = copied.groups;

  large_cell_stor = copied.large_cell_stor;

  //cell_list_isnotFixed;

  int row_num = this->ty / this->rowHeight;
  int col = this->rx / this->wsite;
  /*
  grid = NULL;
  grid = new pixel*[row_num];
  for(int i = 0; i < row_num; i++) {
    grid[i] = new pixel[col];
  }
  */
  for(int i = 0; i < row_num; i++) {
    for(int j = 0; j < col; j++) {
      this->grid[i][j].name = "pixel_" + to_string(i) + "_" + to_string(j);
      this->grid[i][j].y_pos = i;
      this->grid[i][j].x_pos = j;
      this->grid[i][j].linked_cell = NULL;
      this->grid[i][j].isValid = false;
    }
  }
  for(auto& curFragRow : prevrows) {
    int x_start = IntConvert((1.0*curFragRow.origX - core.xLL) / wsite);
    int y_start = IntConvert((1.0*curFragRow.origY - core.yLL) / rowHeight);

    int x_end = x_start + curFragRow.numSites;
    int y_end = y_start + 1;

    for(int i=x_start; i<x_end; i++) {
      for(int j=y_start; j<y_end; j++) {
        grid[j][i].isValid = true;
      }
    }
  }

  fixed_cell_assign();
  group_pixel_assign_2();
  group_pixel_assign();
  init_large_cell_stor();
}
