#include "Component.h"
#include "Condition.h"
#include "Trigger.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <tuple>
#include <string>
using namespace tinyxml2;

/* Constructor/Destructor for Component [base class] */
Component::Component( ) { }
Component::~Component( ) { }

/* Setter/Getter for object name */
void Component::setName( std::string newName ) {
    this->name = newName;
    return;
}
std::string Component::getName( void ) { return name; }

/* Setter/Getter for object status */
void Component::setStatus( std::string newStatus ) {
    this->status = newStatus;
    return;
}
std::string Component::getStatus( void ) { return status; }

/* Setter/Getter for object description */
void Component::setDescription( std::string newDescription ) {
    this->description = newDescription;
    return;
}
std::string Component::getDescription( void ) { return description; }

/* Setter/Getter for object triggers */
void Component::addTrigger( Trigger * trig ) {
    this->triggers.push_back(trig);
    return;
}
std::vector<Trigger *> Component::getTriggers( ) {
    return this->triggers;
}

/* showTriggers() only used for debug */
void Component::showTriggers( ) {
    for(auto i : triggers) {
        std::cout << "Trigger type: "<< i->getMode() << std::endl;
        std::cout << "Trigger print: "<< i->getPrint() << std::endl;
        std::cout << "Trigger command: "<< i->getCommand() << std::endl;
        std::cout << "Trigger action: "<< i->getAction() << std::endl;
    }
    return;
}
