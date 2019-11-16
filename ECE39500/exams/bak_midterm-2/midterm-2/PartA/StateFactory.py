from AddState import AddState
from CVCVState import CVCVState
from InitState import InitState
from EofState import EofState
from ErrorState import ErrorState
from VCVState import VCVState
import sys

class StateFactory():
    INT_MIN = -sys.maxsize - 1

    def __init__(self, compiler):
        self.compiler = compiler
        self.states = {
            "add": AddState(compiler),
            "CVCVState": CVCVState(compiler),
            "EofState": EofState(compiler),
            "ErrorState": ErrorState(compiler),
            "InitState": InitState(compiler),
            "VCVState": VCVState(compiler),
        }
        return
    
    def getState(self, state):
        return self.states[state]
