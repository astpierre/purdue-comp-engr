from AddState import AddState
from Compiler import *
from CompilerState import CompilerState
from CVCVState import CVCVState
from VCVState import  VCVState
from ErrorState import ErrorState
from InitState import InitState
from StateFactory import StateFactory
from EofState import EofState


def main(filename):
    compiler = Compiler()
    statefactory = StateFactory(compiler)
    compiler.compile(filename)