//
// Created by asaintp on 1/21/19.
//

#ifndef HW3B_DUCK_H
#define HW3B_DUCK_H
#include <string>
#include "FlyBehavior.h"
#include "Quack.h"

class Duck {
public:

    Duck(std::string);
    Duck( );
    virtual ~Duck( );

    virtual void quack( );
    virtual void setFlyBehavior(FlyBehavior*);
    virtual void setQuackBehavior(Quack*);
    virtual void fly( );
    virtual void swim( );
    virtual void display( );


private:
    std::string kind;
    FlyBehavior* flyBehavior;
    Quack* quackBehavior;
};
#endif //HW3B_DUCK_H
