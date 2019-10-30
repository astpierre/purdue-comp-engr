#!/usr/local/bin/python3.8

import sys, os, threading, time
from MatrixMultiply import MatrixMultiply
from MatrixCommander import MatrixCommander

def initArray(a, val):
    for i in range(len(a)):
        for j in range(len(a[0])):
            a[i][j] = val;
    return a

def partitionArrays(a, b, c, rowPartitions, colPartitions):
    partitionedArrays = []
    for rowPartition in range(rowPartitions):
        for colPartition in range(colPartitions):
            mm = MatrixMultiply(a,b,c,colPartitions, colPartition, rowPartitions, rowPartition)
            partitionedArrays.append(mm)
    return partitionedArrays

def multiplyArrays(partitionedArrays):
    start = time.time()
    for mm in partitionedArrays:
        mm.mm()
    end = time.time()
    tdiff = end-start
    print(f"\tduration: {tdiff}s")
    return None

def explain_this(*args):
    print("="*60)
    print(f" Performing Matrix Multiplication\n {args[0]}")
    print("="*60)


def main():
    m = 200
    n = 300
    a=[0]*m
    b=[0]*n
    c=[0]*m
    for i in range(m):
        a[i]=[0]*n
        b[i]=[0]*n
        c[i]=[0]*m
    for i in range(n):
        b[i]=[0]*m

    a=initArray(a, 5)
    b=initArray(b, 2)
    
    # Partition arrays
    partitionedArrays = partitionArrays(a,b,c,2,2)

    # Perform MM() without utilizing threads + display performance
    explain_this(f"USING NO WORKER THREADS")
    multiplyArrays(partitionedArrays)

    # Perform MM() using threads + display performance
    num_threads = 2
    MC = MatrixCommander(num_threads) # Create the commander obj

    # Add jobs to commander's task-queue
    for pa in partitionedArrays: MC.addJob(pa) 
    
    explain_this(f"USING {num_threads} WORKER THREADS")
    MC.run() # Creates threads and executes .mm() on partitions
    
    # Perform MM() using threads + display performance
    num_threads = 4
    MC2 = MatrixCommander(num_threads) # Create the commander obj

    # Add jobs to commander's task-queue
    for pa in partitionedArrays: MC.addJob(pa)
    
    explain_this(f"USING {num_threads} WORKER THREADS")
    MC2.run() # Creates threads and executes .mm() on partitions
    return None

if __name__=="__main__":
    main()
