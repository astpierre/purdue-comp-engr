#!/usr/bin/env python3

class Bytecode():
    def __init__(self, name, opcode):
        self.name = name
        self.op = opcode

    def __str__(self):
        return f"Bytecode Object: {self.name}\t{self.op}"