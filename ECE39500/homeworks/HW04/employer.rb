class Animal
  @move_behavior
  @talk_behavior

  def initialize(move_behavior, talk_behavior)
    @move_behavior = move_behavior
    @talk_behavior = talk_behavior
  end

  def performMove
    @move_behavior.move()
  end

  def performTalk
    @talk_behavior.talk()
  end

end
