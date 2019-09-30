#!/usr/bin/env python3.7

#######################################################
#   Author:     Andrew St. Pierre
#   email:      astpier@purdue.edu
#   ID:         ee364b17
#   Date:       01/22/2019
#######################################################

import os
import sys

DataPath = os.path.expanduser("~ee364/DataFolder/Lab02")

def stateExists(stateName):
    """
    :param state
    :return T/F if state is present in *.dat file
    """
    with open(os.path.join(DataPath, "zip.dat")) as f:
        for line in f.readlines():
            if stateName in line:
                return True
        return False

def stateToZips():
    """
    :param none
    :return dictionary mapping state names to list of zipcodes
    """
    nameToZips = {}
    with open(os.path.join(DataPath, "zip.dat")) as f:
        for i in range(2):
            f.readline()
        for line in f.readlines():
            line = line.split()
            if len(line) > 3:
                tmp = str(line[0])+" "+str(line[1])
                if tmp not in nameToZips:
                    nameToZips[tmp] = [int(line[3])]
                else:
                    nameToZips[tmp].append(int(line[3]))
            elif line[0] not in nameToZips:
                nameToZips[line[0]] = [int(line[2])]
            else:
                nameToZips[line[0]].append(int(line[2]))
    return nameToZips

def getCodeFor(stateName):
    """
    INPUT: full state name
    OUTPUT: list of zip codes belonging to that state
    """
    if not stateExists(stateName): return []
    # Get a dictionary
    nameToZips = stateToZips()
    zips = nameToZips[stateName]
    strZips = []
    zips.sort()
    for z in zips:
        strZips.append(str(z))

    return strZips

def getMinLatitude(stateName):
    """
    INPUT: full state name
    OUTPUT: minimum latitude value of give state
    """
    stateZips,lats = getCodeFor(stateName),[]
    with open(os.path.join(DataPath, "coordinates.dat")) as f:
        for i in range(2):
            f.readline()
        for line in f.readlines():
            line = line.split()
            if line[2] in stateZips:
                lats.append(float(line[0]))
    return min(lats)

def getMaxLongitude(stateName):
    """
    INPUT: full state name
    OUTPUT: minimum latitude value of give state
    """
    stateZips,longits = getCodeFor(stateName),[]
    with open(os.path.join(DataPath, "coordinates.dat")) as f:
        for i in range(2):
            f.readline()
        for line in f.readlines():
            line = line.split()
            if line[2] in stateZips:
                longits.append(float(line[1]))
    return max(longits)


if __name__ == "__main__":
    print(getCodeFor("Indiana"))
    print(getMinLatitude("Indiana"))
    print(getMaxLongitude("Indiana"))