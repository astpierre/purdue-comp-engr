from CompilerState import CompilerState
from StateFactory import StateFactory
import sys

class CVCVState(CompilerState):
    INT_MIN = -sys.maxsize - 1

    def __init__(self, compiler):
        self.compiler = compiler
        return
    
    def comma(self):
        self.compiler.state = StateFactory.getState("VCVState")

    def value(self, s):
        print("Parsing CVCV, expected , found int {s}")
        self.compiler.state = StateFactory.getState("ErrorState")

    def eol(self):
        print(f"Parsing CVCV, expected value, found eol")
        self.compiler.state = StateFactory.getState("ErrorState")

    def eof(self):
        print("Parsing InitState, expected value, found eof")
        self.compiler.state = StateFactory.getState("ErrorState")
    
    def __str__(self):
        return "CVCVState"