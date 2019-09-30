import os
import sys
import numpy as np
import matplotlib.pyplot as plt

def getData( ):
    with open("output.txt") as f:
        lines = f.readlines()
    n_size = []
    cpu_ticks = []
    for line in lines:
        line = line.split()
        n_size.append(float(line[0]))
        cpu_ticks.append(float(line[1]))
    plt.xticks(np.arange(0, 1000000, step=200000))
    plt.yticks(np.arange(0, 500000, step=25000))
    plt.plot(n_size, cpu_ticks)
    plt.xlabel("Number of longs to sort (N)")
    plt.ylabel("CPU clock ticks required to sort array")
    plt.title("size of array vs time to sort")
    #plt.show()
    plt.savefig('plots/quick_sort_01.png')

if __name__ == '__main__':
    getData()
