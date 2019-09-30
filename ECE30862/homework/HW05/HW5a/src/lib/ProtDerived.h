#ifndef PROTDERIVED_H
#define PROTDERIVED_H
#include <iostream>
#include <string>
#include "Base.h"
using namespace std;

class ProtDerived : protected Base {
public:
   ProtDerived( );
   virtual ~ProtDerived( );
   //void print( );
   int showMePublicB() const;
   int showMePrivB() const;
   int showMeProtB() const;
};

#endif /* PROTDERIVED_H */
