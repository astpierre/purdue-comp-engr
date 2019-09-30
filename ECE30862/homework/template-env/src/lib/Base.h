#ifndef BASE_H_
#define BASE_H_
#include <string>

class Base {
public:
   Base( );
   virtual ~Base( );

   virtual std::string sayHello();
};
#endif /*BASE_H*/
