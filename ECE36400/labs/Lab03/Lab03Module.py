#!/usr/bin/env python3.7

#######################################################
#   Author:     Andrew St. Pierre
#   email:      astpier@purdue.edu
#   ID:         ee364b17
#   Date:       01/29/2019
#######################################################

import os
import sys
from collections import namedtuple

DataPath = os.path.expanduser("~ee364/DataFolder/Lab03")

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

def getStateByCounty(county):
    stateToZip = stateToZips()
    zipsToCoords = getZipsToCoords()
    countyCoordinates = getCountiesToCoordsList()
    try:
        targetCountyCoordinates = countyCoordinates[county]
    except ValueError:
        return set()
    stateList = []
    for state in stateToZip:
        zips = stateToZip[state]
        for z in zips:
            if z in zipsToCoords:
                for coord in zipsToCoords[z]:
                    for c in targetCountyCoordinates:
                        if c.latitude == coord.latitude:
                            if c.longitude == coord.longitude:
                                stateList.append(state)
    return set(stateList)

def getZipsToCoords():
    coordEntries = {}
    CoordEntry = namedtuple("CoordEntry", ["latitude", "longitude"])
    with open(os.path.join(DataPath, "coordinates.dat")) as f:
        lines = f.readlines()
        lines = lines[2:]

    for line in lines:
        line = line.split()
        latitude, longitude, zipcode = line[0].strip(), line[1].strip(), line[2].strip().strip("\n")
        newEntry = CoordEntry(latitude, longitude)
        if int(zipcode) not in coordEntries:
            coordEntries[int(zipcode)] = [newEntry]
        else:
            coordEntries[int(zipcode)].append(newEntry)
    return coordEntries

def getCountiesToCoordsList():
    countyEntries = {}
    CoordEntry = namedtuple("CoordEntry", ["latitude", "longitude"])
    with open(os.path.join(DataPath, "counties.dat")) as f:
        lines = f.readlines()
        lines = lines[2:]
    for line in lines:
        line = line.split()
        if len(line) > 3:
            countyStr = ""
            latitude = line[0].strip()
            longitude = line[1].strip()
            countyList = line[2:]
            for i in countyList:
                countyStr += (i + " ")
            countyName = countyStr.strip().strip("\n")
        else:
            latitude, longitude, countyName = line[0].strip(), line[1].strip(), line[2].strip().strip("\n")
        newEntry = CoordEntry(latitude, longitude)
        if countyName not in countyEntries:
            countyEntries[countyName] = [newEntry]
        else:
            countyEntries[countyName].append(newEntry)
    return countyEntries

def getCount(state):
    if not stateExists(state):
        raise ValueError(f"Invalid state {state}")

    stateToZip = stateToZips()
    zipsToCoords = getZipsToCoords()
    countyCoordinates = getCountiesToCoordsList()

    countyList = []
    zips = stateToZip[state]
    for z in zips:
        for zipCoord in zipsToCoords[z]:
            for county in countyCoordinates:
                for countyCoord in countyCoordinates[county]:
                    if zipCoord.latitude == countyCoord.latitude:
                        if zipCoord.longitude == countyCoord.longitude:
                            countyList.append(county)
    return len(set(countyList))

if __name__ == "__main__":
    #print(getStateByCounty("Orange"))
    print(getCount("New York"))
