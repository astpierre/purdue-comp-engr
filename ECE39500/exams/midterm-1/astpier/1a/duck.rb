require_relative 'duckbase'

class Duck < DuckBase
   
    def initialize(fly_behavior: nil, quack_behavior: nil, swim_behavior: nil, name: 'duck')
      @fly = fly_behavior
      @quack = quack_behavior
      @swim = swim_behavior
      @name = name
    end

    def fly
      if @fly != nil then
        @fly.do()
      end
    end

    def quack
      if @quack != nil then
        @quack.do()
      end
    end

    def swim
      if @swim != nil then
        @swim.do()
      end
    end

    def do_your_thing
      puts "Duck on display: #@name"
      puts @fly.do unless @fly == nil
      puts @quack.do unless @quack == nil
      puts @swim.do unless @swim == nil
      puts "="*40
    end
end
