#include "Set.h"
#include <iostream>
#include <string>

Set::Set( unsigned int maxSize ) {
    numSlots = maxSize/32 + 1;
    slots = new unsigned int [numSlots];
    for(unsigned int i=0; i<numSlots; i++) {
        slots[i] &= 0x00000000;
    }
    numElements = 0;
}

Set::~Set( ) {  }

void Set::add( unsigned int newMember ) {
    unsigned int newSlot = 0;
    newSlot = (newMember) / 32;
    unsigned int position = (newMember) % 32;
    if(slots[newSlot]&(1<<(position))) {
        numElements = numElements;
    } else {
        slots[newSlot] |= (1<<(position));
        numElements += 1;
    }
}

Set Set::operator+( const unsigned int newMember ) {
    // /unsigned int setSize = numSlots;
    Set newSet = Set(63);
    if(numElements == 0) {
        newSet.add(newMember);
        return newSet;
    }

    unsigned int ctr = 0;
    for(unsigned int i=0; i<numSlots; i++) {
        for(unsigned int j=0; j<32; j++) {
            if(slots[i] & (1<<j)) {
                newSet.add(ctr);
            }
            ctr += 1;
        }
    }
    newSet.add(newMember);
    return newSet;
}

void Set::remove( unsigned int oldMember ) {
    unsigned int oldSlot = 0;
    oldSlot = oldMember / 32;
    unsigned int position = oldMember % 31;
    slots[oldSlot] &= (~(1<<(position)));
}

Set Set::operator-( const unsigned int oldMember ) {
    //unsigned int setSize = getNumSlots();
    Set newSet = Set(63);

    unsigned int ctr = 0;
    for(unsigned int i=0; i<numSlots; i++) {
        for(unsigned int j=0; j<32; j++) {
            if(slots[i] & (1<<j)) {
                newSet.add(ctr);
            }
        }
        ctr += 1;
    }
    newSet.remove(oldMember);
    return newSet;
}

Set Set::operator&( const Set Set2 ) {
    // Get max numSlots
    unsigned int numSlots1 = this->getNumSlots();
    unsigned int numSlots2 = Set2.numSlots;
    unsigned int maxNumSlots = 0;
    if(numSlots1 >= numSlots2) maxNumSlots = numSlots1;
    else maxNumSlots = numSlots2;

    Set newSet = Set(maxNumSlots * 32);
    unsigned int ctr = 0;
    for(unsigned int i=0; i<maxNumSlots; i++) {
        for(unsigned int j=0; j<32; j++) {
            if(this->slots[i] & (1<<j)) {
                if(Set2.slots[i] & (1<<j)) {
                    newSet.add(ctr);
                }
            }
            ctr += 1;
        }
    }
    return newSet;
}

Set Set::operator/( const Set Set2 ) {
    Set newSet = Set(numSlots * 32);
    unsigned int ctr = 0;
    for(unsigned int i=0; i<numSlots; i++) {
        for(unsigned int j=0; j<32; j++) {
            if(this->slots[i] & (1<<j)) {
                if(Set2.slots[i] & (1<<j)) {
                    newSet.numElements = newSet.numElements;
                } else {
                    newSet.add(ctr);
                }
            }
            ctr += 1;
        }
    }
    return newSet;
}

Set Set::operator~( ) {
    Set newSet = Set(63);
    unsigned int ctr = 0;
    for(unsigned int i=0; i<numSlots; i++) {
        for(unsigned int j=0; j<32; j++) {
            if(this->slots[i] & (1<<j)) {
                newSet.numElements = newSet.numElements;
            } else newSet.add(ctr);
            ctr += 1;
        }
    }
    return newSet;
}

/*std::ostream& Set::operator<<( std::ostream& os ) {
    unsigned int ctr = 0;
    for(unsigned int i=0; i<this->numSlots; i++) {
        for(unsigned int j=0; j<32; j++) {
            if(this->slots[i] & (1<<j)) os << ctr << " ";
            ctr += 1;
        }
    }
    return os;
}*/

/*Set::Set( const Set Set2 ) {
    std::cout << "Copy constructor invoked." << std::endl;
}*/

void Set::printSet( ) {
    unsigned int ctr = 0;
    for(unsigned int i=0; i<numSlots; i++) {
        for(unsigned int j=0; j<32; j++) {
            if(slots[i] & (1<<j)) {
                std::cout << ctr << " ";
            }
            ctr += 1;
        }
    }
    std::cout << " " << std::endl;
}

unsigned int Set::getNumSlots( ) {
    return numSlots;
}
