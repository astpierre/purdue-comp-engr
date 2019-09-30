###############################################################################
#   Author:	Andrew St. Pierre
#   email: 	astpier@purdue.edu
#   ID: 	ee364b17
#   Date: 	Thursday, January 10, 2019
###############################################################################

import os
import sys

# Module level variables
DataPath = os.path.expanduser('~ee364/DataFolder/Prelab01')

def find(pattern: str) -> list:
    """
    Reads the file sequence.txt and searches for the provided input pattern
    Returns a list of all number sequences that match given pattern
    """
    # Load the data sequence first into a variable
    path = os.path.join(DataPath, 'sequence.txt')
    fileHandle = open(path, 'r')
    sequence = fileHandle.read() #'1547896154321687984'

    # Create a list of all testable subsequences
    patLen, seqLen, subSeqs = len(pattern), len(sequence), []
    x,y = 0, patLen
    while y <= seqLen:
        subSeqs.append(sequence[x:y])
        x,y = x+1, y+1

    # Test each subsequence for condition matching
    matches, notMatch = [], False
    for s in subSeqs:
        i = 0
        while i<patLen:
            if s[i] == pattern[i]:
                i = i + 1
            elif pattern[i] == "X":
                i = i + 1
            else:
                notMatch = True
                break
        if notMatch == True:
            notMatch = False
        elif notMatch == False:
            matches.append(s)
    return matches

def getStreakProduct(sequence: str, maxSize: int, product: int) -> list:
    """
    Searches the string sequence for all subsequences whos size is between
    two and maxSize, inclusively.
    Returns a list of all subsequences whose digital product equals product.
    """
    # Create a list of all testable subsequences
    x,subSeqs = 0,[]
    for x in range(len(sequence)):
        y = 2
        while y <= maxSize:
            if x+y > len(sequence): break
            else:
                subSeqs.append(sequence[x:x+y])
                y += 1

    # Test each subsequence for condition matching
    matches = []
    for s in subSeqs:
        multiplicands,p = [],1
        multiplicands = [int(i) for i in list(s)]
        for m in multiplicands: p *= m
        if p == product: matches.append(s)
    return matches

def writePyramids(filePath: str, baseSize: int, count: int, char: str) -> None:
    """
    Saves one or more pyramid-shaped sequences of characters to file.
    """
    # Open the file designated by filePath
    fileHandle = open(filePath, 'w')

    # Generate a single pyramid and use it to generate the rest
    nspaces,nchars,pyramid = baseSize//2,1,[]
    while nchars <= baseSize:
        pyramid.append(nspaces*" "+nchars*char+nspaces*" ")
        nchars+=2
        nspaces-=1

    # Write the list to the target file
    for l in pyramid:
        line = (str(l)+" ")*count
        fileHandle.write(line+'\n')

def getStreaks(sequence: str, letters: str) -> list:
    """
    Takes in a string and returns a list of the streaks, in the order
    of their appearance in the sequence, of the letters provided.
    """
    streakDict = {}
    for l in letters:
        streak,idx,idx_prev = "",0,-1
        while(idx >= 0):
            if idx_prev == -1:
                idx = sequence.find(l)
            else:
                idx = sequence.find(l,idx+1)
            if int(idx_prev) != int(idx) - 1:
                if idx == -1: break
                else:
                    if streak != "":
                        streakDict[streak] = startIndex
                    startIndex,idx_prev,streak = idx,idx,sequence[idx]
            elif idx == 0:
                startIndex, idx_prev, streak = idx, idx, sequence[idx]
            else:
                idx_prev = idx
                streak += str(sequence[idx])
        if streak not in streakDict and streak != "":
            streakDict[streak] = startIndex
    orderedStreakDict = sorted(streakDict, key=streakDict.__getitem__)
    return list(orderedStreakDict)

def findNames(nameList: list, part: str, name: str) -> list:
    """
    Takes in a list of names and returns the matches in nameList for
    the given name and part (F)irst or (L)ast. Returns a list of matches.
    """
    parts = ["F","L","FL"]
    if part not in parts: return []
    matches = []
    for person in nameList:
        person = person.split()
        if part == "F":
            if person[0].lower() == name.lower():
                matches.append(str(person[0]+" "+person[1]))
        elif part == "L":
            if person[1].lower() == name.lower():
                matches.append(str(person[0]+" "+person[1]))
        elif part == "FL" or part == "LF":
            if person[0].lower() == name.lower():
                matches.append(str(person[0]+" "+person[1]))
            elif person[1].lower() == name.lower():
                matches.append(str(person[0]+" "+person[1]))
    return matches

def convertToBoolean(num: int, size: int) -> list:
    """
    Takes in a positive integer and returns a list of Booleans representing
    the number num where the length of the list is a minmum of size.
    """
    if type(num) != int: return []
    if type(size) != int: return []
    boolList = []
    binary = str(bin(num))
    binary = binary[2:]
    x = 0
    while (x+len(binary)) < size:
        boolList.append(False)
        x += 1
    for b in binary:
        boolList.append(bool(int(b)))
    return boolList

def convertToInteger(boolList: int) -> int:
    """
    Takes in a list of Booleans representing the integer to be returned.
    """
    if type(boolList) != list: return None
    if not len(boolList): return None
    binaryList = ""
    for b in boolList:
        if b == True:
            binaryList += '1'
        elif b == False:
            binaryList += '0'
        else:
            return None
    return(int(binaryList,2))

if __name__ == "__main__":
    # Write anything here to test your code
    #print(find('154'))
    #print(find('X54'))
    #print(getStreakProduct('14822',3,32))
    #writePyramids('pyramids13.txt',13,6,'X')
    #writePyramids('pyramids15.txt', 15, 5, '*')
    #print(getStreaks("AAASSSSSSAPPPSSPPBBCCCSSS", "SAQT"))
    #print(getStreaks("AAASSSSSSAPPPSSPPBBCCCSSS", "PAZ"))
    #print(getStreaks("AAASSSSSSAPPPSSPPBBCCCSSS", "Q"))
    names = ["George Smith", "Mark Johnson", "Cordell Theodore", "Maria Satterfield", "Johnson Cadence"]
    #print(findNames(names, "L", "johnson"))
    #print(findNames(names, "F", "JOHNSON"))
    #print(findNames(names, "FL", "Johnson"))
    #print(convertToBoolean(135, 12))
    #print(convertToBoolean(9, 3))
    bList = [True, False, False, False, False, True, True, True]
    bList2 = [False, False, True, False, False, True]
    #print(convertToInteger(bList))
    #print(convertToInteger(bList2))
    #print(convertToInteger([True, True]))
