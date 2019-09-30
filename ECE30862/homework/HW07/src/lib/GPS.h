#ifndef GPS_H
#define GPS_H
#include "Observer.h"
#include "Subject.h"

class GPS: public Subject {
public:
    GPS(int s);
    virtual ~GPS( );
    virtual void subscribe(Observer * o);
    virtual void update(double xx, double yy);
    virtual void notify();
private:
    double x, y;
    int idx;
    int size;
    Observer ** obs;
};

#endif /* GPS_H */
