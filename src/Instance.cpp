#include "RLDP.h"

using namespace RL_LEGALIZER;

bool Instance::get_moveTry(){
  return this->moveTry;
}

int Instance::get_Net_num(){
  return this->cell_nets.size();
}

double Instance::get_Height(double rH){
  return this->cell->height / rH;
}

double Instance::get_Width(double rH){
  return this->cell->width / rH;
}

double Instance::get_Xcoord(double rx){
  return this->moveTry ? this->cell->x_coord / rx : this->cell->init_x_coord / rx;
}

double Instance::get_Ycoord(double ty){
  return this->moveTry ? this->cell->y_coord / ty : this->cell->init_y_coord / ty;
}

double Instance::get_GcellXcoord(int Gcell_grid, double rx){
  int x_pre;
  int col;
  int shamt_x;
  int x_new;

  if(this->moveTry){
    x_pre = this->cell->x_coord;
  }
  else{
    x_pre = this->cell->init_x_coord;
  }

  col = rx / Gcell_grid;

  shamt_x = Gcell_id % Gcell_grid;

  x_new = x_pre - shamt_x * col;

  return double(x_new) / col;
}

double Instance::get_GcellYcoord(int Gcell_grid, double ty){
  int y_pre;
  int row;
  int shamt_y;
  int y_new;

  if(this->moveTry){
    y_pre = this->cell->y_coord;
  }
  else{
    y_pre = this->cell->init_y_coord;
  }

  row = ty / Gcell_grid;

  shamt_y = Gcell_id / Gcell_grid;

  y_new = y_pre - shamt_y * row;

  return double(y_new) / row;
}

int Instance::get_Nearcell_num(RLDP& ckt){
  int num = 0;
  int x = this->moveTry ? this->cell->x_coord : this->cell->init_x_coord;
  int y = this->moveTry ? this->cell->y_coord : this->cell->init_y_coord;

  rect theRect;
  theRect.xLL = std::max(ckt.die.xLL, x - this->cell->width * 2);
  theRect.xUR = std::min(ckt.die.xUR, x + this->cell->width * 2);
  theRect.yLL = std::max(ckt.die.yLL, y - this->cell->height * 2);
  theRect.yUR = std::min(ckt.die.yUR, y + this->cell->height * 2);

  int x_start = (int)floor(theRect.xLL / ckt.wsite + 0.5);
  int y_start = (int)floor(theRect.yLL / ckt.rowHeight + 0.5);
  int x_end = (int)floor(theRect.xUR / ckt.wsite + 0.5);
  int y_end = (int)floor(theRect.yUR / ckt.rowHeight + 0.5);

  Instance*** mark_grid = ckt.get_mark_grid();
  for(int i = y_start; i < y_end; i++){
    for(int j = x_start; j < x_end; j++){
      if(mark_grid[i][j]){
        num++;
      }
    }
  }

  return num;
}