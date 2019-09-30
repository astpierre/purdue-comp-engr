###############################################################################
#   Author:	Andrew St. Pierre
#   email: 	astpier@purdue.edu
#   ID: 	ee364b17
#   Date: 	Tuesday, April 09, 2019
###############################################################################

import os
import re
from pprint import pprint as pp
from measurement import calculateDistance

# Data path
DataPath=os.path.expanduser('~ee364/DataFolder/Lab13')

# PART I
def getCost(sourceZip, destinationZip):
    destLat = ""
    destLon = ""
    sourceLat = ""
    sourceLon = ""

    with open(os.path.join(DataPath, "coordinates.dat")) as f:
        lines = f.readlines()
    pattern=r"([\.\-\+\d]+)"
    for line in lines:
        line = line.split(",")
        zip = line[0].strip("\"").strip(",").strip("\"").strip(" ").strip("\"").strip(" ")

        if(zip == str(sourceZip)):
            sourceLat = line[2].strip("\"").strip(",").strip("\"").strip(" ").strip("\"").strip(" ")
            matches = re.search(pattern, sourceLat)
            sourceLat = matches.group(0)
            sourceLon = line[3].strip("\"").strip(",").strip("\"").strip(" ").strip("\"").strip(" ")
            matches = re.search(pattern, sourceLon)
            sourceLon = matches.group(0)
            if(destLat != ""):
                break
        if(zip == str(destinationZip)):
            destLat = line[2].strip("\"").strip(",").strip("\"").strip(" ").strip("\"").strip(" ")
            matches = re.search(pattern, destLat)
            destLat = matches.group(0)
            destLon = line[3].strip("\"").strip(",").strip("\"").strip(" ").strip("\"").strip(" ")
            matches = re.search(pattern, destLon)
            destLon = matches.group(0)
            if (sourceLat != ""):
                break
    try:
        sourceTuple = (float(sourceLat), float(sourceLon))
        destTuple = (float(destLat), float(destLon))
        miles = calculateDistance(sourceTuple, destTuple)
        return round((miles * 0.01), 2)
    except ValueError:
        return round((0.00),2)

def loadPackages( ):
    packageCompanies = set()
    packageGroups = []
    with open(os.path.join(DataPath, "packages.dat")) as f:
        lines = f.readlines()
        lines = lines[1:]
    for line in lines:
        pattern = r"^\"([^\"]+)\"[\s,]+\"([^\"]+)\"[\s,]+\"([^\"]+)\"$"
        matches = re.search(pattern, line)
        company= matches.group(1)
        sourceAddr = matches.group(2)
        destAddr = matches.group(3)
        newPackage=Package(company, sourceAddr, destAddr)

        if company not in packageCompanies:
            packageCompanies.add(company)
            newPackageGroup = PackageGroup(company.strip(" "), [newPackage])
            packageGroups.append(newPackageGroup)
        else:
            for pg in packageGroups:
                if pg.company == company:
                    pg = pg + newPackage
                    break

    packageGroups=sorted(packageGroups, key=lambda packageGroup:packageGroup.company)
    return packageGroups

class Package:
    def __init__(self, companyName, sourceAddr, destAddr):
        self.company = companyName
        self.source = sourceAddr
        self.destination = destAddr
        self.calculateCost( )
    def calculateCost(self):
        pattern = r"(\d{5})$"
        self.zipSource = re.search(pattern, self.source)
        self.zipDest = re.search(pattern, self.destination)
        self.zipSource = self.zipSource.group(1)
        self.zipDest = self.zipDest.group(1)
        self.cost = getCost(self.zipSource, self.zipDest)
    def __str__(self):
        return f"{self.zipSource} => {self.zipDest}, Cost = ${self.cost}"
    def __lt__(self, other):
        if not isinstance(other, Package):
            raise TypeError("Argument must be a member of the Package class.")
        if self.cost < other.cost:
            return True
        return False
    def __le__(self, other):
        if not isinstance(other, Package):
            raise TypeError("Argument must be a member of the Package class.")
        if self.cost <= other.cost:
            return True
        return False
    def __eq__(self, other):
        if not isinstance(other, Package):
            raise TypeError("Argument must be a member of the Package class.")
        if self.cost == other.cost:
            return True
        return False
    def __ne__(self, other):
        if not isinstance(other, Package):
            raise TypeError("Argument must be a member of the Package class.")
        if self.cost != other.cost:
            return True
        return False
    def __gt__(self, other):
        if not isinstance(other, Package):
            raise TypeError("Argument must be a member of the Package class.")
        if self.cost > other.cost:
            return True
        return False
    def __ge__(self, other):
        if not isinstance(other, Package):
            raise TypeError("Argument must be a member of the Package class.")
        if self.cost >= other.cost:
            return True
        return False
    def __add__(self, other):
        if not isinstance(other, Package):
            raise TypeError("Argument must be a member of the Package class.")
        if(self.company != other.company):
            raise ValueError("Argument must have the same company name")
        return PackageGroup(self.company, [self, other])

