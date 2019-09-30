###############################################################################
#   Author:	Andrew St. Pierre
#   email: 	astpier@purdue.edu
#   ID: 	ee364b17
#   Date: 	Tuesday, March 05, 2019
###############################################################################

import os
import sys

# Required methods / classes
class TimeSpan:
    # special methods
    def __init__(self, weeks, days, hours):
        # attributes -- member vars -- fields -- properties
        self.weeks = self._validateArg(weeks, 'W')
        self.days = self._validateArg(days, 'D')
        self.hours = self._validateArg(hours, 'H')
        self._checkMemberVars()

    def _checkMemberVars(self):
        if self.hours >= 24:
            self.days += self.hours // 24
            self.hours = self.hours % 24
        if self.days >= 7:
            self.weeks += self.days // 7
            self.days = self.days % 7

    def _validateArg(self, data, mode):
        if data < 0:
            raise ValueError("The arguments cannot be negative.")
        if mode == 'W':
            return data
        elif mode == 'D':
            if data >= 7:
                self.weeks += data // 7
                self._checkMemberVars()
                return data % 7
            else:
                return data
        elif mode == 'H':
            if data >= 24:
                self.days += data // 24
                return data % 24
            else:
                return data
        else:
            raise ValueError("Mode must be (W)eeks, (D)ays, or (H)ours.")

    def __str__(self):
        if self.weeks < 10:
            strWeeks = '0'+str(self.weeks)
        else: strWeeks = str(self.weeks)
        if self.hours < 10:
            strHours = '0'+str(self.hours)
        else: strHours = str(self.hours)
        return f"{strWeeks}W {self.days}D {strHours}H"

    def getTotalHours(self):
        return ((self.weeks*(7*24)) + (self.days*(24)) + (self.hours))

    def __add__(self, other):
        if isinstance(other, TimeSpan):
            sum_weeks = self.weeks + other.weeks
            sum_days = self.days + other.days
            sum_hours = self.hours + other.hours
            SumTimeSpan = TimeSpan(sum_weeks, sum_days, sum_hours)
            return SumTimeSpan
        else:
            raise TypeError("Argument must be instance of TimeSpan class.")

    def __mul__(self, scale):
        if(type(scale) == type(1)):
            if scale <= 0:
                raise ValueError("Argument must be greater than 0.")
            scale_weeks = self.weeks * scale
            scale_days = self.days * scale
            scale_hours = self.hours * scale
            ScaledTimeSpan = TimeSpan(scale_weeks, scale_days, scale_hours)
            return ScaledTimeSpan
        else:
            raise TypeError("Argument must be an integer.")

# Test methods
def __TEST_1( ):
    print("TEST 1: ")
    ts1 = TimeSpan(1, 6, 24)
    print(ts1) # good 02W 0D 00H
    print(ts1.getTotalHours()) # good
def __TEST_2( ):
    print("TEST 2: ")
    ts1 = TimeSpan(1, 6, 25)
    print(ts1) # good 02W 0D 00H
    ts2 = TimeSpan(4, 6, 23)
    print(ts2) # good 04W 6D 23H
    print(ts1+ts2) # good 07W 0D 00H
def __TEST_3( ):
    print("TEST 3: ")
    ts1 = TimeSpan(100, 6, 25)
    print(ts1) # good 02W 0D 00H
    s1ts1 = ts1 * 3
    s2ts1 = ts1 * 3
    if s1ts1.getTotalHours() != s2ts1.getTotalHours():
        print("test fail")
    else: print("test pass")
    print(s1ts1)
    print(s2ts1)

if __name__ == "__main__":
    # Test calls
    __TEST_1()
    __TEST_2()
    __TEST_3()