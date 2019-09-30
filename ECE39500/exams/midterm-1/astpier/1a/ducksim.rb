require_relative 'duckbase'
require_relative 'duck'
require_relative 'behavior'
require_relative 'flybehavior'
require_relative 'flywithwings'
require_relative 'nofly'
require_relative 'quackbehavior'
require_relative 'quackquack'
require_relative 'squeaksqueak'
require_relative 'swimbehavior'
require_relative 'paddleswim'
require_relative 'floatswim'


def main
    plain_duck = Duck.new(FlyBehavior.new(), QuackBehavior.new(), SwimBehavior.new())
    living_duck = Duck.new(FlyWithWings.new(), QuackQuack.new(), PaddleSwim.new())
    rubber_duck = Duck.new(NoFly.new(), SqueakSqueak.new(), FloatSwim.new())

    puts "Plain Duck: " + plain_duck.fly + ' ' + plain_duck.quack + ' ' + plain_duck.swim
    puts "Living Duck: " + living_duck.fly + ' ' + living_duck.quack + ' ' + living_duck.swim
    puts "Rubber Duck: " + rubber_duck.fly + ' ' + rubber_duck.quack + ' ' + rubber_duck.swim

end

main
