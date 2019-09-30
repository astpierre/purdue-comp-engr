#include "Room.h"
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

/* Constructor/Destructor for Room */
Room::Room( XMLElement * roomElement ) {
    /* Room name, status, description, type */
    if(roomElement->FirstChildElement("name") != nullptr) {
        setName(roomElement->FirstChildElement("name")->GetText());
    } else {
        setName("NONE");
    }
    if(roomElement->FirstChildElement("status") != nullptr) {
        setStatus(roomElement->FirstChildElement("status")->GetText());
    } else {
        setStatus("NONE");
    }
    if(roomElement->FirstChildElement("description") != nullptr) {
        setDescription(roomElement->FirstChildElement("description")->GetText());
    } else {
        setDescription("NONE");
    }
    if(roomElement->FirstChildElement("type") != nullptr) {
        setType(roomElement->FirstChildElement("type")->GetText());
    }

    /* Room borders */
    XMLElement * pBorders = nullptr;
    pBorders = roomElement->FirstChildElement("border");
    while(pBorders) {
        std::string direction = pBorders->FirstChildElement("direction")->GetText();
        std::string roomName = pBorders->FirstChildElement("name")->GetText();
        addBorder(direction, roomName);
        pBorders = pBorders->NextSiblingElement("border");
    }

    /* Room items */
    XMLElement * pItems = nullptr;
    pItems = roomElement->FirstChildElement("item");
    while(pItems) {
        addItem(pItems->GetText( ));
        pItems = pItems->NextSiblingElement("item");
    }

    /* Room triggers */
    XMLElement * pTrigger = nullptr;
    pTrigger = roomElement->FirstChildElement("trigger");
    while(pTrigger) {
        Trigger * t = new Trigger(pTrigger);
        addTrigger(t);
        pTrigger = pTrigger->NextSiblingElement("trigger");
    }

    /* Room creatures */
    XMLElement * pCreature = nullptr;
    pCreature = roomElement->FirstChildElement("creature");
    while(pCreature) {
        addCreature(pCreature->GetText( ));
        pCreature = pCreature->NextSiblingElement("creature");
    }

    /* Room containers */
    XMLElement * pContainer = nullptr;
    pContainer = roomElement->FirstChildElement("container");
    while(pContainer) {
        addContainer(pContainer->GetText( ));
        pContainer = pContainer->NextSiblingElement("container");
    }
}

Room::~Room( ) { }

/* Setter/Getter for Items */
void Room::addItem( std::string item ) {
    this->items.push_back(item);
}
void Room::removeItem( std::string item ) {
    for(unsigned i = 0; i < this->items.size(); i++) {
        if(this->items[i] == item) {
            this->items.erase(this->items.begin()+i);
        }
    }
}
std::vector<std::string> Room::getItems( ) {
    return this->items;
}

/* Setter/Getter for room type */
void Room::setType( std::string type ) {
    this->roomType = type;
}
std::string Room::getType( ) {
    return this->roomType;
}

/* Setter/Getter for Containers */
void Room::addContainer( std::string container ) {
    this->containers.push_back(container);
}
void Room::removeContainer( std::string container ) {
    for(unsigned i = 0; i < this->containers.size(); i++) {
        if(this->containers[i] == container) {
            this->containers.erase(this->containers.begin()+i);
        }
    }
}
std::vector<std::string> Room::getContainers( ) {
    return this->containers;
}

/* Setter/Getter for Creatures */
void Room::addCreature( std::string creature ) {
    this->creatures.push_back(creature);
}
void Room::removeCreature( std::string creature ) {
    for(unsigned i = 0; i < this->creatures.size(); i++) {
        if(this->creatures[i] == creature) {
            this->creatures.erase(this->creatures.begin()+i);
        }
    }
}
std::vector<std::string> Room::getCreatures( ) {
    return this->creatures;
}

/* Setter/Getter + Methods for room borders */
std::vector<std::tuple<std::string, std::string>> Room::getBorders( ) {
    return this->borders;
}
void Room::showBorders( ) {
    std::string dir = "";
    std::string rName = "";
    for(auto i : this->borders) {
        std::tie(dir, rName) = i;
        std::cout << "Bordering room: " << rName << " | In direction:" << dir << '\n';
    }
}
void Room::addBorder( std::string dir, std::string name ) {
    std::tuple<std::string, std::string> newBorder = std::make_tuple(dir, name);
    this->borders.push_back(newBorder);
}
std::string Room::checkBorder( std::string direction ) {
    std::string dir = "";
    std::string rName = "";
    for(auto i : this->borders) {
        std::tie(dir, rName) = i;
        if(direction == dir) {
            return rName;
        }
    }
    return "NONE";
}
