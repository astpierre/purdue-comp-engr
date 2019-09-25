require_relative "headhunter"

class JobSeeker
  attr_reader :minSalary, :name

  def initialize(headhunter, name, minSalary)
    headhunter.add_observer(self)
    @name = name
    @minSalary = minSalary
  end
  
  def update(companyName, jobTitle, monthlyRate)
    puts @name.ljust(10) + 'New Job Match Received!  | ' + companyName.ljust(10) + jobTitle.ljust(35) + '$' + monthlyRate.to_s.ljust(7)
  end

  def to_s
    'JobSeeker'
  end
end