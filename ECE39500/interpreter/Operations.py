import sys, os, time
import struct
from pathlib import Path

class Push_c:
    def exe(self, obj):
        obj.sp += 1
        obj.rstack[obj.sp] = obj.mem[obj.pc+1]
        obj.pc += 2
        return None
