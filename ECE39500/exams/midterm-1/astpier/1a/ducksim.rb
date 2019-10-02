#!/usr/bin/env ruby

require_relative 'duckbase'
require_relative 'duck'
require_relative 'behavior'
require_relative 'flybehavior'
require_relative 'flywithwings'
require_relative 'quackbehavior'
require_relative 'quackquack'
require_relative 'squeaksqueak'
require_relative 'swimbehavior'
require_relative 'paddleswim'
require_relative 'floatswim'


def main
    puts "========================================" 
    puts " Duck on display: <duck.name>"
    puts "  <duck.fly.do>"
    puts "  <duck.quack.do>"
    puts "  <duck.swim.do>"
    puts "========================================" 
    
    plain_duck = Duck.new(fly_behavior: FlyBehavior.new(), 
                          quack_behavior: QuackBehavior.new(), 
                          swim_behavior: SwimBehavior.new(),
                          name: "Plain Duck")
    living_duck = Duck.new(fly_behavior: FlyWithWings.new(), 
                           quack_behavior: QuackQuack.new(), 
                           swim_behavior: PaddleSwim.new(),
                          name: "Living Duck")
    rubber_duck = Duck.new(quack_behavior: SqueakSqueak.new(), 
                           swim_behavior: FloatSwim.new(),
                          name: "Rubber Duck")
    dogtoy_duck = Duck.new(quack_behavior: SqueakSqueak.new(), name: "DogToy")

    plain_duck.do_your_thing
    living_duck.do_your_thing
    rubber_duck.do_your_thing
    dogtoy_duck.do_your_thing
end

main
