#ifndef RL_LEGALIZER_INCLUDE_RLDP_H_
#define RL_LEGALIZER_INCLUDE_RLDP_H_

#include "circuit.h"
#include <iostream>
#include <string>

using namespace opendp;

namespace RL_LEGALIZER{

  struct truffle{
    int Gcell_id;
    int stdcell_num;
    int Gcell_density;
    truffle() : Gcell_id(-1), stdcell_num(0), Gcell_density(0) {}
    truffle(int x, int y, int z) : Gcell_id(x), stdcell_num(y), Gcell_density(z) {}
  };

  struct Instance {
    opendp::cell *cell;
    bool moveTry;
    int Gcell_id;
    std::vector<opendp::net*> cell_nets;

    double get_width();
    bool get_moveTry();
    double get_GcellXcoord(int Gcell_grid, float rx);
    double get_GcellYcoord(int Gcell_grid, float ty);

    Instance() : cell(nullptr), moveTry(false), Gcell_id(-1) {};
    Instance(opendp::cell *cell, int Gcell_id) : cell(cell), moveTry(false), Gcell_id(Gcell_id) {};
  };

  class RLDP : public opendp::circuit {
   private:
    int placed_cell;
    int placed_Gcell;
    bool placement_fail;
    int total_cell;
    int Gcell_grid;
    std::vector<truffle> Gcell_density;
    std::vector< Instance > cell_list;
    std::vector< std::vector<Instance*> > Gcell_cell_list;
   public:
    RLDP();
    ~RLDP() = default;
    void read_files(std::string argv, int Gcell_grid_num);
    void copy_data(const RLDP& copied);
    void copy_allocate(double ty, double rowHeight, double rx, int wsite);
    void copy_delete();

    void Cell_init();
    void net_assign_to_cell();
    std::vector< std::vector<Instance*> >& get_Cell();
    void Gcell_init();
    std::vector<truffle> get_Gcell();

    void pre_placement();
    void place_oneCell(int runtime_gcell, int cell_idx);
    void place_oneCell(int cell_idx);

    double reward_calc();
    double reward_calc_Gcell(int gcell_id);
    double calc_HPWL();
    double calc_HPWL(int gcell_id, int cell_idx);
    double calc_avg_disp();

    int get_Gcell_grid(){return this->Gcell_grid * this->Gcell_grid;}
    int total_cell_num(){return this->total_cell;}
    double get_die_rx(){return this->rx;}
    double get_die_ty(){return this->ty;}
    double get_die_rH(){return this->rowHeight;}
    int get_die_wsite(){return this->wsite;}

    bool calc_done();
    bool calc_Gcell_done(int runtime_gcell);

    void SA(const RLDP& copied, std::vector<int> action_list, int Iter);
  };
}

#endif