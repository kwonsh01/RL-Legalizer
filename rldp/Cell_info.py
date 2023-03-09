import rldp
import sys
import time

if(len(sys.argv)) < 3:
    print("Invalid arguments")
    print("Gcell grid num?: ")
    print("1: Nangate45")
    print("2: des_perf_a_md1")
    sys.exit()

gcell_grid = int(sys.argv[1])

if(int(sys.argv[2]) == 1):
    argv = "opendp -lef benchmarks/gcd_nangate45/Nangate45_tech.lef -lef benchmarks/gcd_nangate45/Nangate45.lef -def benchmarks/gcd_nangate45/gcd_nangate45_global_place.def -cpu 8 -output_def gcd_nangate45_output.def"
else:
    argv = "opendp -lef benchmarks/des_perf_a_md1/tech.lef -lef benchmarks/des_perf_a_md1/cells_modified.lef -def benchmarks/des_perf_a_md1/placed.def -cpu 8 -placement_constraints benchmarks/des_perf_a_md1/placement.constraints -output_def des_perf_a_md1_output.def"

ckt = rldp.RLDP()
ckt_original = rldp.RLDP()

ckt.read_files(argv, gcell_grid)

Cell = ckt.get_Cell()
Gcell = ckt.get_Gcell()
x = 0
print("Cell size: ", Cell.size())
for i in Cell:
    print()
    print("\033[32m", x,  "\033[0m", "'s Gcell size: ", i.size())
    x += 1
    for j in i:
        a = '%-10s' % str(j.cell.id)
        b = '%-10s' % str(j.Gcell_id)
        print("    Cell_id: ", a, "Gcell_id: ", b)

print()
print("Gcell size: ", Gcell.size())
print()
for i in (Gcell):
    a = '%-10s' % str(i.Gcell_id)
    b = '%-10s' % str(i.stdcell_num)
    c = '%-10s' % str(i.Gcell_density)
    print("    Gcell_id: ", a, "Stdcell_num: ", b, "Gcell_density: ", c)