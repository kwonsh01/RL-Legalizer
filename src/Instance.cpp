#include "RLDP.h"

using namespace RL_LEGALIZER;

bool Instance::get_moveTry(){
  return this->moveTry;
}

int Instance::get_Netsize(){
  return cell_nets.size();
}

double Instance::get_Height(double rH){
  return cell->height / rH;
}

double Instance::get_Width(double rH){
  return cell->width / rH;
}

double Instance::get_Xcoord(double rx){
  return cell->isPlaced ? this->cell->x_coord / rx : this->cell->init_x_coord / rx;
}

double Instance::get_Ycoord(double ty){
  return cell->isPlaced ? this->cell->y_coord / ty : this->cell->init_y_coord / ty;
}

double Instance::get_GcellXcoord(int Gcell_grid, double rx){
  int x_pre;
  int col;
  int shamt_x;
  int x_new;

  if(cell->isPlaced){
    x_pre = cell->x_coord;
  }
  else{
    x_pre = cell->init_x_coord;
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

  if(cell->isPlaced){
    y_pre = cell->y_coord;
  }
  else{
    y_pre = cell->init_y_coord;
  }

  row = ty / Gcell_grid;

  shamt_y = Gcell_id / Gcell_grid;

  y_new = y_pre - shamt_y * row;

  return double(y_new) / row;
}