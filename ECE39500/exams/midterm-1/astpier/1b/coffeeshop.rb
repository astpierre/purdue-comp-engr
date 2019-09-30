require_relative 'coffee'
require_relative 'strategies'


def main
  cream = Cream.new()
  sugar = Sugar.new()
  soy = Soy.new()

  cream_and_sugar = Coffee.new([cream, sugar])
  cream_and_sugar.make
  puts cream_and_sugar
  
  everything = Coffee.new([cream, sugar, soy])
  everything.make
  puts everything

  just_sugar = Coffee.new([sugar])
  just_sugar.make
  puts just_sugar
end


main
