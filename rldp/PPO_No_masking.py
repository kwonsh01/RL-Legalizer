import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.distributions import Categorical
import gc

import rldp
import time

#Hyperparameters
learning_rate = 0.00002 # 0.003 ~ 0.000005
gamma         = 0.99 # 0.8 ~ 0.9997 in general: 0.99
lmbda         = 0.95 # 0.9 ~ 1.0
eps_clip      = 0.2 # 0.1 ~ 0.3
K_epoch       = 15 # 3 ~ 30
T_horizon     = 50 # 32 ~ 5000

Gcell_grid_num = 3
Iter = 0
minEpi = 100000

class EarlyStopping:
    def __init__(self, patience=20, verbose=False, delta_disp = 0, path='checkpoint.pt'):
        self.patience = patience
        self.verbose = verbose
        self.counter = 0
        self.best_score = None
        self.best_disp = None
        self.early_stop = False
        self.disp_min = 10000
        self.avg_disp = 10000
        self.delta_disp = delta_disp
        self.path = path

    def __call__(self, disp, avg_disp, model):
        if self.best_score is None and self.best_disp is None:
            self.best_disp = disp
            self.save_checkpoint(disp, avg_disp, model)
        elif (disp > self.best_disp - self.delta_disp and avg_disp > self.avg_disp - self.delta_disp):
            self.counter += 1
            print(f'EarlyStopping counter: {self.counter} out of {self.patience}')
            if self.counter >= self.patience:
                self.early_stop = True
        else:
            self.best_disp = disp
            self.avg_disp = avg_disp
            self.save_checkpoint(disp, avg_disp, model)
            self.counter = 0

    def save_checkpoint(self, disp, avg_disp, model):
        if self.verbose:
            print(f'Disp decresed({self.disp_min:.6f} --> {disp:.6f}).  Saving model ...')
        torch.save(model.state_dict(), self.path)
        self.disp_min = disp
        self.avg_disp = avg_disp

class PPO(nn.Module):
    def __init__(self):
        super(PPO, self).__init__()
        self.data = []
        self.fc1 = nn.Linear(9, 256)
        self.fc2 = nn.Linear(256, 256)
        self.fc3 = nn.Linear(256, 256)
        self.fc4 = nn.Linear(256, 256)
        self.fc_pi = nn.Linear(256, 1)
        self.fc_v = nn.Linear(256, 1)
        self.optimizer = optim.Adam(self.parameters(), lr=learning_rate)

    def pi(self, x, softmax_dim=0):
        x = F.normalize(x, dim=softmax_dim)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = F.relu(self.fc3(x))
        x = F.relu(self.fc4(x))
        x = self.fc_pi(x)
        prob = F.softmax(x, dim=softmax_dim)
        return prob

    def v(self, x):
        x = F.normalize(x, dim=0)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = F.relu(self.fc3(x))
        x = F.relu(self.fc4(x))
        x = self.fc_v(x)
        return x

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

            ratio = torch.exp(torch.log(pi_a) - torch.log(prob_a))
            # ratio = torch.exp((torch.log(pi_a.clamp(1e-45, 1e38)) - torch.log(prob_a.clamp(1e-45, 1e38))).clamp_(max=88))

            surr1 = ratio * advantage # r*A
            surr2 = torch.clamp(ratio, 1-eps_clip, 1+eps_clip) * advantage
            loss = -torch.min(surr1, surr2) + F.smooth_l1_loss(self.v(s) , td_target.detach())

            self.optimizer.zero_grad()
            loss.mean().backward()
            self.optimizer.step()

def read_state_gcell(Cell, rx, ty, rH, placed_cell_num, ckt):
    state = []
    total_gcell = Cell.size()
    for j in (Cell):
        moveTry = 1.0 if j.moveTry else 0.0
        # x = j.get_GcellXcoord(Gcell_grid_num, rx)
        # y = j.get_GcellYcoord(Gcell_grid_num, ty)
        x = j.get_Xcoord(rx)
        y = j.get_Ycoord(ty)
        width = j.get_Width(rH)
        height = j.get_Height(rH)
        net_num = j.get_Net_num()
        near_cell = j.get_Nearcell_num(ckt)
        state.append([moveTry, x, y, width, height, net_num, near_cell, total_gcell, placed_cell_num])
    return state

