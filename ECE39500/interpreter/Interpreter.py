import sys, os, time
import struct
from pathlib import Path

from Bytecode import Bytecode
from Operations import *

from util import get_opcodes


class Interpreter():
    def __init__(self, compiled_code):
        self.is_dev = False
        self.compiled_code = compiled_code
        self.opcodes = get_opcodes()
        self.rstack = ['\0','\0','\0','\0']
        self.sp = -1
        self.fpstack = ['\0','\0','\0','\0']
        self.fpsp = -1
        self.pc = 0
        self.mem = self.read_program()


    def read_program(self):
        return [ byte for byte in Path(self.compiled_code).read_bytes() ]


    def __is_opcode(self, byte):
        return byte in self.opcodes.keys()


    def get_bytecode(self):
        byte = self.mem[self.pc]
        if self.is_dev: print(self.opcodes[byte])
        
        if self.opcodes[byte] == "pushc":
            return Push_c()
        elif self.opcodes[byte] == "pushs":
            return Push_s()
        elif self.opcodes[byte] == "pushi":
            return Push_i()
        elif self.opcodes[byte] == "pushf":
            return Push_f()
        
        elif self.opcodes[byte] == "pushvc":
            return Push_vc()
        elif self.opcodes[byte] == "pushvs":
            return Push_vs()
        elif self.opcodes[byte] == "pushvi":
            return Push_vi()
        elif self.opcodes[byte] == "pushvf":
            return Push_vf()
        
        elif self.opcodes[byte] == "popm":
            return Pop_m()
        elif self.opcodes[byte] == "popv":
            return Pop_v()
        elif self.opcodes[byte] == "popa":
            return Pop_a()
        
        elif self.opcodes[byte] == "peekc":
            return Peek_c()
        elif self.opcodes[byte] == "peeks":
            return Peek_s()
        elif self.opcodes[byte] == "peeki":
            return Peek_i()
        elif self.opcodes[byte] == "peekf":
            return Peek_f()

        elif self.opcodes[byte] == "pokec":
            return Poke_c()
        elif self.opcodes[byte] == "pokes":
            return Poke_s()
        elif self.opcodes[byte] == "pokei":
            return Poke_i()
        elif self.opcodes[byte] == "pokef":
            return Poke_f()
        
        elif self.opcodes[byte] == "swp":
            return Swp()
        
        elif self.opcodes[byte] == "add":
            return Add()
        elif self.opcodes[byte] == "sub":
            return Sub()
        elif self.opcodes[byte] == "mul":
            return Mul()
        elif self.opcodes[byte] == "div":
            return Div()
        
        elif self.opcodes[byte] == "printc":
            return Print_c()
        elif self.opcodes[byte] == "prints":
            return Print_s()
        elif self.opcodes[byte] == "printi":
            return Print_i()
        elif self.opcodes[byte] == "printf":
            return Print_f()

        elif self.opcodes[byte] == "cmpe":
            return Cmpe()
        elif self.opcodes[byte] == "cmplt":
            return Cmplt()
        elif self.opcodes[byte] == "cmpgt":
            return Cmpgt()

        elif self.opcodes[byte] == "jmp":
            return Jmp()
        elif self.opcodes[byte] == "jmpc":
            return Jmpc()
        elif self.opcodes[byte] == "call":
            return Call()
        elif self.opcodes[byte] == "ret":
            return Ret()
        
        elif self.opcodes[byte] == "halt":
            return Halt()
        return None


    def run_program(self):
        runme = True
        while(runme):
            bc = self.get_bytecode()
            if bc.exe(self) == False:
                print(self)
                runme=False
    

    def __str__(self):
        return f"""\npc={self.pc}\nrstack={self.rstack}\tsp={self.sp}\nfpstack={self.fpstack}\tfpsp={self.fpsp}\n"""
