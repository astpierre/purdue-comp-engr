#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <string>
using namespace std;

class Base {
private:
   int privB;
protected:
   int protB;
public:
   int publicB;

   Base( );
   virtual ~Base( );

   virtual void print( ) const;
   virtual int getPrivB() const;
   virtual int getPublicB() const;
   virtual int getProtB() const;
};

#endif /* BASE_H */
