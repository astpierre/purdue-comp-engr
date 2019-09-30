#include <iostream>
#include "DogToy.h"

DogToy::DogToy( ) : Duck("DogToy") {
    // USE one of the other types of ducks as an example to fill this in
    // PUT CODE HERE Make fly behavior be NoFly( )
    setFlyBehavior(new NoFly( ));
    // PUT CODE HERE Make Quack behavior be Squeak
    setQuackBehavior(new Squeak( ));
}
DogToy::~DogToy( ) { }