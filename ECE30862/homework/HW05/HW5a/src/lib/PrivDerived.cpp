#include "PrivDerived.h"

PrivDerived::PrivDerived( ) { }
PrivDerived::~PrivDerived( ){ }

int PrivDerived::showMePublicB() const {
    return getPublicB();
}

int PrivDerived::showMeProtB() const {
    return getProtB();
}

int PrivDerived::showMePrivB() const {
    return getPrivB();
}
