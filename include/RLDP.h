#ifndef RL_LEGALIZER_INCLUDE_RLDP_H_
#define RL_LEGALIZER_INCLUDE_RLDP_H_

#include "circuit.h"
#include <iostream>

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

  class RLDP : public opendp::circuit {
   public:
    RLDP();
    ~RLDP() = default;
    void read_files(std::string argv, int Gcell_grid_num);
    void copy_data(const circuit& copied);

    int Gcell_grid;
    std::vector<truffle> Gcell_density;
    std::vector< std::vector<opendp::cell*> > cell_list_isnotFixed;
  };

}
#endif //RL_LEGALIZER_INCLUDE_RLDP_H_
