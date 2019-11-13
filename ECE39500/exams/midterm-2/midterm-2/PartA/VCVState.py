from CompilerState import CompilerState
from StateFactory import StateFactory
import sys

class VCVState(CompilerState):
    INT_MIN = -sys.maxint - 1

    def __init__(self, compiler):
        self.compiler = compiler
        return
    
    def comma(self):
        print("Parsing VCVState, expected int, found ,")
        self.compiler.state = StateFactory.getState("ErrorState")

    def value(self, s):
        self.compiler.valueCount += 1
        self.compiler.values[self.compiler.valueCount] = int(s)
        self.compiler.state = StateFactory.getState("CVState")

    def eol(self):
        print(f"Parsing VCVState, expected value, found eol")
        self.compiler.state = StateFactory.getState("ErrorState")

    def eof(self):
        print("Parsing VCVState, expected value, found eof")
        self.compiler.state = StateFactory.getState("ErrorState")
    
    def __str__(self):
        return "VCVState"