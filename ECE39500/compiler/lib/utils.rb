
module CompilerUtils
  BC_MAP = {
    cmpe: 132,
    cmplt: 136,
    cmpgt: 140,
    jmp: 36,
    jmpc: 40,
    call: 40,
    ret: 48,
    pushc: 68,
    pushs: 69,
    pushi: 70,
    pushf: 71,
    pushvc: 72,
    pushvs: 73,
    pushvi: 74,
    pushvf: 75,
    popm: 76,
    popv: 80,
    popa: 77,
    peekc: 84,
    peeks: 85,
    peeki: 86,
    peekf: 87,
    pokec: 88,
    pokes: 89,
    pokei: 90,
    pokef: 91,
    swp: 94,
    add: 100,
    sub: 104,
    mul: 108,
    div: 112,
    printc: 148,
    prints: 149,
    printi: 150,
    printf: 151,
    halt: 0,
  }

  class SymbolTable
    @@num_symbols = 0
    def initialize
      @table = {}
    end

    def add(key, value)
      @@num_symbols += 1
      @table[key] = value
    end

    def get(key)
      @table[key]
    end

    def to_s
      puts @table
    end
  end
end