def main():
    print("===========================================================================")
    print("   Open Source Mixed-Height Standard Cell Detail Placer < OpenDP_v1.0 >    ")
    print("   Developers : SangGi Do, Mingyu Woo                                      ")
    print("   RL : SH Kwon, SH Kim, CH Lee                                            ")
    print("===========================================================================")

    file = 'nangate45'
    # file = 'des_perf_a_md1'
    # file = 'fft_2_md2'
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
    elif(file == 'pci_bridge32_b_md1'):
        argv = "opendp -lef benchmarks/pci_bridge32_b_md1/tech.lef -lef benchmarks/pci_bridge32_b_md1/cells_modified.lef -def benchmarks/pci_bridge32_b_md1/placed.def -cpu 4 -placement_constraints benchmarks/pci_bridge32_b_md1/placement.constraints -output_def pci_bridge32_b_md1_out.def"
    elif(file == 'pci_bridge32_b_md2'):
        argv = "opendp -lef benchmarks/pci_bridge32_b_md2/tech.lef -lef benchmarks/pci_bridge32_b_md2/cells_modified.lef -def benchmarks/pci_bridge32_b_md2/placed.def -cpu 4 -placement_constraints benchmarks/pci_bridge32_b_md2/placement.constraints -output_def pci_bridge32_b_md2_out.def"
    elif(file == 'gcd'):
        argv = "opendp -lef benchmarks/gcd_nangate45/Nangate45_tech.lef -lef benchmarks/gcd_nangate45/Nangate45.lef -def benchmarks/gcd_nangate45/gcd_replace.def -cpu 4 -output_def gcd_nangate45_output.def"
    elif(file == 'large01'):
        argv = "opendp -lef benchmarks/gcd_nangate45/Nangate45_tech.lef -lef benchmarks/gcd_nangate45/Nangate45.lef -def benchmarks/gcd_nangate45/large01.def -cpu 4 -output_def gcd_nangate45_output.def"
    elif(file == 'medium01'):
        argv = "opendp -lef benchmarks/gcd_nangate45/Nangate45_tech.lef -lef benchmarks/gcd_nangate45/Nangate45.lef -def benchmarks/gcd_nangate45/medium01.def -cpu 4 -output_def gcd_nangate45_output.def"

    output = "data/"
    # output = "data_des/"
    # output = "data_fft/"

    model = PPO().to(device)
    load = input("Load model? [y/n]")
    if(load == 'y'):
        checkpoint = torch.load('data/checkpoint.pt')
        model.load_state_dict(checkpoint)

    #post placement
    ckt = rldp.RLDP()
    ckt_original = rldp.RLDP()

    ckt.read_files(argv, Gcell_grid_num)

    Cell = ckt.get_Cell() #total_cell_vector, sorted by gcell_id
    Gcell = ckt.get_Gcell() #cell number at Gcells vector, [0]:gcell_id, [1]:stdcell_num, [2]:gcell_density

    ckt.pre_placement()

    rx = ckt.get_die_rx()
    ty = ckt.get_die_ty()
    rH = ckt.get_die_rH()

    ckt_original.copy_allocate(ty, rH, rx, ckt.get_die_wsite())
    ckt_original.copy_data(ckt)

    total_cell = ckt.total_cell_num()

    action_list = rldp.IntVector()
    score_arr = []
    hpwl_arr = []
    total_epi_time_arr = []
    avg_disp_arr = []
    inference_time_arr = []
    train_time_arr = []
    early_stopping = EarlyStopping(patience = 20, verbose = True)

    n_episode = 1
    howLong = int(input("How Long? (min)"))
    timeUp = False
    END = False
    start = time.time()

    while not END:
        print("[TRAIN] Start New Episode!")
        print("[TRAIN] EPISODE #", n_episode)
        epi_time_start = time.time()

        inference_time_start = 0
        train_time_start = 0

        ckt.copy_data(ckt_original)

        score = 0.0
        stepN = 0
        done = False
        runtime_Gcell = 0 # gcell index using runtime

        while not done:
            gcell_done = False
            placed_cell_num = 0
            s = read_state_gcell(Cell[Gcell[runtime_Gcell].Gcell_id], rx, ty, rH, placed_cell_num, ckt)

            while not gcell_done:
                #step
                current_time = time.time()-start
                print(f'Execute...ing time: {current_time:.3f}[s]')
                #action
                a_time = time.time()
                s_List = s[:]
                s_List = torch.tensor(s_List, dtype=torch.float).to(device)

                prob = model.pi(s_List)
                probf = prob.flatten()

                for i in range(len(s)):
                    if s[i][0]:
                        probf[i] = 0.0

                a = Categorical(probf)
                a = a.sample()
                a = a.item()

                if timeUp:
                    action_list.push_back(Cell[Gcell[runtime_Gcell].Gcell_id][a].cell.id)

                #placement
                placed = ckt.place_oneCell(Gcell[runtime_Gcell].Gcell_id, a)
                placed_cell_num += 1
                stepN += 1
                inference_time_start += time.time() - a_time

                #reward
                if(placed):
                    r = rH/(1+Cell[Gcell[runtime_Gcell].Gcell_id][a].cell.disp)
                else:
                    r = -5

                print("\033[31m" + "Episode: " + "\033[0m", n_episode)
                print("\033[33m" + "reward: " + "\033[0m", r)
                print("\033[32m" + "         placed_Gcell_num: ", placed_cell_num, "\033[0m")
                print("\033[32m" + "         stdcell_num_Gcell: ", Gcell[runtime_Gcell].stdcell_num, "\033[0m")
                print("\033[32m" + "         stepN: ", stepN, "\033[0m")
                print("\033[32m" + "         total_cell_num: ", total_cell, "\033[0m")

                #cellist reload and state update
                s_prime = read_state_gcell(Cell[Gcell[runtime_Gcell].Gcell_id], rx, ty, rH, placed_cell_num, ckt)
                model.put_data((s, a, r, s_prime, probf[a].item(), done))
                s = s_prime

                score += r
                gcell_done = ckt.calc_Gcell_done(runtime_Gcell)

            t_time = time.time()
            model.train_net()
            train_time_start += time.time() - t_time

            runtime_Gcell += 1
            done = ckt.calc_done()

        #episode end
        score_arr.append(score)
        hpwl_arr.append(ckt.HPWL(""))
        total_epi_time_arr.append(time.time() - epi_time_start)
        inference_time_arr.append(inference_time_start)
        train_time_arr.append(train_time_start)
        avg_disp_arr.append(ckt.calc_avg_disp())

        if(n_episode >= minEpi):
            avgDisp = 0
            for i in range(minEpi):
                avgDisp += avg_disp_arr[n_episode - 1 - i]

            avgDisp = avgDisp / minEpi

            early_stopping(avg_disp_arr[n_episode - 1], avgDisp, model)

        if timeUp:
            END = True
        elif(early_stopping.early_stop):
            timeUp = True
        elif(time.time() - start) > howLong * 60:
            timeUp = True

        n_episode += 1

    # SA
    ckt.SA(ckt_original, action_list, Iter)
    ckt_original.copy_delete()

    total_time = time.time() - start
    print()
    print("[TRAIN] End Training!")
    print(f'\033[31mExecute Time: \033[0m {total_time:.3f}[s]')
    print("\033[31m" + "Execute Episode: " + "\033[0m", n_episode)
    print()

    ckt.write_def("output/"+file+"_"+str(time.localtime().tm_mon)+"_"+str(time.localtime().tm_mday)+"_"+str(time.localtime().tm_hour)+"_"+str(time.localtime().tm_min)+".def")
    print("data: ", output)

    f1 = open(output + "hpwl.txt", 'w')
    f3 = open(output + "score.txt", 'w')
    f4 = open(output + "epi_time.txt", 'w')
    f5 = open(output + "avg_disp.txt", 'w')
    f6 = open(output + "train_time.txt", 'w')
    f7 = open(output + "inference_time.txt", 'w')

    f1.write(str(hpwl_arr))
    f3.write(str(score_arr))
    f4.write(str(total_epi_time_arr))
    f5.write(str(avg_disp_arr))
    f6.write(str(train_time_arr))
    f7.write(str(inference_time_arr))

    print("- - - - - < Program END > - - - - - ")

if __name__ == '__main__':
    is_cuda = torch.cuda.is_available()
    if is_cuda:
        gc.collect()
        torch.cuda.empty_cache()
        device = torch.device("cuda:0")
        print("GPU is available")
    else:
        device = torch.device("cpu")
        print("GPU not available, CPU used")
    main()
