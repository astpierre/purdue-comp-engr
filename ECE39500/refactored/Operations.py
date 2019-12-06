import sys, os, time
import struct
from pathlib import Path
from util import *

class Push_c:
    def exe(self, obj):
        obj.sp += 1
        obj.rstack[obj.sp] = obj.mem[obj.pc+1]
        obj.pc += 2
        return True


class Push_s:
    def exe(self, obj):
        s = [obj.mem[obj.pc+1], obj.mem[obj.pc+2]]
        s = bytearray(s)
        s = struct.unpack("<h", s)
        s=s[0]
        obj.sp += 1
        obj.rstack[obj.sp] = s
        obj.pc += 3
        return True


class Push_i:
    def exe(self, obj):
        i = [obj.mem[obj.pc+1], obj.mem[obj.pc+2], obj.mem[obj.pc+3], obj.mem[obj.pc+4]]
        i = bytearray(i)
        i = struct.unpack("<i", i)
        i=i[0]
        obj.sp += 1
        try:
            obj.rstack[obj.sp] = i
        except IndexError:
            obj.rstack.append(i)

        obj.pc += 5
        return True


class Push_f:
    def exe(self, obj):
        f = [obj.mem[obj.pc+1], obj.mem[obj.pc+2], obj.mem[obj.pc+3], obj.mem[obj.pc+4]]
        f = bytearray(f)
        f = struct.unpack("<f", f)
        f = f[0]
        obj.sp += 1
        obj.rstack[obj.sp] = f
        obj.pc += 5
        return True


class Push_vc:
    def exe(self, obj):
        obj.rstack[obj.sp] = obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1]
        obj.pc += 1
        return None


class Push_vs:
    def exe(self, obj):
        obj.rstack[obj.sp] = obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1]
        obj.pc += 1
        return True


class Push_vi:
    def exe(self, obj):
        obj.rstack[obj.sp] = obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1]
        obj.pc += 1
        return True


class Push_vf:
    def exe(self, obj):
        obj.rstack[obj.sp] = obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1]
        obj.pc += 1
        return True


class Pop_m:
    def exe(self, obj):
        obj.sp -= obj.rstack[obj.sp] + 1
        obj.pc += 1
        return True


class Pop_v:
    def exe(self, obj):
        obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1] = obj.rstack[obj.sp-1]
        obj.sp -= 2
        obj.pc += 1
        return True


class Pop_a:
    def exe(self, obj):
        val_top = obj.rstack[obj.sp]
        for i in range(val_top-1):
            obj.rstack[obj.fpstack[obj.fpsp]+i+1] = obj.rstack[obj.sp-obj.rstack[obj.sp]+i]
        obj.sp = obj.fpstack[obj.fpsp] + obj.rstack[obj.sp]
        obj.pc += 1
        return True


class Peek_c:
    def exe(self, obj):
        obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp-1]+1] = obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1]
        obj.pc += 1
        return True


class Peek_s:
    def exe(self, obj):
        obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp-1]+1] = obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1]
        obj.pc += 1
        return True


class Peek_i:
    def exe(self, obj):
        obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp-1]+1] = obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1]
        obj.pc += 1
        return True


class Peek_f:
    def exe(self, obj):
        obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp-1]+1] = obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1]
        obj.pc += 1
        return True


class Poke_c:
    def exe(self, obj):
        obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1] = obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp-1]+1]
        obj.pc += 1
        return True


class Poke_s:
    def exe(self, obj):
        obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1] = obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp-1]+1]
        obj.pc += 1
        return True


class Poke_i:
    def exe(self, obj):
        obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1] = obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp-1]+1]
        obj.pc += 1
        return True


class Poke_f:
    def exe(self, obj):
        obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp]+1] = obj.rstack[obj.fpstack[obj.fpsp]+obj.rstack[obj.sp-1]+1]
        obj.pc += 1
        return True


class Swp:
    def exe(self, obj):
        tmp = obj.rstack[obj.sp - 1]
        obj.rstack[obj.sp - 1] = obj.rstack[obj.sp]
        obj.rstack[obj.sp] = tmp
        obj.pc += 1
        return True
    

class Add:
    def exe(self, obj):
        obj.rstack[obj.sp-1] = obj.rstack[obj.sp - 1] + obj.rstack[obj.sp]
        obj.sp -= 1
        obj.pc += 1
        return True


class Sub:
    def exe(self, obj):
        obj.rstack[obj.sp-1] = obj.rstack[obj.sp - 1] - obj.rstack[obj.sp]
        obj.sp -= 1
        obj.pc += 1
        return True


class Mul:
    def exe(self, obj):
        obj.rstack[obj.sp-1] = obj.rstack[obj.sp - 1] * obj.rstack[obj.sp]
        obj.sp -= 1
        obj.pc += 1
        return True


class Div:
    def exe(self, obj):
        obj.rstack[obj.sp-1] = obj.rstack[obj.sp - 1] / obj.rstack[obj.sp]
        obj.sp -= 1
        obj.pc += 1
        return True


class Print_c:
    def exe(self, obj):
        print(f"{obj.rstack[obj.sp]:.2f}")
        obj.sp -= 1
        obj.pc += 1
        return True


class Print_s:
    def exe(self, obj):
        print(f"{obj.rstack[obj.sp]:.2f}")
        obj.sp -= 1
        obj.pc += 1
        return True


class Print_i:
    def exe(self, obj):
        print(f"{obj.rstack[obj.sp]:.2f}")
        obj.sp -= 1
        obj.pc += 1
        return True


class Print_f:
    def exe(self, obj):
        print(f"{obj.rstack[obj.sp]:.2f}")
        obj.sp -= 1
        obj.pc += 1
        return True


class Halt:
    def exe(self, obj):
        return False


class Cmpe:
    def exe(self, obj):
        obj.rstack[obj.sp-1] = obj.rstack[obj.sp-1] == obj.rstack[obj.sp]
        obj.sp -= 1
        obj.pc += 1
        return True


class Cmplt:
    def exe(self, obj):
        obj.rstack[obj.sp-1] = obj.rstack[obj.sp-1] < obj.rstack[obj.sp]
        obj.sp -= 1
        obj.pc += 1
        return True


class Cmpgt:
    def exe(self, obj):
        obj.rstack[obj.sp-1] = obj.rstack[obj.sp-1] > obj.rstack[obj.sp]
        obj.sp -= 1
        obj.pc += 1
        return True


class Jmp:
    def exe(self, obj):
        obj.pc = obj.rstack[obj.sp]
        obj.sp -= 1
        return True


class Jmpc:
    def exe(self, obj):
        if(obj.rstack[obj.sp-1]):
            obj.pc = obj.rstack[obj.sp]
            obj.sp -= 2
        else:
            obj.sp -= 2
            obj.pc += 1
        return True


class Call:
    def exe(self, obj):
        obj.fpsp += 1
        obj.fpstack[obj.fpsp] = obj.sp - obj.rstack[obj.sp] - 1
        obj.sp -= 1
        obj.pc = obj.rstack[obj.sp]
        obj.sp -= 1
        return True


class Ret:
    def exe(self, obj):
        obj.sp = obj.fpstack[obj.fpsp]
        obj.fpsp -= 1
        obj.pc = obj.rstack[obj.sp]
        obj.sp -= 1
        return True
