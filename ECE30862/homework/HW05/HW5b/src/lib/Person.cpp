#include "Person.h"
#include <string>
#include <iostream>

Person::Person(int d, int m, int y, std::string n) :
   day(d), month(m), year(y), name(n) {
   std::cout << "constructed Person " << std::endl;
}

Person::~Person( ) { }
