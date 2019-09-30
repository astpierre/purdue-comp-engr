###############################################################################
#   Author:	Andrew St. Pierre
#   email: 	astpier@purdue.edu
#   ID: 	ee364b17
#   Date: 	Saturday, March 02, 2019
###############################################################################

import os
import sys
import itertools
from enum import Enum
from copy import deepcopy
from collections import UserList
from pprint import pprint as pp

# Required enums
class DataClass(Enum):
    Class1 = 1
    Class2 = 2

# Required methods / classes
class Datum:
    # special methods
    def __init__(self, *args):
        # attributes -- member vars -- fields -- properties
        self._storage = ()
        self.numPoints = 0
        self._validateArgs(*args)

    def _validateArgs(self, *args):
        listargs = []
        for item in [*args]:
            if type(item) != type(1.0):
                raise TypeError("Arguments must be floats.")
            else:
                listargs.append(item)
                self.numPoints += 1
        self._storage = tuple(listargs)

    def __str__(self):
        formattedPoints = []
        for item in self._storage:
            item = "{:.2f}".format(item)
            formattedPoints.append(item)
        msg = "(%s"%', '.join([str(item) for item in formattedPoints])+")"
        return msg

    def __hash__(self):
        return hash(self._storage)

    def distanceFrom(self, D2):
        if not isinstance(D2, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        maxLen = max(len(self._storage), len(D2._storage))
        distance_squared = 0.00
        for i in range(maxLen):
            try:
                p1 = self._storage[i]
            except:
                p1 = 0.0
            try:
                p2 = D2._storage[i]
            except:
                p2 = 0.0
            distance_squared += (p1-p2)**2
        return distance_squared**(0.5)

    def clone(self):
        clone = deepcopy(self)
        return clone

    def __contains__(self, value):
        if type(value) != type(1.0):
            raise TypeError("Membership check must only be done with a float.")
        return value in self._storage

    def __len__(self):
        return len(self._storage)

    def __iter__(self):
        return iter(self._storage)

    def __neg__(self):
        negPoints = [-v for v in self._storage]
        NegD = Datum(*negPoints)
        return NegD

    def __getitem__(self, index):
        return self._storage[index]

    def __add__(self, other):
        if isinstance(other, Datum):
            maxLen = max(len(self._storage), len(other._storage))
            sumPoints = []
            for i in range(maxLen):
                try:
                    p1 = self._storage[i]
                except:
                    p1 = 0.0
                try:
                    p2 = other._storage[i]
                except:
                    p2 = 0.0
                sumPoints.append(p1+p2)
            SumDatum = Datum(*sumPoints)
            return SumDatum
        elif type(other) == type(1.0):
            sumPoints = [v+other for v in self._storage]
            SumDatum = Datum(*sumPoints)
            return SumDatum
        else:
            raise TypeError("Argument must be instance of Datum class or of type float.")

    def __sub__(self, other):
        if isinstance(other, Datum):
            maxLen = max(len(self._storage), len(other._storage))
            diffPoints = []
            for i in range(maxLen):
                try:
                    p1 = self._storage[i]
                except:
                    p1 = 0.0
                try:
                    p2 = other._storage[i]
                except:
                    p2 = 0.0
                diffPoints.append(p1-p2)
            DiffDatum = Datum(*diffPoints)
            return DiffDatum
        elif type(other) == type(1.0):
            diffPoints = [v-other for v in self._storage]
            DiffDatum = Datum(*diffPoints)
            return DiffDatum
        else:
            raise TypeError("Argument must be instance of Datum class or of type float.")

    def __mul__(self, other):
        if type(other) != type(1.0):
            raise TypeError("Argument must be of type float.")
        prodPoints = [v*other for v in self._storage]
        ProdDatum = Datum(*prodPoints)
        return ProdDatum

    def __truediv__(self, other):
        if type(other) != type(1.0):
            raise TypeError("Argument must be of type float.")
        divPoints = [v/other for v in self._storage]
        DivDatum = Datum(*divPoints)
        return DivDatum

    def __lt__(self, other):
        if not isinstance(other, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        Origin = Datum(0.0, 0.0, 0.0) # auto-extends
        dist1 = self.distanceFrom(Origin)
        dist2 = other.distanceFrom(Origin)
        if dist1 < dist2: return True
        else: return False

    def __le__(self, other):
        if not isinstance(other, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        Origin = Datum(0.0, 0.0, 0.0) # auto-extends
        dist1 = self.distanceFrom(Origin)
        dist2 = other.distanceFrom(Origin)
        if dist1 <= dist2: return True
        else: return False

    def __eq__(self, other):
        if not isinstance(other, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        Origin = Datum(0.0, 0.0, 0.0) # auto-extends
        dist1 = self.distanceFrom(Origin)
        dist2 = other.distanceFrom(Origin)
        if dist1 == dist2: return True
        else: return False

    def __ne__(self, other):
        if not isinstance(other, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        Origin = Datum(0.0, 0.0, 0.0) # auto-extends
        dist1 = self.distanceFrom(Origin)
        dist2 = other.distanceFrom(Origin)
        if dist1 != dist2: return True
        else: return False

    def __gt__(self, other):
        if not isinstance(other, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        Origin = Datum(0.0, 0.0, 0.0) # auto-extends
        dist1 = self.distanceFrom(Origin)
        dist2 = other.distanceFrom(Origin)
        if dist1 > dist2: return True
        else: return False

    def __ge__(self, other):
        if not isinstance(other, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        Origin = Datum(0.0, 0.0, 0.0) # auto-extends
        dist1 = self.distanceFrom(Origin)
        dist2 = other.distanceFrom(Origin)
        if dist1 >= dist2: return True
        else: return False
class Data(UserList):
    def __init__(self, datumList=None):
        if datumList == None:
            UserList.__init__(self, [])
        else:
            self._validateArgs(datumList)
    def _validateArgs(self, datumList):
        for datum in datumList:
            if not isinstance(datum, Datum):
                raise TypeError("Argument must be a member of the Datum class.")
        UserList.__init__(self, datumList)

    def computeBounds(self):
        maxDim = -1
        for datum in self.data:
            if datum.numPoints > maxDim:
                maxDim = datum.numPoints
        minYield, maxYield = [], []
        for i in range(maxDim):
            currMin, currMax = None, None
            for datum in self.data:
                try:
                    temp = datum[i]
                except:
                    temp = 0.0
                if(currMax == None) or (temp > currMax):
                    currMax = temp
                if(currMin == None) or (temp < currMin):
                    currMin = temp
            maxYield.append(currMax)
            minYield.append(currMin)
        minDatum = Datum(*minYield)
        maxDatum = Datum(*maxYield)
        return tuple([minDatum, maxDatum])

    def computeMean(self):
        maxDim = -1
        numDatum = 0
        for datum in self.data:
            if datum.numPoints > maxDim:
                maxDim = datum.numPoints
            numDatum+=1
        meanYield = []
        for i in range(maxDim):
            sumPoints = 0.0
            for datum in self.data:
                try:
                    temp = datum[i]
                except:
                    temp = 0.0
                sumPoints += temp
            meanYield.append(sumPoints/float(numDatum))
        return Datum(*meanYield)

    def append(self, item):
        if not isinstance(item, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        super().append(item)
    def count(self, item):
        if not isinstance(item, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        return super().count(item)
    def index(self, item):
        if not isinstance(item, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        return super().index(item)
    def insert(self, idx, item):
        if not isinstance(item, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        super().insert(idx, item)
    def remove(self, item):
        if not isinstance(item, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        super().remove(item)
    def __setitem__(self, idx, item):
        if not isinstance(item, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        super().__setitem__(idx, item)
    def extend(self, item):
        if not isinstance(item, Datum):
            raise TypeError("Argument must be a member of the Datum class.")
        super().append(item)
class DataClassifier():
    def __init__(self, group1, group2):
        # attributes -- member vars -- fields -- properties
        self._group1 = self._validateArgs(group1)
        self._group2 = self._validateArgs(group2)

    def _validateArgs(self, group):
        if not isinstance(group, Data):
            raise TypeError("Argument must be a member of the Data class.")
        if len(group.data) == 0:
            raise ValueError("Data object must not be empty.")
        return group

    def classify(self, other):
        if not isinstance(other, Datum):
            raise TypeError("Argument must be a member of the Datum class.")

        G1mean = self._group1.computeMean()
        G2mean = self._group2.computeMean()
        G1Dist = other.distanceFrom(G1mean)
        G2Dist = other.distanceFrom(G2mean)
        if G1Dist < G2Dist:
            return DataClass(1)
        else: return DataClass(2)


# Test methods
def __TEST_1( ):
    print("TEST 1: ")
    d1 = Datum(10.1, 5.00, 52.2, -5.00000)
    d2 = Datum(10.1, 5.00, 52.2, -5.00000, -2.0, -2.0, 2.0, 2.0)
    print(d1)
    print(d2)
    print(d1.distanceFrom(d2)) # out: 4.0, correct!
def __TEST_2( ):
    print("TEST 2: ")
    d1 = Datum(10.1, 5.00, 52.2, -5.00000)
    d2 = d1.clone()
    print(d1)
    print(d2)
    print(d1.distanceFrom(d2)) # out: 0.0, correct!
def __TEST_3( ):
    print("TEST 3: ")
    d1 = Datum(10.1, 5.00, 52.2, -5.00000)
    print(d1)
    if 5.00 in d1: pp("test pass")
    else: pp("test fail")
    if len(d1) == 4: pp("test pass")
    else: pp("test fail")
def __TEST_4( ):
    print("TEST 4: ")
    d1 = Datum(10.1, 5.00, 52.2, -5.00000)
    print(d1)
    for v in d1:
        pp(f"Value: {v}")
def __TEST_5( ):
    print("TEST 5: ")
    d1 = Datum(10.1, 5.00, 52.2, -5.00000)
    d2 = -d1
    print(d1)
    print(d2)
def __TEST_6( ):
    print("TEST 6: ")
    d1 = Datum(10.1, 5.00, 52.2, -5.00000)
    print(d1)
    print(d1[0])
def __TEST_7( ):
    print("TEST 7: ")
    d1 = Datum(10.1, 5.00, 52.2, -5.00000)
    d2 = Datum(10.1, 5.00, 52.2, -5.00000)
    print(d1)
    Sum1 = d1 + 1.0
    print(Sum1)
    Sum2 = d1 + d2
    print(Sum2)
def __TEST_8( ):
    print("TEST 8: ")
    d1 = Datum(10.1, 5.00, 52.2, -5.00000)
    d2 = Datum(10.1, 5.00, 52.2, -5.00000)
    print(d1)
    Diff1 = d1 - 1.0
    print(Diff1)
    Diff2 = d1 - d2
    print(Diff2)
def __TEST_9( ):
    print("TEST 9: ")
    d1 = Datum(10.1, 5.00, 52.2, -5.00000)
    print(d1)
    Prod1 = d1 * 2.0
    print(Prod1)
    Div1 = d1 / -2.0
    print(Div1)
def __TEST_10( ):
    D1 = Datum(1.0, 2.0, 4.0)
    D2 = Datum(-1.0, -2.0, -4.1)
    if not D1 == D2: pp("test pass: =")
    if D1 <= D2: pp("test pass: =<")
    if not D1 >= D2: pp("test pass: =>")
    if not D1 > D2: pp("test pass: >")
    if D1 < D2: pp("test pass: <")
def __TEST_11( ):
    print("TEST 11: ")
    d1 = Datum(10.1, 5.00, 52.2, -5.00000, 0.0, -1.0)
    d2 = Datum(-2.0, -2.0, 2.0, 2.0)
    print(d1)
    print(d2)
    D = Data([d1,d2])
    minY, maxY = D.computeBounds()
    print(f"min bounds: {minY}")
    print(f"max bounds: {maxY}")
def __TEST_12( ):
    print("TEST 12: ")
    d1 = Datum(10.0, 15.00, 10.0, 15.00000)
    d2 = Datum(10.0, 5.00, 10.0, 5.00000, 0.00)
    print(d1)
    print(d2)
    D = Data([d1,d2])
    meanY = D.computeMean()
    print(f"mean: {meanY}")
def __TEST_13( ):
    print("TEST 13: ")
    d1 = Datum(10.0, 15.00, 10.0, 15.00000)
    d2 = Datum(10.0, 5.00, 10.0, 5.00000, 0.00)
    d3 = Datum(10.0, 5.00)
    print(d1)
    print(d2)
    D = Data([d1,d2])
    #meanY = D.computeMean()
    D[0] = d2
    print(D.count(d2))
    D.extend(d3)
    for i in D.data:
        print(i)
    D.insert(0, d2)
    print(D.count(d2))
    for i in D.data:
        print(i)
def __TEST_14( ):
    print("TEST 14: ")
    d1 = Datum(10.0, 15.00, 10.0, 15.00000)
    d2 = Datum(11.0, 16.00, 10.0, 15.00000)

    d3 = Datum(0.0, 1.00, 1.0, 1.00000, 0.00)
    d4 = Datum(2.0, 1.00, 0.0, 3.00000, 0.00)


    d = Datum(1.0, 0.00, 1.0, 0.00000, 1.00)

    D1 = Data([d1,d2])
    D2 = Data([d3,d4])

    DC = DataClassifier(D1, D2)

    print(DC.classify(d)) # output: DataClass.Class2

if __name__ == "__main__":
    # Test calls
    '''
    __TEST_1( )
    __TEST_2( )
    __TEST_3( )
    __TEST_4( )
    __TEST_5( )
    __TEST_6( )
    __TEST_7( )
    __TEST_8( )
    __TEST_9( )
    __TEST_10( )
    __TEST_11( )
    __TEST_12( )
    __TEST_14( )
    '''
