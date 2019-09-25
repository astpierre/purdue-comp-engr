require "observer"
require_relative "employer"
require_relative "jobseeker"

class HeadHunter
  attr_accessor :observers

  include Observable 

  def initialize(name)
    @name = name
    @observers = []
    @jobPositions = []
  end

  def update(companyName, jobTitle, monthlyRate)
    @jobPositions << [companyName, jobTitle, monthlyRate]
    puts "HeadHunter: #{@name} received new job opening  | " + companyName.ljust(10) + jobTitle.ljust(35) + '$' + monthlyRate.to_s.ljust(7)
    changed
    notify_observers(companyName, jobTitle, monthlyRate)
  end

  def add_observer(o)
    @observers << o
  end

  def notify_observers(companyName, jobTitle, monthlyRate)
    for obs in @observers
      if obs.minSalary <= monthlyRate
        obs.update(companyName, jobTitle, monthlyRate)
      end
    end
  end

end