#include "Condition.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <tuple>
#include <string>
using namespace tinyxml2;

/* Constructor/Destructor for Condition */
Condition::Condition( XMLElement * ConditionElement ) {
    if(ConditionElement->FirstChildElement("status") != nullptr) {
        this->status = ConditionElement->FirstChildElement("status")->GetText();
    } else this->status = "NONE";

    if(ConditionElement->FirstChildElement("has") != nullptr) {
        this->has = ConditionElement->FirstChildElement("has")->GetText();
    } else this->has = "NONE";

    if(ConditionElement->FirstChildElement("object") != nullptr) {
        this->object = ConditionElement->FirstChildElement("object")->GetText();
    } else this->object = "NONE";

    if(ConditionElement->FirstChildElement("owner") != nullptr) {
        this->owner = ConditionElement->FirstChildElement("owner")->GetText();
    } else this->owner = "NONE";
}

Condition::~Condition( ) { }

/* Setter/Getter for "Has" attribute */
void Condition::setHas( std::string h ) { has = h; }
std::string Condition::getHas( ) {  return has;  }

/* Setter/Getter for owner attribute */
void Condition::setOwner( std::string o ) { owner = o; }
std::string Condition::getOwner( ) {  return owner;  }

/* Setter/Getter for object condtion is bound to */
void Condition::setObject( std::string o ) {  object = o;  }
std::string Condition::getObject( ) {  return object;  }

/* Setter/Getter for status of object condition is bound to */
void Condition::setStatus( std::string s ) {  status = s;  }
std::string Condition::getStatus( ) {  return status;  }
