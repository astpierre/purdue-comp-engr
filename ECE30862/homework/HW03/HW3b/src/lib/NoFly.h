//
// Created by asaintp on 1/21/19.
//

#ifndef HW3B_NOFLY_H
#define HW3B_NOFLY_H
#include "FlyBehavior.h"

class NoFly : public FlyBehavior {
public:

    NoFly( );
    virtual ~NoFly( );
    virtual void fly( );

};
#endif //HW3B_NOFLY_H
