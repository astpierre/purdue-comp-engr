#ifndef DPUBLIC_H
#define DPUBLIC_H
#include <iostream>
#include <string>
#include "PublicDerived.h"
using namespace std;

class dPublic : public PublicDerived {
public:
   dPublic( );
   virtual ~dPublic( );
};

#endif /* DPUBLIC_H */
