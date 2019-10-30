#!/usr/local/bin/python3.8

import sys, os, threading, time
from MyReader import MyReader
from MatrixMultiply import MatrixMultiply
from Commander import Commander
from utils import *


def main():
    # Fetch arrays for MatrixMultiply jobs
    partitioned_arrays = fetchArrays()
    
    # Create MyReader instances 
    mr1 = MyReader("input/file1.txt")
    mr2 = MyReader("input/file2.txt")
    mr3 = MyReader("input/file3.txt")
    
    # Create the commander object w/ N threads
    num_threads = 2
    C = Commander(num_threads)

    # Add MatrixMultiply jobs to commander's task-queue
    for pa in partitioned_arrays: C.addJob(pa) 
    
    # Add MyReader instance jobs to commander's task-queue
    for j in (mr1, mr2, mr3): C.addJob(j)

    # Execute all commands in commander's task-queue
    duration = C.run()
    print(f"  Duration: {duration}s")

    return None

if __name__=="__main__":
    main()
