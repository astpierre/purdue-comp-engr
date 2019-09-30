#include <iostream>
#include "GPS.h"

GPS::GPS(int s) : size(s), x(0.0), y(0.0), idx(0) {
   this->obs = new Observer*[size];
   std::cout << "Created new GPS, observer array size = "<<size << std::endl;
}

GPS::~GPS( ) {
   delete obs;
}

void GPS::subscribe(Observer * o) {
    if(this->idx > this->size) {
        std::cout << "ERROR: GPS::subscribe, observer array full!" << std::endl;
    } else {
        this->obs[idx] = o;
        if(this->idx < this->size) {
            this->idx += 1;
        } else {
            std::cout <<"idx="<<idx<<"=size="<<size<<std::endl;
        }
    }
    return;
}

void GPS::update(double xx, double yy) {
    this->x = xx;
    this->y = yy;
    //std::cout << "new map location: ("<<x<<","<<y<<")"<< '\n';
    this->notify();
}

void GPS::notify() {
    for(int i=0; i<=idx; i++) {
        this->obs[i]->notify(this->x, this->y);
    }
}
