class Behavior
  def do
    raise NotImplementedError, "#{self.class} has not implemented method '#{__method__}'"
  end
end
