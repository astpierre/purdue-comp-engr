import sys

class CompilerState():
    INT_MIN = -sys.maxsize - 1

    def __init__(self):
        return
    
    def comma(self):
        pass

    def value(self):
        pass

    def eol(self):
        pass

    def eof(self):
        pass

    def validOperands(self, operands, count):
        valid = True
        for i in range(count):
            if not valid: break
            if operands[i] == INT_MIN:
                valid = False
        return valid
    
    def printInvalidOperands(self, operands, count):
        for i in range(count):
            if operands[i] < 0:
                print(f"Operand[{i}], {operands[i]} is invalid.")
        return None