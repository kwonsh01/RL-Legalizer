from matplotlib import pyplot as plt
from scipy.signal import savgol_filter
import numpy as np
import ast
# from pypreprocessor import pypreprocessor

# pypreprocessor.parse()

#define DEBUG

f1 = open("hpwl.txt", 'r')
f3 = open("score.txt", 'r')
f4 = open("epi_time.txt", 'r')
f5 = open("avg_disp.txt", 'r')
#ifdef DEBUG
f6 = open("train_time.txt", 'r')
f7 = open("inference_time.txt", 'r')
#endif

hpwl = f1.readline()
score = f3.readline()
epi_time = f4.readline()
avg_disp = f5.readline()
#ifdef DEBUG
train_time = f6.readline()
inference_time = f7.readline()
#endif

hpwl = ast.literal_eval(hpwl)
score = ast.literal_eval(score)
epi_time = ast.literal_eval(epi_time)
avg_disp = ast.literal_eval(avg_disp)
#ifdef DEBUG
train_time = ast.literal_eval(train_time)
inference_time = ast.literal_eval(inference_time)
#endif

hpwl_mean = sum(hpwl) / len(hpwl)
score_mean = sum(score) / len(score)
epi_time_mean = sum(epi_time) / len(epi_time)
avg_disp_mean = sum(avg_disp) / len(avg_disp)
#ifdef DEBUG
train_time_mean = sum(train_time) / len(train_time)
inference_time_mean = sum(inference_time) / len(inference_time)
#endif

score_s = savgol_filter(score, 51, 3)
hpwl_s = savgol_filter(hpwl, 51, 3)
avg_disp_s = savgol_filter(avg_disp, 51, 3)

print("\033[31m" + "score_mean:" + "\033[0m", score_mean)
print("\033[31m" + "hpwl_mean: " + "\033[0m", hpwl_mean)
print("\033[31m" + "avg_disp_mean: " + "\033[0m", avg_disp_mean)
print("\033[31m" + "episode_time_mean: " + "\033[0m", epi_time_mean)
#ifdef DEBUG
print("\033[31m" + "train_time_mean: " + "\033[0m", train_time_mean)
print("\033[31m" + "inference_time_mean: " + "\033[0m", inference_time_mean)
#endif

plt.title("Score")
plt.plot(score, alpha=0.5, color=[10/255,46/255,36/255])
plt.plot(score_s)
plt.show()

plt.title("HPWL")
plt.plot(hpwl, alpha=0.5, color=[0.3,0.3,0.5])
plt.plot(hpwl_s)
plt.show()

plt.title("Avg_disp")
plt.plot(avg_disp, alpha=0.5, color=[0.3,0.3,0.5])
plt.plot(avg_disp_s)
plt.show()

plt.title("Episode_time")
plt.plot(epi_time)
plt.show()