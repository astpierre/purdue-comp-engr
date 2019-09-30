// This is the main class for template-env
#include "src/lib/Base.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    Base * testBase = new Base( );
    std::cout << testBase->sayHello();
    std::cout << "Hello World!" << std::endl;
    return 0;
}
