require_relative 'animal'

class Fish < Animal
    def initialize(move_behavior, talk_behavior)
        super(move_behavior, talk_behavior)
    end
end