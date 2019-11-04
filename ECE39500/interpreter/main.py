#!/usr/bin/python3

import sys, os, time
import struct
from pathlib import Path

from Bytecode import Bytecode
from Interpreter import Interpreter

from util import get_opcodes




def main(filename):
    interpreter = Interpreter(filename)
    interpreter.run_program()
    exit(0)






if __name__=="__main__":
    main("tests/Test_Binaries/Basics.bin")
