###############################################################################
#   Author:	Andrew St. Pierre
#   email: 	astpier@purdue.edu
#   ID: 	ee364b17
#   Date: 	Wednesday, March 27, 2019
###############################################################################

import os
import re
from pprint import pprint as pp
from measurement import calculateDistance

# Data path
DataPath=os.path.expanduser('~ee364/DataFolder/Lab10')

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
    packageList = []
    packageCompanies = set()
    packageGroups = []
    with open(os.path.join(DataPath, "packages.dat")) as f:
        lines = f.readlines()
        lines = lines[1:]
    for line in lines:
        pattern = r"\"([^\"]+).*\"{1}([^\"]+)\"{1}.*\"{1}([^\"]+)\""
        matches = re.search(pattern, line)
        company= matches.group(1)
        if company not in packageCompanies:
            packageCompanies.add(company)
        sourceAddr = matches.group(2)
        destAddr = matches.group(3)
        newPackage=Package(sourceAddr, destAddr)
        packageList.append([newPackage,company])
    for company in packageCompanies:
        companyGroup=[]
        for p in packageList:
            if p[1].strip(" ")==company.strip(" "):
                companyGroup.append(p[0])
        newPackageGroup = PackageGroup(company.strip(" "),companyGroup)
        packageGroups.append(newPackageGroup)
    packageGroups=sorted(packageGroups, key=lambda packageGroup:packageGroup.company)
    return packageGroups

class Package:
    # special methods
    def __init__(self, sourceAddr, destAddr):
        # attributes -- member vars -- fields -- properties
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
            if package.zipSource in zipSet:
                relevantPackages.append(package)
        relevantPackages = sorted(relevantPackages, reverse=True)
        return relevantPackages

# PART II
def getNumberPattern( ):
    pattern=r"((([1-2]{1}[0-9]{2})|([0-9]{1,2}))\.([1-2]{1}[0-9]{2}|[0-9]{1,2})\.([1-2]{1}[0-9]{2}|[0-9]{1,2})\.([1-2]{1}[0-9]{2}|[0-9]{1,2}))"
    return pattern



# Test methods
def __TEST_1( ):
    print("TEST 1: ")
    pp(getCost("99337", "35115"))
def __TEST_2( ):
    print("TEST 2: ")
    packageGroups= loadPackages()
    for pg in packageGroups:
        print(pg)
        for p in pg.packages:
            print(p)
def __TEST_3( ):
    print("TEST 3: ")
    packageGroups = loadPackages()
    for pg in packageGroups:
        ps = pg.getByZip(("99337", "78144","14304"))
        for p in ps:
            print(p)
def __TEST_4( ):
    pat = getNumberPattern()
    match=re.search(pat, "The IP is 215.68.0.94")
    print(match[0])
    match=re.search(pat, "512.189.260.33 is not valid, but 215.68.0.94 is valid")
    print(match[0])


if __name__ == "__main__":
    __TEST_1()
    __TEST_2()
    __TEST_3()
    __TEST_4()
