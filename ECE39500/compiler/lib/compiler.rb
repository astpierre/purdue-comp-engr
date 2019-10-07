require_relative "utils"

module Compiler
  include CompilerUtils
  # BC_MAP == CompilerUtils::BC_MAP
  @symbol_table = CompilerUtils::SymbolTable.new

  def Compiler.main
    @program_lines = []
    File.open("./programfile.txt", "r") do |f|
      f.each_line do |line|
        @program_lines << line
      end
    end

    Compiler.createSymbolTable

    Compiler.generateByteCode

    puts @symbol_table

  end

  def Compiler.createSymbolTable
    var_func_name = nil
    func_stack_offset = 0

    @program_lines.each do |line|
      line_arr = line.split(' ')
      if line_arr[0] == "subr" then
        var_func_name = line_arr[2]
        func_stack_offset = 0
      end

      if line_arr[0] == "decl" then
        key = var_func_name << line_arr[1]
        @symbol_table.add(key, func_stack_offset)
        func_stack_offset = func_stack_offset + 1
      end
    end
  end


  def Compiler.generateByteCode
    @program_lines.each do |line|
      puts line
    end
  end
end

Compiler.main
