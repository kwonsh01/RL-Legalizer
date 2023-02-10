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

  string argv = "opendp -lef ../benchmarks/des_perf_a_md1/tech.lef -lef ../benchmarks/des_perf_a_md1/cells_modified.lef -def ../benchmarks/des_perf_a_md1/placed.def -cpu 4 -placement_constraints ../benchmarks/des_perf_a_md1/placement.constraints -output_def ../output/des_perf_a_md1_output.def";

  CMeasure measure;
  measure.start_clock();

  RLDP ckt, ckt0;

  ckt.read_files(argv, 1);
  ckt0.copy_data(ckt);

  ckt.simple_placement(measure);
  ckt.calc_density_factor(4);
  ckt.write_def(ckt.out_def_name);
  ckt.evaluation();
  ckt.check_legality();

  ckt.copy_data(ckt0);

  ckt.evaluation();
  ckt.check_legality();

  cout << " - - - - - < Program END > - - - - - " << endl;

  return 0;
}
