#!/usr/bin/env python3.7

#######################################################
#   Author:     Andrew St. Pierre
#   email:      astpier@purdue.edu
#   ID:         ee364b17
#   Date:       01/15/2019
#######################################################

def findLongest():
    """
    Find the starting integer, below or equal to 1000000 that generates
    the longest sequence.
    """
    MAXIMUM = 1000000
    prevSequences,maxLen = {"1":1},0
    for i in range(2,MAXIMUM+1):
        if i % 2 == 0:
            pass
        else:
            val,seqLen = i,1
            while val != None:
                if str(val) in prevSequences:
                    seqLen += int(prevSequences[str(val)])
                    val = None
                elif val % 2 == 0:
                    val = val / 2
                    seqLen += 1
                    if val == 1:
                        val = None
                elif val % 2 == 1:
                    val = val*3 + 1
                    seqLen += 1
                    if val == 1:
                        val = None
            prevSequences[str(i)] = seqLen
            if seqLen > maxLen: maxLen,maxLenVal = seqLen,i
    return maxLenVal
def getSet(val):
    valSet = set()
    for c in str(val):
        valSet.add(c)
    return valSet
def findSmallest():
    curr,satisfied = 1,False
    while satisfied == False:
        if getSet(curr) != getSet(curr*2):
            curr+=1
        elif getSet(curr) != getSet(curr*3):
            curr+=1
        elif getSet(curr) != getSet(curr*4):
            curr+=1
        elif getSet(curr) != getSet(curr*5):
            curr+=1
        elif getSet(curr) != getSet(curr*6):
            curr+=1
        else:
            satisfied = True
    return curr

if __name__ == "__main__":
    #print(findLongest())
    print(findSmallest())