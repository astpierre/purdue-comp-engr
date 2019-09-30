#ifndef HW3B_DOG_H
#define HW3B_DOG_H

#include "Duck.h"

class Dog {
public:

    Dog( );
    virtual ~Dog( );
    void play(Duck*);
    virtual std::string bark();
};


#endif //HW3B_DOG_H
