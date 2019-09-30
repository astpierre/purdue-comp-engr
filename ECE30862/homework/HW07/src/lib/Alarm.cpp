#include <iostream>
#include <cmath>
#include "Alarm.h"

Alarm::Alarm(Subject * s, int i, double xx, double yy, double alarm) :
id(i), x(xx), y(yy), soundAlarm(alarm) {
    s->subscribe(this);
}

Alarm::~Alarm( ) { }

void Alarm::notify(double xx, double yy) {
    double x_diff_squared = std::pow((xx - this->x), 2);
    double y_diff_squared = std::pow((yy - this->y), 2);
    double distance = std::sqrt(x_diff_squared + y_diff_squared);
    if(distance > this->soundAlarm) {
        std::cout << "Alarm"<<this->id<<" sounded! Moved "<< distance <<" meters"<< std::endl;
    }
}
