#include <iostream>
#include "DogToy.h"

DogToy::DogToy( ) : Duck("DogToy") {
   setFlyBehavior(new NoFly( ));
   setQuackBehavior(new Squeak( ));
}
DogToy::~DogToy( ) { }
