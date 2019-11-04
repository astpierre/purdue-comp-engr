import sys, os, time
import struct
from pathlib import Path

from Bytecode import Bytecode
from Operations import Push_c

from util import get_opcodes


class Interpreter():
    def __init__(self, compiled_code):
        self.compiled_code = compiled_code
        self.opcodes = get_opcodes()
        self.rstack = [0,0,0,0]
        self.sp = -1
        self.fpstack = [0,0,0,0]
        self.fpsp = -1
        self.pc = -1
        self.mem = self.read_program()

    def read_program(self):
        return [ byte for byte in Path(self.compiled_code).read_bytes() ]


    def __is_opcode(self, byte):
        return byte in self.opcodes.keys()


    def run_program(self):
        for byte in self.mem:
            if self.__is_opcode(byte):
                if self.opcodes[byte] == "pushc":
                    Push_c().exe(self)
                elif self.opcodes[byte] == "pushs":
                    Push_s().exe(self)
                elif self.opcodes[byte] == "pushi":
                    Push_i().exe(self)
                elif self.opcodes[byte] == "pushf":
                    Push_f().exe(self)
                
                elif self.opcodes[byte] == "pushvc":
                    Push_vc().exe(self)
                elif self.opcodes[byte] == "pushvs":
                    Push_vs().exe(self)
                elif self.opcodes[byte] == "pushvi":
                    Push_vi().exe(self)
                elif self.opcodes[byte] == "pushvf":
                    Push_vf().exe(self)
                
                elif self.opcodes[byte] == "popm":
                    Pop_m().exe(self)
                elif self.opcodes[byte] == "popv":
                    Pop_v().exe(self)
                elif self.opcodes[byte] == "popa":
                    Pop_a().exe(self)
                
                elif self.opcodes[byte] == "peekc":
                    Peek_c().exe(self)
                elif self.opcodes[byte] == "peeks":
                    Peek_s().exe(self)
                elif self.opcodes[byte] == "peeki":
                    Peek_i().exe(self)
                elif self.opcodes[byte] == "peekf":
                    Peek_f().exe(self)

                elif self.opcodes[byte] == "pokec":
                    Poke_c().exe(self)
                elif self.opcodes[byte] == "pokes":
                    Poke_s().exe(self)
                elif self.opcodes[byte] == "pokei":
                    Poke_i().exe(self)
                elif self.opcodes[byte] == "pokef":
                    Poke_f().exe(self)
                
                elif self.opcodes[byte] == "swp":
                    Swp().exe(self)
                
                elif self.opcodes[byte] == "add":
                    Add().exe(self)
                elif self.opcodes[byte] == "sub":
                    Sub().exe(self)
                elif self.opcodes[byte] == "mul":
                    Mul().exe(self)
                elif self.opcodes[byte] == "div":
                    Div().exe(self)
                
                elif self.opcodes[byte] == "printc":
                    Print_c().exe(self)
                elif self.opcodes[byte] == "prints":
                    Print_s().exe(self)
                elif self.opcodes[byte] == "printi":
                    Print_i().exe(self)
                elif self.opcodes[byte] == "printf":
                    Print_f().exe(self)
                
                elif self.opcodes[byte] == "halt":
                    Halt().exe(self)
            
            else:
                pass
    
    def __str__(self):
        return f"""rstack: {self.rstack}\tsp={self.sp}\nfpstack{self.fpstack}\tfpsp={self.fpsp}\n"""