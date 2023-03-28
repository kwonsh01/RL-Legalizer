import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.distributions import Categorical
import gc

import rldp
import time
import copy
import math

# from pypreprocessor import pypreprocessor
# pypreprocessor.parse()

#define DEBUG

#Hyperparameters
learning_rate = 0.00003 # 0.003 ~ 0.000005
gamma         = 0.99 # 0.8 ~ 0.9997 in general: 0.99
lmbda         = 0.975 # 0.9 ~ 1.0
eps_clip      = 0.2 # 0.1 ~ 0.3
K_epoch       = 15 # 3 ~ 30
T_horizon     = 50 # 32 ~ 5000

Gcell_grid_num = 3
Iter = 150

class PPO(nn.Module):
    def __init__(self):
        super(PPO, self).__init__()
        self.data = []
        self.fc1 = nn.Linear(5, 128)
        self.fc2 = nn.Linear(128, 128)
        self.fc_pi = nn.Linear(128, 1)
        self.fc_v = nn.Linear(128, 1)
        self.optimizer = optim.Adam(self.parameters(), lr=learning_rate)

    def pi(self, x, softmax_dim=0):
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc_pi(x)
        prob = F.softmax(x, dim=softmax_dim)
        return prob

    def v(self, x):
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        v = self.fc_v(x)
        return v

    def put_data(self, transition):
        self.data.append(transition)

    def make_batch(self):
        s_lst, a_lst, r_lst, s_prime_lst, prob_a_lst, done_lst = [], [], [], [], [], []

        for transition in self.data:
            s, a, r, s_prime, prob_a, done = transition
            s_lst.append(s)
            a_lst.append([a])
            r_lst.append([r])
            s_prime_lst.append(s_prime)
            prob_a_lst.append([prob_a])
            done_mask = 0 if done else 1
            done_lst.append([done_mask])

        s = torch.tensor(s_lst, dtype=torch.float).to(device)
        a = torch.tensor(a_lst).to(device)
        r = torch.tensor(r_lst, dtype=torch.float).to(device)
        s_prime = torch.tensor(s_prime_lst, dtype=torch.float).to(device)
        done_mask = torch.tensor(done_lst, dtype=torch.float).to(device)
        prob_a = torch.tensor(prob_a_lst, dtype=torch.float).to(device)

        self.data = []
        return s, a, r, s_prime, done_mask, prob_a

    def train_net(self):
        s, a, r, s_prime, done_mask, prob_a = self.make_batch()

        a = a.reshape(a.shape[0],1,1)

        for i in range(K_epoch):
            td_target = r + gamma * self.v(s_prime) * done_mask
            delta = td_target - self.v(s)
            delta = delta.cpu()
            delta = delta.detach().numpy()

            advantage_lst = []
            advantage = 0.0
            for delta_t in delta[::-1]:
                advantage = gamma * lmbda * advantage + delta_t[0]
                advantage_lst.append([advantage])
            advantage_lst.reverse()
            advantage = torch.tensor(advantage_lst, dtype=torch.float).to(device)

            pi = self.pi(s, softmax_dim=1)

            pi_a = pi.gather(1,a)

            ratio = torch.exp(torch.log(pi_a) - torch.log(prob_a))  # a/b == exp(log(a)-log(b))
            # ratio = torch.exp((torch.log(pi_a.clamp(1e-45, 1e38)) - torch.log(prob_a.clamp(1e-45, 1e38))).clamp_(max=88))

            surr1 = ratio * advantage # r*A
            surr2 = torch.clamp(ratio, 1-eps_clip, 1+eps_clip) * advantage
            loss = -torch.min(surr1, surr2) + F.smooth_l1_loss(self.v(s) , td_target.detach())

            self.optimizer.zero_grad()
            loss.mean().backward()
            self.optimizer.step()

def read_state_gcell(Cell, rx, ty, rH):
    state = []
    for j in (Cell):
        isTried = 1.0 if j.get_moveTry() else 0.0
        # x = j.get_GcellXcoord(Gcell_grid_num, rx)
        x = j.get_Xcoord(rx)
        # y = j.get_GcellYcoord(Gcell_grid_num, ty)
        y = j.get_Ycoord(ty)
        width = j.get_width(rH)
        net_num = j.get_Netsize()
        state.append([isTried, x, y, width, float(net_num)/Gcell_grid_num])
    return state

