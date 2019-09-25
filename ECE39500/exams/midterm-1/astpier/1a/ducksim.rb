require_relative 'duckbase'
require_relative 'duck'
require_relative 'behavior'
require_relative 'flybehavior'
require_relative 'flywithwings'


def main
    d = Duck.new(FlyBehavior.new())
    dw = Duck.new(FlyWithWings.new())

    puts d.fly
    puts dw.fly

end

main
