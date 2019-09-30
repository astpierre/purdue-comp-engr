#ifndef NOFLY_H_
#define NOFLY_H_
#include "FlyBehavior.h"

class NoFly : public FlyBehavior {
public:

   NoFly( );
   virtual ~NoFly( );
   void fly( );

};
#endif /* NOFLY_H_ */
