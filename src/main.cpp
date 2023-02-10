#include <iostream>
#include "RLDP.h"

using namespace std;
using namespace RL_LEGALIZER;

int main() {

  cout << "===========================================================================" << endl;
  cout << "   Open Source Mixed-Height Standard Cell Detail Placer < OpenDP_v1.0 >    " << endl;
  cout << "   Developers : SangGi Do, Mingyu Woo                                      " << endl;
  cout << "   RL : SH Kwon, SH Kim, CH Lee                                            " << endl;
  cout << "===========================================================================" << endl;

//  string argv = "opendp -lef ../benchmarks/des_perf_a_md1/tech.lef -lef ../benchmarks/des_perf_a_md1/cells_modified.lef -def ../benchmarks/des_perf_a_md1/placed.def -cpu 4 -placement_constraints ../benchmarks/des_perf_a_md1/placement.constraints -output_def ../output/des_perf_a_md1_output.def";
  string argv = "opendp -lef ../benchmarks/gcd_nangate45/Nangate45_tech.lef -lef ../benchmarks/gcd_nangate45/Nangate45.lef -def ../benchmarks/gcd_nangate45/gcd_nangate45_global_place.def -cpu 4 -output_def ../output/gcd_nangate45_output.def";

  RLDP ckt;

  ckt.read_files(argv, 3);

  ckt.pre_placement();

  std::vector< std::vector<instance> > Cells = ckt.get_Cell();
  std::vector<truffle> Gcells = ckt.get_Gcell();

  for(int i = 0; i < Gcells.size(); i++){
    cout << " GCell's id: " << Gcells[i].gcell_id << endl;
    cout << "   GCell's cells_num: " << Gcells[i].stdcell_num << endl;
    cout << "   GCell's density: " << Gcells[i].gcell_density << endl;
  }

  for(int i = 0; i < Cells.size(); i++){
    for(int j = 0; j < Cells[i].size(); j++){
      ckt.place_oneCell(i, j);
    }
  }

  ckt.calc_density_factor(4);
  ckt.write_def(ckt.out_def_name);
  ckt.evaluation();
  ckt.check_legality();

  cout << " - - - - - < Program END > - - - - - " << endl;

  return 0;
}
