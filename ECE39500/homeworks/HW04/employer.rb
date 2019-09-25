require "observer"

class Employer
  include Observable

  def initialize
    @jobOpenings = []
  end

  def newJob(companyName, jobTitle, monthlyRate)
    @jobOpenings << [companyName, jobTitle, monthlyRate]
    puts "Employer: #{companyName} " + 'adding job opening  | ' + companyName.ljust(10) + jobTitle.ljust(35) + '$' + monthlyRate.to_s.ljust(7)
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
