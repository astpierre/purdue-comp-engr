require "observer"
require_relative "employer"
require_relative "jobseeker"

class HeadHunter
  attr_accessor :observers

  include Observable 

  def initialize
    @observers = []
    @jobPositions = []
  end

  def update(companyName, jobTitle, monthlyRate)
    @jobPositions << [companyName, jobTitle, monthlyRate]
    changed
    notify_observers(companyName, jobTitle, monthlyRate)
  end

  def notify_observers(companyName, jobTitle, monthlyRate)
    puts @observer_count
    @observers.each do |observer|
      if observer.minSalary <= monthlyRate
        observer.update(companyName, jobTitle, monthlyRate)
      end
    end
  end

end