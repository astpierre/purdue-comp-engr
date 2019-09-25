require_relative "employer"
require_relative "headhunter"
require_relative "jobseeker"

def main

    google = Employer.new()
    apple = Employer.new()

    hh = HeadHunter.new()
    google.add_observer(hh)
    apple.add_observer(hh)

    andrew = JobSeeker.new(hh, "Andrew", 100)
    linus = JobSeeker.new(hh, "Linus", 50)

    google.newJob("Google", "Site Reliability Engineer", 110)
    apple.newJob("Apple", "Software Engineer", 70)

end

main