def main():
    print("===========================================================================")
    print("   Open Source Mixed-Height Standard Cell Detail Placer < OpenDP_v1.0 >    ")
    print("   Developers : SangGi Do, Mingyu Woo                                      ")
    print("   RL : SH Kwon, SH Kim, CH Lee                                            ")
    print("===========================================================================")

    file = 'nangate45'
    if(file == 'nangate45'):
        argv = "opendp -lef benchmarks/gcd_nangate45/Nangate45_tech.lef -lef benchmarks/gcd_nangate45/Nangate45.lef -def benchmarks/gcd_nangate45/gcd_nangate45_global_place.def -cpu 4 -output_def gcd_nangate45_output.def"
    elif(file == 'des_perf_a_md1'):
        argv = "opendp -lef benchmarks/des_perf_a_md1/tech.lef -lef benchmarks/des_perf_a_md1/cells_modified.lef -def benchmarks/des_perf_a_md1/placed.def -cpu 4 -placement_constraints benchmarks/des_perf_a_md1/placement.constraints -output_def des_perf_a_md1_output.def"
    elif(file == 'des_perf_1'):
        argv = "opendp -lef benchmarks/des_perf_1/tech.lef -lef benchmarks/des_perf_1/cells_modified.lef -def benchmarks/des_perf_1/placed.def -cpu 4 -placement_constraints benchmarks/des_perf_1/placement.constraints -output_def des_perf_1_output.def"
    elif(file == 'fft_2_md2'):
        argv = "opendp -lef benchmarks/fft_2_md2/tech.lef -lef benchmarks/fft_2_md2/cells_modified.lef -def benchmarks/fft_2_md2/placed.def -cpu 4 -placement_constraints benchmarks/fft_2_md2/placement.constraints -output_def fft_2_md2_output.def"
    elif(file == 'fft_a_md2'):
        argv = "opendp -lef benchmarks/fft_a_md2/tech.lef -lef benchmarks/fft_a_md2/cells_modified.lef -def benchmarks/fft_a_md2/placed.def -cpu 4 -placement_constraints benchmarks/fft_a_md2/placement.constraints -output_def fft_a_md2_output.def"
    elif(file == 'fft_a_md3'):
        argv = "opendp -lef fft_a_md2/tech.lef -lef benchmarks/fft_a_md3/cells_modified.lef -def benchmarks/fft_a_md3/placed.def -cpu 4 -placement_constraints benchmarks/fft_a_md3/placement.constraints -output_def fft_a_md3_output.def"
    elif(file == 'pci_bridge32_b_md2'):
        argv = "opendp -lef benchmarks/pci_bridge32_b_md2/tech.lef -lef benchmarks/pci_bridge32_b_md2/cells_modified.lef -def benchmarks/pci_bridge32_b_md2/placed.def -cpu 4 -placement_constraints benchmarks/pci_bridge32_b_md2/placement.constraints -output_def pci_bridge32_b_md2_out.def"
    elif(file == 'gcd'):
        argv = "opendp -lef benchmarks/gcd_nangate45/Nangate45_tech.lef -lef benchmarks/gcd_nangate45/Nangate45.lef -def benchmarks/gcd_nangate45/gcd_replace.def -cpu 4 -output_def gcd_nangate45_output.def"
    elif(file == 'large01'):
        argv = "opendp -lef benchmarks/gcd_nangate45/Nangate45_tech.lef -lef benchmarks/gcd_nangate45/Nangate45.lef -def benchmarks/gcd_nangate45/large01.def -cpu 4 -output_def gcd_nangate45_output.def"
    elif(file == 'medium01'):
        argv = "opendp -lef benchmarks/gcd_nangate45/Nangate45_tech.lef -lef benchmarks/gcd_nangate45/Nangate45.lef -def benchmarks/gcd_nangate45/medium01.def -cpu 4 -output_def gcd_nangate45_output.def"

    output = "data/"

    #post placement
    ckt = rldp.RLDP()
    ckt_original = rldp.RLDP()

    ckt.read_files(argv, Gcell_grid_num)

    Cell = ckt.get_Cell() #total_cell_vector
    Gcell = ckt.get_Gcell() #cell number at Gcells vector, [0]:gcell_id, [1]:stdcell_num, [2]:gcell_density

    ckt.pre_placement()

    rx = ckt.get_die_rx()
    ty = ckt.get_die_ty()
    rH = ckt.get_die_rH()

    ckt_original.copy_allocate(ty, rH, rx, ckt.get_die_wsite())
    ckt_original.copy_data(ckt)

    total_cell = ckt.total_cell_num()
    number_of_gcell = ckt.get_Gcell_grid() #number_of_gcell

    model = PPO().to(device)

    action_list = rldp.IntVector()
    score_arr = []
    hpwl_arr = []
    total_epi_time_arr = []
    avg_disp_arr = []
    #ifdef DEBUG
    inference_time_arr = []
    train_time_arr = []
    #endif

    n_episode = 1
    howLong = int(input("How Long? (min)"))
    timeUp = False
    END = False
    start = time.time()

    while not END:
        print("[TRAIN] Start New Episode!")
        print("[TRAIN] EPISODE #",n_episode)
        epi_time_start = time.time()

        #ifdef DEBUG #endif
        inference_time_start = 0
        train_time_start = 0
        #endif

        #load initial circuit and state
        ckt.copy_data(ckt_original)

        score = 0.0
        stepN = 0
        done = False
        runtime_Gcell = 0 # gcell index using runtime

        while not done:
            gcell_done = False
            placed_cell_num = 0
            s = read_state_gcell(Cell[Gcell[runtime_Gcell].Gcell_id], rx, ty, rH)

            while not gcell_done:
                #step
                current_time = time.time()-start
                print(f'Execute...ing time: {current_time:.3f}[s]')
                #action
                #ifdef DEBUG
                a_time = time.time()
                #endif

                s_List = copy.deepcopy(s)
                s_List = torch.tensor(s_List, dtype=torch.float).to(device)

                prob = model.pi(s_List)
                probf = prob.flatten()

                for i in range(len(s)):
                    if s[i][0]:
                        # if Cell[Gcell[runtime_Gcell].Gcell_id][i].get_moveTry():
                        probf[i] = 0.0

                a = Categorical(probf)
                a = a.sample()
                a = a.item()

                if timeUp:
                    action_list.push_back(Cell[Gcell[runtime_Gcell].Gcell_id][a].cell.id)

                hpwl_before = ckt.calc_HPWL(Gcell[runtime_Gcell].Gcell_id, a)

                #placement and reward/done load
                ckt.place_oneCell(Gcell[runtime_Gcell].Gcell_id, a)
                placed_cell_num = placed_cell_num + 1
                stepN += 1
                #ifdef DEBUG
                inference_time_start += time.time() - a_time
                #endif

                # r = 5*rH / (1+Cell[Gcell[runtime_Gcell].Gcell_id][a].cell.disp)

                # r = 100 * ckt.reward_calc_Gcell(Gcell[runtime_Gcell].Gcell_id)
                hpwl_after = ckt.calc_HPWL(Gcell[runtime_Gcell].Gcell_id, a)
                hpwl_delta = 10 *  (hpwl_after - hpwl_before)/hpwl_after
                r = math.exp(-hpwl_delta)
                #+ rH / (1+Cell[Gcell[runtime_Gcell].Gcell_id][a].cell.disp)

                print("\033[31m" + "Episode: " + "\033[0m", n_episode)
                print("\033[33m" + "reward: " + "\033[0m", r)
                print("\033[32m" + "         placed_Gcell_num: ", placed_cell_num, "\033[0m")
                print("\033[32m" + "         stdcell_num_Gcell: ", Gcell[runtime_Gcell].stdcell_num, "\033[0m")
                print("\033[32m" + "         stepN: ", stepN, "\033[0m")
                print("\033[32m" + "         total_cell_num: ", total_cell, "\033[0m")
                print("\033[32m" + "         runtime_Gcell: ", runtime_Gcell, "\033[0m")
                print("\033[32m" + "         Gcell_id: ", Gcell[runtime_Gcell].Gcell_id, "\033[0m")

                #cellist reload and state update
                s_prime = read_state_gcell(Cell[Gcell[runtime_Gcell].Gcell_id], rx, ty, rH)

                model.put_data((s, a, r, s_prime, probf[a].item(), done))

                s = s_prime

                score += r

                gcell_done = ckt.calc_Gcell_done(runtime_Gcell)

            #ifdef DEBUG
            t_time = time.time()
            #endif
            model.train_net()
            #ifdef DEBUG
            train_time_start += time.time() - t_time
            #endif

            runtime_Gcell += 1

            done = ckt.calc_done()

        #episode end
        score_arr.append(score)
        hpwl_arr.append(ckt.HPWL(""))
        total_epi_time_arr.append(time.time() - epi_time_start)
        #ifdef DEBUG
        inference_time_arr.append(inference_time_start)
        train_time_arr.append(train_time_start)
        #endif
        avg_disp_arr.append(ckt.calc_avg_disp())

        if timeUp:
            END = True
        if(time.time() - start) > howLong * 60:
            timeUp = True
        else:
            n_episode += 1

    # SA
    ckt.SA(ckt_original, action_list, Iter)
    ckt_original.copy_delete()

    end = time.time()
    print()
    print("[TRAIN] End Training!")
    total_time = end-start
    print(f'\033[31mExecute Time: \033[0m {total_time:.3f}[s]')
    print("\033[31m" + "Execute Episode: " + "\033[0m", n_episode)
    print()

    ckt.write_def("output/"+str(time.localtime().tm_mon)+"_"+str(time.localtime().tm_mday)+"_"+str(time.localtime().tm_hour)+"_"+str(time.localtime().tm_sec)+".def")
    print("data: ", output)

    f1 = open(output + "hpwl.txt", 'w')
    f3 = open(output + "score.txt", 'w')
    f4 = open(output + "epi_time.txt", 'w')
    f5 = open(output + "avg_disp.txt", 'w')
    #ifdef DEBUG
    f6 = open(output + "train_time.txt", 'w')
    f7 = open(output + "inference_time.txt", 'w')
    #endif

    f1.write(str(hpwl_arr))
    f3.write(str(score_arr))
    f4.write(str(total_epi_time_arr))
    f5.write(str(avg_disp_arr))
    #ifdef DEBUG
    f6.write(str(train_time_arr))
    f7.write(str(inference_time_arr))
    #endif

    print("- - - - - < Program END > - - - - - ")

if __name__ == '__main__':
    is_cuda = torch.cuda.is_available()
    if is_cuda:
        gc.collect()
        torch.cuda.empty_cache()
        device = torch.device("cuda:1")
        print("GPU is available")
    else:
        device = torch.device("cpu")
        print("GPU not available, CPU used")
    main()
