require_relative 'duckbase'

class Duck < DuckBase
   
    def initialize(fly_behavior)#, quack_behavior, swim_behavior)
        @fly = fly_behavior
        #@quack = quack_behavior
        #@swim = swim_behavior
    end

    def fly
        @fly.do()
    end

=begin

    def quack
        @quack.do()
    end

    def swim
        @swim_behavior.do()
    end
=end

end
