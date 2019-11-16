from CompilerState import CompilerState, StateFactory
import sys

class EofState(CompilerState):
    INT_MIN = -sys.maxsize - 1

    def __init__(self, compiler):
        self.compiler = compiler
        return
    
    def comma(self):
        print("Parsing EofState, expected eol, found ,")
        self.compiler.state = StateFactory.getState("ErrorState")

    def value(self):
        print("Parsing EofState, expected eol, found value")
        self.compiler.state = StateFactory.getState("ErrorState")

    def eol(self):
        pass

    def eof(self):
        print("Parsing EofState, expected value, found eof")
        self.compiler.state = StateFactory.getState("ErrorState")
    
    def __str__(self):
        return "EofState"