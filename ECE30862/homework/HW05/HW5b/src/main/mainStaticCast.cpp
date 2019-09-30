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

    student = static_cast<Student*>(faculty);
    std::cout << "before (student=faculty).putGPA(6.6)" << std::endl;
    student->putGPA(6.6);
    std::cout << "before (student=faculty).getGPA" << std::endl;
    student->getGPA( );

    student = new Student(3,3,3,"Irena");
    faculty = static_cast<Faculty *>(student); // compiles, but will cause problems at runtime
    std::cout << "before (faculty=student).putSalary" << std::endl;
    faculty->putSalary(500.0);
    std::cout << "before (faculty=student).getSalary" << std::endl;
    faculty->getSalary( );

    v = (void*) person ;
    student = static_cast<Student*>(v);
    std::cout << "before (student=person).getGPA" << std::endl;
    student->getGPA( );
    std::cout << "finished" << std::endl;
}
