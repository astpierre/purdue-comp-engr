require_relative "employer"
require_relative "headhunter"
require_relative "jobseeker"

def main
    google = Employer.new()
    facebook = Employer.new()
    apple = Employer.new()

    h1 = HeadHunter.new("H1")       # Apple and Google
    h2 = HeadHunter.new("H2")       # Google & Facebok
    h3 = HeadHunter.new("H3")       # Facebook & Apple
    
    google.add_observer(h1)
    apple.add_observer(h1)

    google.add_observer(h2)
    facebook.add_observer(h2)

    apple.add_observer(h3)
    facebook.add_observer(h3)

    # JobSeekers: Andrew, Michael and Dwight
    andrew = JobSeeker.new(h1, "Andrew", 100)       # Andrew receives jobs from Apple, Google, and Facebook
    h2.add_observer(andrew)
    michael = JobSeeker.new(h2, "Michael", 50)      # Michael receives jobs from Apple, Google, and Facebook
    h3.add_observer(michael)
    dwight = JobSeeker.new(h3, "Dwight", 25)        # Dwight receives jobs from Apple, Google, and Facebook
    h1.add_observer(dwight)
    oscar = JobSeeker.new(h3, "Oscar", 1000)        # Oscar receives jobs from Apple, Google, and Facebook
    h1.add_observer(oscar)

    google.newJob("Google", "Site Reliability Engineer", 110)   # Notifies ALL - Oscar
    apple.newJob("Apple", "Software Engineer", 70)              # Notifies Michael and Dwight
    facebook.newJob("Facebook", "Software Engineer", 30)        # Notifies Dwight
    facebook.newJob("Facebook", "Production Engineer", 3000)    # Notifies ALL
    
end

main