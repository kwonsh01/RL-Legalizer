#include "RLDP.h"
#include <string>
#include <vector>

using namespace RL_LEGALIZER;

int Instance::get_x_coord(){
  if(!cell->x_coord)
    return cell->init_x_coord;
  else
    return cell->x_coord;
}

int Instance::get_y_coord(){
  if(!cell->y_coord)
    return cell->init_y_coord;
  else
    return cell->y_coord;
}

double Instance::get_width(){
  return cell->width;
}

bool Instance::get_moveTry(){
  return this->moveTry;
}