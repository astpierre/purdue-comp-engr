#ifndef SQUEAK_H_
#define SQUEAK_H_
#include <string>
#include "Quack.h"

class Squeak : public Quack {
public:

   Squeak( );
   virtual ~Squeak( );
   void quack( );
};
#endif /* SQUEAK_H_ */
