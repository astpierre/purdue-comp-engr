require_relative 'coffee'

class Strat
  attr_accessor :name, :price

  @name = 'default'
  @price = 0.00

  def add_to(coffee)
      newcost = coffee.cost.to_f + @price.to_f
      coffee.cost = newcost
      coffee.ingredients.push(@name)
  end
end


class Cream < Strat
  def initialize
    @name = 'cream'
    @price = 0.45
  end
  
  def add_to(*)
      super
  end
end


class Soy < Strat
  def initialize
    @name = 'soy'
    @price = 0.25
  end

  def add_to(*)
      super
  end
end


class Sugar < Strat
  def initialize
    @name = 'sugar'
    @price = 0.15
  end
  def add_to(*)
      super
  end
end
