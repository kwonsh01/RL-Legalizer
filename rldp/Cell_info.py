import rldp
import sys
import os

numThreads = 4
outpos = os.getcwd() + "output"
dirpos = os.getcwd() + "/benchmarks"
dirList = os.listdir(dirpos)

def GetFileName( pos, extension ):
    lis = os.listdir( pos )
    res = []
    for curFile in lis:
        if curFile.endswith("." + extension):
            res.append(curFile)
    return res

def GetFileStr( pos, folder, ext, modeStr ):
    retList = GetFileName("%s/%s"%(pos, folder), ext)
    retStr = ""
    for rStr in retList:
        retStr = retStr + "%s %s/%s/%s " % (modeStr, pos, folder, rStr)
    return retStr

if(len(sys.argv)) < 3:
    print("usage:   ./Cell_info.py <benchname_number> <Gcell_number>\n")
    for idx, cdir in enumerate(sorted(dirList)):
        if idx==0: continue
        print("%d %s" % (idx, cdir))
    sys.exit(1)

if sys.argv[1].isdigit():
    benchNum = int(sys.argv[1])
    benchName = sorted(os.listdir(dirpos))[benchNum]
if sys.argv[2].isdigit():
    gcell_grid = int(sys.argv[2])

lefStr = GetFileStr( dirpos, benchName, 'lef', '-lef' )
defStr = GetFileStr( dirpos, benchName, 'def', '-def' )
constStr = GetFileStr( dirpos, benchName, 'constraints', '-placement_constraints' )

exeStr = "opendp" + " " + lefStr + defStr + constStr + " -cpu %d -output_def %s/%s.def" % (numThreads, outpos, benchName)

ckt = rldp.RLDP()
ckt_original = rldp.RLDP()

ckt.read_files(exeStr, gcell_grid)

rH = ckt.get_die_rH()
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
    print("    Cell_id: ", a, "Gcell_id: ", b, "Height: ", j.cell.height/rH)

# print()
# print("Gcell size: ", Gcell.size())
# print()
# for i in (Gcell):
#     a = '%-10s' % str(i.Gcell_id)
#     b = '%-10s' % str(i.stdcell_num)
#     c = '%-10s' % str(i.Gcell_density)
#     print("    Gcell_id: ", a, "Stdcell_num: ", b, "Gcell_density: ", c)

# for i in Cell:
#     for j in i:
#         ckt.place_oneCell(j.cell.id)
# ckt.calc_density_factor(4)
# ckt.evaluation()
# ckt.check_legality()