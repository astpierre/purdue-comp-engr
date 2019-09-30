#include "Trigger.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <tuple>
#include <string>
using namespace tinyxml2;

/* Constructor/Deconstructor for Trigger object */
Trigger::Trigger( XMLElement * triggerElement ) {
    if(triggerElement->FirstChildElement("type") != nullptr) {
        changeMode(triggerElement->FirstChildElement("type")->GetText());
    } else {
        changeMode("single");
    }

    if(triggerElement->FirstChildElement("print") != nullptr) {
        setPrint(triggerElement->FirstChildElement("print")->GetText());
    } else {
        setPrint("NONE");
    }

    if(triggerElement->FirstChildElement("command") != nullptr) {
        setCommand(triggerElement->FirstChildElement("command")->GetText());
    } else {
        setCommand("NONE");
    }
    if(triggerElement->FirstChildElement("action") != nullptr) {
        setAction(triggerElement->FirstChildElement("action")->GetText());
    } else {
        setAction("NONE");
    }
    /* Conditions */
    XMLElement * pCondition = nullptr;
    pCondition = triggerElement->FirstChildElement("condition");
    while(pCondition) {
        Condition * c = new Condition(pCondition);
        this->conditions.push_back(c);
        pCondition = pCondition->NextSiblingElement("condition");
    }
    
    // Initial count
    this->times_used = 0;
}

Trigger::~Trigger( ) { }

/* Setter/Getter for command trigger bound to */
void Trigger::setCommand( std::string newCommand ) {
    command = newCommand;
    return;
}
std::string Trigger::getCommand( void ) {  return command;  }

/* Setter/Getter for print message displayed when trigger trigged */
void Trigger::setPrint( std::string printStr ) {
    this->print = printStr;
}
std::string Trigger::getPrint( void ) {  return print;  }

/* Setter/Getter for trigger ready status [not sure where used] */
void Trigger::setReady( bool value ) {
    ready = value;
    return;
}
void Trigger::setAction(std::string act) {
    this->action = act;
    return;
}
std::string Trigger::getAction() {
    return action;
}
bool Trigger::getReadyStatus( void ) {  return ready;  }

/* Setter/Getter for trigger mode (permanent or single[default]) */
void Trigger::changeMode( std::string newMode ) {
    if(newMode.compare("unlimited") == 0) {
        this->mode = newMode;
    } else if(newMode.compare("permanent") == 0) {
        this->mode = newMode;
    } else if(newMode.compare("single") == 0) {
        this->mode = newMode;
    } else {
        std::cout << "Unsupported mode: " << newMode << std::endl;
        return;
    }
    return;
}
std::string Trigger::getMode( void ) {  return mode;  }

/* Setter/Getter # times trigger has been trigged */
void Trigger::incrTimesUsed( void ) {
    this->times_used += 1;
    return;
}
int Trigger::getTimesUsed( void ) {  return times_used;  }

/* Getter for trigger conditions vector */
std::vector<Condition *> Trigger::getConditions( ) {
    return this->conditions;
}
