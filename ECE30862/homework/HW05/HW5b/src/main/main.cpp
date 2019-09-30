//
// THIS CODE IS EVIL and you should never do anything like this.
// It demonstrates what can go wrong when you use C-style casts
//

#include "src/lib/Person.h"
#include "src/lib/Student.h"
#include "src/lib/Faculty.h"
#include <iostream>

int main() {
    std::cout << "========================================\n";
    Person* person = new Person(1,1,1,"Bob");
    Faculty* faculty = new Faculty(2,2,2,"Dumbledore");
    Student* student;
    void* v;

    student = (Student*) faculty;
    std::cout << "before (student=faculty).putGPA(6.6)" << std::endl;
    student->putGPA(6.6);
    std::cout << "before (student=faculty).getGPA" << std::endl;
    student->getGPA( );

    student = new Student(3,3,3,"Irena");
    faculty = (Faculty *) student; // compiles, but will cause problems at runtime
    std::cout << "before (faculty=student).putSalary" << std::endl;
    faculty->putSalary(500.0);
    std::cout << "before (faculty=student).getSalary" << std::endl;
    faculty->getSalary( );

    v = (void*) person ;
    student = (Student*) v;
    std::cout << "before (student=person).getGPA" << std::endl;
    student->getGPA( );
    std::cout << "finished" << std::endl;
}
