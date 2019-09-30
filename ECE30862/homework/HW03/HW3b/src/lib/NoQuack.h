//
// Created by asaintp on 1/21/19.
//

#ifndef HW3B_NOQUACK_H
#define HW3B_NOQUACK_H

#include <string>
#include "Quack.h"

class NoQuack : public Quack {
public:

    NoQuack( );
    virtual ~NoQuack( );
    virtual void quack( );
};
#endif //HW3B_NOQUACK_H
