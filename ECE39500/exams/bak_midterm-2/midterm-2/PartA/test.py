from Compiler import *
from StateFactory import *
"""
from CVCVState import CVCVState
from VCVState import  VCVState
from ErrorState import ErrorState
from InitState import InitState
from AddState import AddState
from EofState import EofState
"""

def main(filename):
    compiler = Compiler()
    statefactory = StateFactory(compiler)
    compiler.compile(filename)