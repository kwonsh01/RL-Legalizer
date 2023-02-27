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
    truffle(int x, int y, int z){
      gcell_id = x;
      stdcell_num = y;
      gcell_density = z;
    }
  };

  struct instance {
    opendp::cell *cell;
    bool moveTry;
    int gcell_id;

    instance() : cell(nullptr), moveTry(false), gcell_id(-1) {};
    instance(opendp::cell *cell, int gcell_id) : cell(cell), moveTry(false), gcell_id(gcell_id) {};
  };

  class RLDP : public opendp::circuit {
   public:
    RLDP();
    ~RLDP() = default;
    void read_files(std::string argv, int Gcell_grid_num);
    void copy_data(const circuit& copied);
    std::vector< std::vector<instance> > get_Cell();
    void Gcell_init();
    std::vector<truffle> get_Gcell();
    void pre_placement();
    void place_oneCell(int runtime_gcell, int cell_idx);

   private:
    int total_cell;
    int Gcell_grid;
    std::vector<truffle> Gcell_density;
    std::vector< std::vector<instance> > cell_list_isnotFixed;
  };
}

#endif RL_LEGALIZER_INCLUDE_RLDP_H_
