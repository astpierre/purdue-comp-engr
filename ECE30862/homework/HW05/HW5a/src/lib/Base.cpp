#include "Base.h"

Base::Base( ) : privB(1), protB(2), publicB(3) {  }

Base::~Base( ) { }

void Base::print( ) const {
   cout << "Base" << endl;
   cout << "privB: " << privB;
   cout << ", protB: " << protB;
   cout << ", publicB: " << publicB;
   cout << endl << endl;
}

int Base::getPrivB() const {
    return privB;
}
int Base::getProtB() const {
    return protB;
}
int Base::getPublicB() const {
    return publicB;
}
