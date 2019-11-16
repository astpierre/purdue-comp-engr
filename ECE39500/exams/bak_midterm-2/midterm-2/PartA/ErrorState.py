from CompilerState import CompilerState
from StateFactory import StateFactory
import sys

class ErrorState(CompilerState):
    INT_MIN = -sys.maxsize - 1

    def __init__(self, compiler):
        self.compiler = compiler
        return
    
    def comma(self):
        print(f"In error state processing {self.compiler.targetState}, tossing ','")

    def value(self, s):
        print(f"In error state processing {self.compiler.targetState}, tossing {s}")

    def eol(self):
        print(f"In error state processing {self.compiler.targetState}, processing eol")
        self.compiler.targetState.eol()

    def eof(self):
        print(f"In error state processing {self.compiler.targetState}, eof found, terminating compiler")
    
    def __str__(self):
        return "ErrorState"