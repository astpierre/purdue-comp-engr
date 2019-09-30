###############################################################################
#   Author:	Andrew St. Pierre
#   email: 	astpier@purdue.edu
#   ID: 	ee364b17
#   Date: 	Tuesday, February 26, 2019
###############################################################################

import os
import sys
from pprint import pprint as pp

class Rectangle:
    # special methods
    def __init__(self, llPoint, urPoint):
        # attributes -- member vars -- fields -- properties
        self._validateInput(llPoint, urPoint)

    def _validateInput(self, llPoint, urPoint):
        x_ll = llPoint[0]
        x_ur = urPoint[0]
        y_ll = llPoint[1]
        y_ur = urPoint[1]
        if x_ll > x_ur:
            raise ValueError("x_ll must be less than x_ur.")
        if y_ll > y_ur:
            raise ValueError("y_ll must be less than y_ur.")
        # passes checks, initialize variables
        self.lowerLeft = llPoint
        self.upperRight = urPoint
    def isSquare(self):
        x_ll = self.lowerLeft[0]
        x_ur = self.upperRight[0]
        y_ll = self.lowerLeft[1]
        y_ur = self.upperRight[1]
        if (x_ur - x_ll) == (y_ur - y_ll):
            return True
        else: return False
    def intersectsWith(self, rect):
        lLeft = [rect.lowerLeft[0], rect.lowerLeft[1]]
        lRight = [rect.upperRight[0], rect.lowerLeft[1]]
        uLeft = [rect.lowerLeft[0], rect.upperRight[1]]
        uRight = [rect.upperRight[0], rect.upperRight[1]]
        if self.lowerLeft[0] < lLeft[0] < self.upperRight[0]:
            if self.lowerLeft[1] < lLeft[1] < self.upperRight[1]:
                return True
        if self.lowerLeft[0] < lRight[0] < self.upperRight[0]:
            if self.lowerLeft[1] < lRight[1] < self.upperRight[1]:
                return True
        if self.lowerLeft[0] < uLeft[0] < self.upperRight[0]:
            if self.lowerLeft[1] < uLeft[1] < self.upperRight[1]:
                return True
        if self.lowerLeft[0] < uRight[0] < self.upperRight[0]:
            if self.lowerLeft[1] < uRight[1] < self.upperRight[1]:
                return True
        return False
    def __eq__(self, rect2):
        if not isinstance(rect2, Rectangle):
            raise TypeError("Must only use == operator when comparing two Rectangle objects.")
        if self.upperRight == rect2.upperRight:
            if self.lowerLeft == rect2.lowerLeft:
                return True
        return False
class Circle:
    def __init__(self, center, radius):
        # attributes -- member vars -- fields -- properties
        self._validateInput(center, radius)
    def _validateInput(self, center, radius):
        if radius <= 0.0:
            raise ValueError("Circle radius must be > 0.00")
        self.radius = radius
        self.center = center

# Test methods
def __TEST_1( ):
    # test error throw when validating coordinates
    pp("TEST-1")
    coord1 = (1.0 , 4.0)
    coord2 = (0.9 , 5.0)
    R1 = Rectangle(coord1, coord2)
def __TEST_2( ):
    # test proper initialization
    pp("TEST-2")
    coord1 = (1.0 , 4.0)
    coord2 = (1.9 , 5.0)
    R1 = Rectangle(coord1, coord2)
def __TEST_3( ):
    # test isSquare (true)
    pp("TEST-3")
    coord1 = (1.0 , 1.0)
    coord2 = (2.0 , 2.0)
    R1 = Rectangle(coord1, coord2)
    if R1.isSquare():
        pp("Success, R1 is a square.")
    else: pp("Failure, R1 is a square.")
def __TEST_4( ):
    # test isSquare (false)
    pp("TEST-4")
    coord1 = (1.0 , 4.0)
    coord2 = (1.9 , 5.0)
    R1 = Rectangle(coord1, coord2)
    if R1.isSquare():
        pp("Failure, R1 is NOT a square.")
    else: pp("Success, R1 is NOT a square.")
def __TEST_5( ):
    # test operator overload == (false)
    pp("TEST-5")
    coord1 = (1.0 , 4.0)
    coord2 = (1.9 , 5.0)
    R1 = Rectangle(coord1, coord2)
    coord3 = (1.0 , 1.0)
    coord4 = (2.0 , 2.0)
    R2 = Rectangle(coord3, coord4)
    if R1 == R2:
        pp("Failure, R1 != R2.")
    else:
        pp("Success, R1 != R2.")
def __TEST_6( ):
    # test operator overload == (true)
    pp("TEST-6")
    coord1 = (1.0 , 4.0)
    coord2 = (1.9 , 5.0)
    R1 = Rectangle(coord1, coord2)
    coord3 = (1.0 , 4.0)
    coord4 = (1.9 , 5.0)
    R2 = Rectangle(coord3, coord4)
    if R1 == R2:
        pp("Success, R1 == R2.")
    else:
        pp("Failure, R1 != R2.")
def __TEST_7( ):
    # test intersectsWith() (true)
    pp("TEST-7")
    coord1 = (1.0 , 4.0)
    coord2 = (1.9 , 5.0)
    R1 = Rectangle(coord1, coord2)
    coord3 = (1.1 , 4.1)
    coord4 = (1.9 , 5.1)
    R2 = Rectangle(coord3, coord4)
    if R1.intersectsWith(R2):
        pp("Success, R1 intersects with R2.")
    else:
        pp("Failure, R1 intersects with R2.")
def __TEST_8( ):
    # test intersectsWith() (true)
    pp("TEST-8")
    coord1 = (1.0 , 4.0)
    coord2 = (1.9 , 5.0)
    R1 = Rectangle(coord1, coord2)
    coord3 = (2.1 , 5.1)
    coord4 = (2.9 , 6.1)
    R2 = Rectangle(coord3, coord4)
    if not R1.intersectsWith(R2):
        pp("Success, R1 does NOT intersect with R2.")
    else:
        pp("Failure, R1 does NOT intersect with R2.")

if __name__ == "__main__":
    # Test calls
    #__TEST_1( )
    __TEST_2( )
    #__TEST_3( )
    #__TEST_4( )
    #__TEST_5( )
    #__TEST_6( )
    #__TEST_7( )
    #__TEST_8( )
