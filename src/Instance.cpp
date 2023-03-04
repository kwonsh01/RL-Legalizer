#include "RLDP.h"

using namespace RL_LEGALIZER;

double Instance::get_width(){
  return cell->width;
}

bool Instance::get_moveTry(){
  return this->moveTry;
}

double Instance::get_GcellXcoord(int Gcell_grid, float rx){
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

double Instance::get_GcellYcoord(int Gcell_grid, float ty){
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