require "observer"

class Employer
  include Observable

  def initialize
    @jobOpenings = []
  end

  def newJob(companyName, jobTitle, monthlyRate)
    @jobOpenings << [companyName, jobTitle, monthlyRate]
    changed
    notify_observers(companyName, jobTitle, monthlyRate)
  end

  def to_s
    @jobOpenings.each do |j|
      text = "Job: #{j}"
      puts text
    end
  end
end
