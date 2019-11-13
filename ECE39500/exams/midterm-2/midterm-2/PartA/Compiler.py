from CompilerState import CompilerState
from StateFactory import StateFactory
from AddState import AddState
from CVCVState import CVCVState
from InitState import InitState
from EofState import EofState
from ErrorState import ErrorState
from VCVState import VCVState
import sys

class Compiler():
    INT_MIN = -sys.maxint - 1

    def __init__(self):
        self.DEBUG = False
        self.valueCount = -1
        self.values = {INT_MIN, INT_MIN, INT_MIN}
        self.targetState = None
        self.state = None
        return

    def compiler(self, fileName):
        self.state = StateFactory.getState("InitState")
        


    def getState(self, state):
        return self.states[state]
