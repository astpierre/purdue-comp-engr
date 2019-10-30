import sys, os, threading, time
from MyReader import MyReader
from MatrixMultiply import MatrixMultiply
from Commander import Commander

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

def fetchArrays():
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
    return partitionArrays(a,b,c,2,2)

def explain_this(*args):
    print("="*60)
    print(f" Performing {args[0]}")
    print("="*60)
