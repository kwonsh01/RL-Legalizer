#ifndef RL_LEGALIZER_INCLUDE_RLDP_H_
#define RL_LEGALIZER_INCLUDE_RLDP_H_

#include "circuit.h"
#include <iostream>
#include <string>

using namespace opendp;

namespace RL_LEGALIZER{

  struct truffle{
    int gcell_id;
    int stdcell_num;
    int gcell_density;
    truffle() : gcell_id(-1), stdcell_num(0), gcell_density(0) {}
    truffle(int x, int y, int z) : gcell_id(x), stdcell_num(y), gcell_density(z) {}
  };

  struct Instance {
    opendp::cell *cell;
    bool moveTry;
    int gcell_id;

    int get_x_coord(){
      if(!cell->x_coord)
        return cell->init_x_coord;
      else
        return cell->x_coord;
    }
    int get_y_coord(){
      if(!cell->y_coord)
        return cell->init_y_coord;
      else
        return cell->y_coord;
    }
    double get_width(){
      return cell->width;
    }
    bool get_moveTry(){
      return this->moveTry;
    }
    double getGcellXcoord(int Gcell_grid, int rx){
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

      shamt_x = gcell_id % Gcell_grid;

      x_new = x_pre - shamt_x * col;

      return double(x_new) / col;
    }
    double getGcellYcoord(int Gcell_grid, int ty){
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

      shamt_y = gcell_id / Gcell_grid;

      y_new = y_pre - shamt_y * row;

      return double(y_new) / row;
    }
    
    instance() : cell(nullptr), moveTry(false), gcell_id(-1) {};
    instance(opendp::cell *cell, int gcell_id) : cell(cell), moveTry(false), gcell_id(gcell_id) {};
  };

  class RLDP : public opendp::circuit {
   private:
    int placed_cell;
    int placed_Gcell;
    bool placement_fail;
    int total_cell;
    int Gcell_grid;
    std::vector<truffle> Gcell_density;
    std::vector< std::vector<Instance> > cell_list_isnotFixed;
   public:
    RLDP();
    ~RLDP() = default;
    void read_files(std::string argv, int Gcell_grid_num);
    void copy_data(const circuit& copied);

    std::vector< std::vector<Instance> >& get_Cell();
    void Gcell_init();
    std::vector<truffle> get_Gcell();

    void pre_placement();
    void place_oneCell(int runtime_gcell, int cell_idx);

    double reward_calc();
    double reward_calc_Gcell(int gcell_id);
    double calc_HPWL();
    double calc_avg_disp();

    int get_Gcell_grid(){return this->Gcell_grid * this->Gcell_grid;}
    int total_cell_num(){return this->total_cell;}
    double get_die_rx(){return this->rx;}
    double get_die_ty(){return this->ty;}
    double get_die_rH(){return this->rowHeight;}

    bool calc_done();
    bool calc_Gcell_done(int runtime_gcell);
  };
}

#endif