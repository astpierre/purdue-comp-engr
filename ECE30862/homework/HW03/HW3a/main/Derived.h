#ifndef HW3_DERIVED_H
#define HW3_DERIVED_H
#include "Base.h"

class Derived : public Base {
public:
    // Constructor
    Derived( );
    // Destructor
    virtual ~Derived( );

    // Methods
    void f2(); // Overwrites base->f2()
};
#endif //HW3_DERIVED_H
