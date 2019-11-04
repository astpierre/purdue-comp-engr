import json


def get_opcodes():
    with open("opcodes.json", "r") as op:
        c = op.read()
        opcodes = json.loads(c)
    opcode_dict = {}
    for op in opcodes:
        opcode_dict[op["value"]] = op["opcode"]
    return opcode_dict
