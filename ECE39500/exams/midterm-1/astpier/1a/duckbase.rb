class DuckBase
  def quack
    raise NotImplementedError, "#{self.class} has not implemented method '#{__method__}'"
  end
  
  def fly
    raise NotImplementedError, "#{self.class} has not implemented method '#{__method__}'"
  end
  
  def swim
    raise NotImplementedError, "#{self.class} has not implemented method '#{__method__}'"
  end
end
