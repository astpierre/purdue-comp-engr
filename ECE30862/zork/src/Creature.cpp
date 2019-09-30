#include "Creature.h"
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

/* Constructor/Destructor for Creature */
Creature::Creature( XMLElement * creatureElement ) {
    /* Creature name */
    if(creatureElement->FirstChildElement("name") != nullptr) {
        setName(creatureElement->FirstChildElement("name")->GetText());
    } else {
        setName("NONE");
    }

    /* Creature vulnerabilities */
    XMLElement * pVulnerability = nullptr;
    pVulnerability = creatureElement->FirstChildElement("vulnerability");
    while(pVulnerability) {
        this->vulnerabilities.push_back(pVulnerability->GetText( ));
        pVulnerability = pVulnerability->NextSiblingElement("vulnerability");
    }

    /* Stores attack object */
    XMLElement * pAttack = nullptr;
    pAttack = creatureElement->FirstChildElement("attack");
    XMLElement * pCondition = nullptr;
    XMLElement * pAction = nullptr;
    while(pAttack) {
        pCondition = pAttack->FirstChildElement("condition");
        while(pCondition) {
            Condition * c = new Condition(pCondition);
            this->attackConditions.push_back(c);
            pCondition = pCondition->NextSiblingElement("condition");
        }

        this->attackPrint = (pAttack->FirstChildElement("print")->GetText());

        pAction = pAttack->FirstChildElement("action");
        while(pAction) {
            this->attackActions.push_back(pAction->GetText());
            pAction = pAction->NextSiblingElement("action");
        }
        pAttack = pAttack->NextSiblingElement("attack");
    }

    /* Creature triggers */
    XMLElement * pTrigger = nullptr;
    pTrigger = creatureElement->FirstChildElement("trigger");
    while(pTrigger) {
        Trigger * t = new Trigger(pTrigger);
        addTrigger(t);
        pTrigger = pTrigger->NextSiblingElement("trigger");
    }

    return;
}

Creature::~Creature( ) { }

/* Setter/Getter for Vulnerabilities */
void Creature::addVulnerability( std::string vul ) {
    this->vulnerabilities.push_back(vul);
}
bool Creature::hasVulnerability( std::string vul ) {
    for(auto i : this->vulnerabilities) {
        if(i == vul) return true;
    }
    return false;
}
std::vector<std::string> Creature::getVulnerabilities( ) {
    return this->vulnerabilities;
}

/* Setter/Getter + Methods for Attack related tasks */
void Creature::addAttackAction( std::string action ) {
    this->attackActions.push_back(action);
}
std::vector<std::string> Creature::getAttackActions( ) {
    return this->attackActions;
}
std::string Creature::getAttackPrint(){
    return this->attackPrint;
}
std::vector<Condition *> Creature::getAttackConditions( ) {
    return this->attackConditions;
}
