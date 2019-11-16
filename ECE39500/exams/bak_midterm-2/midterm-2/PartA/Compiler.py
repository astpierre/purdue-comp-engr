from CompilerState import CompilerState
from AddState import AddState
from CVCVState import CVCVState
from InitState import InitState
from EofState import EofState
from ErrorState import ErrorState
from VCVState import VCVState
import sys
import re

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
class Compiler():
    INT_MIN = -sys.maxsize - 1

    def __init__(self):
        self.DEBUG = False
        self.valueCount = -1
        self.values = (INT_MIN, INT_MIN, INT_MIN)
        self.targetState = None
        self.state = None
        return

    def compile(self, fileName):
        self.state = StateFactory.getState("InitState")
        with open(filename, "r") as f:
            lines = f.readlines()
        for line in lines:
            self.parseline(line)


    def parseline(self, line):
        if self.DEBUG:
            print(f"\nParsing input line: {line}")
        line = re.sub(r",", " , ", line)
        line = re.sub(r"\s+", " ", line)
        tokens = line.split(" ")
        for token in tokens:
            self.takeAction(token)
        self.state.eol()
        return
    
    def takeAction(token):
        commands = ("addi", "ld0", "add", "print", "exit")
        if token.isnumeric():
            self.state.value(token)
        elif token in commands:
            self.values[0] = INT_MIN
            self.values[1] = INT_MIN
            self.values[2] = INT_MIN
            self.valueCount = -1
            self.state.value(token)
        elif token == ",":
            self.state.comma()
        else:
            print(f"Unknown token :: {token} ::")
            self.state = StateFactory.getState("ErrorState")

