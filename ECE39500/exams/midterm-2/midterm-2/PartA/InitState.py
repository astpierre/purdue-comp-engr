from CompilerState import CompilerState
from StateFactory import StateFactory
import sys

class InitState(CompilerState):
    INT_MIN = -sys.maxint - 1

    def __init__(self, compiler):
        self.compiler = compiler
        return
    
    def comma(self):
        print("Parsing InitState, expected command, found ,")
        self.compiler.state = StateFactory.getState("ErrorState")

    def value(self, s):
        self.compiler.state = StateFactory.getState(s)
        self.compiler.targetState = self.compiler.state
        if self.compiler.DEBUG:
            print(f"Init to {self.compiler.targetState} transition")

    def eol(self):
        print(f"Error in InitState, expected value, found eol")
        self.compiler.state = StateFactory.getState("ErrorState")

    def eof(self):
        print("Parsing InitState, expected value, found eof")
        self.compiler.state = StateFactory.getState("ErrorState")
    
    def __str__(self):
        return "InitState"