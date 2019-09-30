#ifndef PRIVDERIVED_H
#define PRIVDERIVED_H
#include "Base.h"
#include <iostream>
#include <string>
using namespace std;

class PrivDerived : private Base {
public:
   PrivDerived( );
   virtual ~PrivDerived( );
   // Getters for the now private
   // base getter methods
   int showMePublicB() const;
   int showMePrivB() const;
   int showMeProtB() const;
};

#endif /* PRIVDERIVED_H */
