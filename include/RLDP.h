#ifndef RL_LEGALIZER_INCLUDE_RLDP_H_
#define RL_LEGALIZER_INCLUDE_RLDP_H_

#include "circuit.h"
#include <iostream>

namespace RL_LEGALIZER{
  class RLDP : public opendp::circuit {
   public:
    void read_files(std::string argv, int Gcell_grid_num);
    int Gcell_grid;
  };
}
#endif //RL_LEGALIZER_INCLUDE_RLDP_H_