class PackageGroup:
    # special methods
    def __init__(self, companyName, packageInstances):
        # attributes -- member vars -- fields -- properties
        self.company = companyName
        self._validatePackages(packageInstances)
        self.calculateCost( )
    def _validatePackages(self, packageInstances):
        for p in packageInstances:
            if not isinstance(p, Package):
                raise TypeError("The argument must be an instance of the 'Package' Class")
        self.packages = sorted(packageInstances, reverse=True, key=lambda package: package.cost)
    def __str__(self):
        formattedSize="{:0>3}".format(len(self.packages))
        return f"{self.company}, {formattedSize} Shipments, Cost = ${round(self.cost, 2)}"
    def calculateCost(self):
        self.cost = 0.0
        for package in self.packages:
            self.cost+=package.cost
    def getByZip(self, zipSet):
        if len(zipSet) == 0:
            raise ValueError("The set of zipcodes must not be empty.")
        relevantPackages = []
        for package in self.packages:
            if package.zipDest in zipSet:
                relevantPackages.append(package)
            elif package.zipSource in zipSet:
                relevantPackages.append(package)
        relevantPackages = sorted(relevantPackages, reverse=True)
        return relevantPackages
    def getByState(self, stateSet):
        if len(stateSet) == 0:
            raise ValueError("The set of states must not be empty.")
        relevantPackages = []
        for package in self.packages:
            stateSrc = getStateByZip(package.zipSource)
            stateDest = getStateByZip(package.zipDest)
            if stateSrc in stateSet:
                relevantPackages.append(package)
            elif stateDest in stateSet:
                relevantPackages.append(package)
        relevantPackages = sorted(relevantPackages, reverse=True)
        return relevantPackages
    def getByCity(self, citySet):
        if len(citySet) == 0:
            raise ValueError("The set of cities must not be empty.")
        relevantPackages = []
        for package in self.packages:
            citySrc = getCityByZip(package.zipSource)
            cityDest = getCityByZip(package.zipDest)
            if citySrc in citySet:
                relevantPackages.append(package)
            elif cityDest in citySet:
                relevantPackages.append(package)
        relevantPackages = sorted(relevantPackages, reverse=True)
        return relevantPackages
    def __contains__(self, item):
        if not isinstance(item, Package):
            raise TypeError("Argument must be a member of the Package class.")
        for package in self.packages:
            if( package.source == item.source and
                package.destination == item.destination and
                package.company == item.company and
                package.cost == item.cost): return True
        return False
    def __add__(self, other):
        if not isinstance(other, Package):
            raise TypeError("Argument must be a member of the Package class.")
        if(self.company != other.company):
            raise ValueError("Argument must have the same company name")
        if(other in self): return self
        else:
            self.packages.append(other)
            self.calculateCost()
            self.packages = sorted(self.packages, reverse=True, key=lambda package: package.cost)
            return self

def getStateByZip(zipcode):
    with open(os.path.join(DataPath, "coordinates.dat")) as f:
        lines = f.readlines()
    pattern=r"\""+zipcode+r"\".+\"([A-Z]{2})\""
    for line in lines:
        match = re.search(pattern, line)
        if match:
            return match.group(1).strip("\'")
def getCityByZip(zipcode):
    with open(os.path.join(DataPath, "coordinates.dat")) as f:
        lines = f.readlines()
    pattern=r"\""+zipcode+r"\".+\"([A-Z\sa-z]+)\".+\"([A-Z\sa-z]+)\"$"
    for line in lines:
        match = re.search(pattern, line)
        if match:
            return match.group(1)
def getMaxCost():
    with open(os.path.join(DataPath, "coordinates.dat")) as f:
        lines = f.readlines()
        lines = lines[1:]
    maxCost = 0.00
    zipList = []
    for line in lines:
        line = line.split(",")
        zip = line[0].strip("\"").strip(",").strip("\"").strip(" ").strip("\"").strip(" ")
        zipList.append(zip)
    zipsH = sorted(zipList, reverse=True)
    zipsL = sorted(zipList, reverse=False)
    maxCost = 0.00
    for i in zipsH[:100]:
        for j in zipsL[:100]:
            tmp = getCost(i, j)
            if maxCost < tmp:
                maxCost = tmp
                maxZips = tuple([i,j])
    return maxZips


# Test methods
def __TEST_1( ):
    print("TEST 1: ")
    pgs = loadPackages()
    for pg in pgs:
        for p in pg.packages:
            if p in pg:
                pp("True")
def __TEST_2():
    pp(getMaxCost())


if __name__ == "__main__":
    #__TEST_1()
    __TEST_2()
