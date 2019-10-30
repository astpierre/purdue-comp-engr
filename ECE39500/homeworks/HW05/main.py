import sys, os, threading
from MatrixMultiply import MatrixMultiply
from pprint import PrettyPrinter as pp

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
    for mm in partitionedArrays:
        mm.mm()
    return



def main():
    a=[0]*4
    b=[0]*4
    c=[0]*4
    for i in range(4):
        a[i]=[0]*4
        b[i]=[0]*4
        c[i]=[0]*4
    a=initArray(a, 5)
    b=initArray(b, 2)
    partitionedArrays = partitionArrays(a,b,c,1,1)
    for pa in partitionedArrays:
        pa.mm()
    print(c)
    return None

if __name__=="__main__":
    main()