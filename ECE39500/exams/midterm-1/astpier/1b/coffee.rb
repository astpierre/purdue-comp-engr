require_relative 'strategies'

class Coffee
  attr_accessor :cost, :strategies, :ingredients

  def initialize(strategies)
    @strategies = Array.new
    @cost = 2.00
    @ingredients = Array.new

    for strat in strategies do
      @strategies.push(strat)
    end
  end

  def make
    for strat in @strategies do
      strat.add_to(self)
    end
  end

  def cost=(newcost)
    @cost = newcost
  end
  
  def cost
    @cost
  end

  def to_s
      @ingredients.to_s + '  Total Cost: $' + @cost.to_s
  end
end
