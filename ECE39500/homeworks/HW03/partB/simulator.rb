require_relative 'animal'
require_relative 'move'
require_relative 'talk'
require_relative 'dog'
require_relative 'cat'
require_relative 'fish'
require_relative 'bark'
require_relative 'meow'
require_relative 'mute'
require_relative 'walk'
require_relative 'swim'

dog_move = Walk.new
dog_talk = Bark.new

doggy = Dog.new(dog_move, dog_talk)

doggy.performMove
doggy.performTalk


cat_move = Walk.new
cat_talk = Meow.new

kitty = Cat.new(cat_move, cat_talk)

kitty.performMove
kitty.performTalk


fish_move = Swim.new
fish_talk = Mute.new

fishy = Fish.new(fish_move, fish_talk)

fishy.performMove
fishy.performTalk