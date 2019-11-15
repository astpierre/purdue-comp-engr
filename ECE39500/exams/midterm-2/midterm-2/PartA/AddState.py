from CompilerState import CompilerState
from StateFactory import StateFactory
import sys

class AddState(CompilerState):
    INT_MIN = -sys.maxint - 1

    def __init__(self, compiler):
        self.compiler = compiler
        return
    
    def comma(self):
        self.compiler.state = StateFactory.getState("ErrorState")

    def value(self, s):
        self.compiler.valueCount += 1
        self.compiler.values[self.compiler.valueCount] = int(str)
        self.compiler.state = StateFactory.getState("CVCVState")

    def eol(self):
        if (self.validOperands(self.compiler.values, 3)):
            print(f"reg[{self.compiler.values[2]}] = reg[{self.compiler.values[0]}] + reg[{self.compiler.values[1]}]")
        else:
            self.printInvalidOperands(self.compiler.values, 3)
        self.compiler.state = StateFactory.getState("InitState")

    def eof(self):
        print("Parsing AddState, expected value, found eof")
        self.compiler.state = StateFactory.getState("ErrorState")
    
    def __str__(self):
        return "AddState"