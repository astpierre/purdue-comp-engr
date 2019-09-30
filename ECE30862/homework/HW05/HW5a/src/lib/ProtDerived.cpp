#include "ProtDerived.h"

ProtDerived::ProtDerived( ) { }
ProtDerived::~ProtDerived( ){ }

int ProtDerived::showMePublicB() const {
    return getPublicB();
}

int ProtDerived::showMeProtB() const {
    return getProtB();
}

int ProtDerived::showMePrivB() const {
    return getPrivB();
}
