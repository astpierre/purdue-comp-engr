#include "Game.h"
#include "Component.h"
#include "Creature.h"
#include "Condition.h"
#include "Container.h"
#include "Item.h"
#include "Room.h"
#include "Trigger.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <tuple>
#include <string>
using namespace tinyxml2;

/* Primary methods */
Game::~Game( ) { } /* Deconstructor */
Game::Game( const char * xmlfile ) { /* Constructor */
    /* Open XML file using tinyxml2 */
    XMLDocument doc;
    doc.LoadFile(xmlfile);

    /* Parse XML file */
    XMLNode * pRoot = doc.FirstChildElement("map"); // pRoot == <map>
    //~~ Populate all objects ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /******************************************************
     * For Rooms, Items, Containers, and Creatures, add
     * each to a member vector of Game and pass the XML
     * element to the respective constructor of each obj.
     * Each constructor will properly handle any meta-
     * field of the respective obj.
     *****************************************************/

    /* Rooms */
    XMLElement * pRoom = nullptr;
    pRoom = pRoot->FirstChildElement("room");
    while(pRoom) {
        Room * r = new Room(pRoom);
        this->rooms.push_back(r);
        pRoom = pRoom->NextSiblingElement("room");
    }

    /* Creatures */
    XMLElement * pCreature = nullptr;
    pCreature = pRoot->FirstChildElement("creature");
    while(pCreature) {
        Creature * c = new Creature(pCreature);
        this->creatures.push_back(c);
        pCreature = pCreature->NextSiblingElement("creature");
    }

    /* Items */
    XMLElement * pItem = nullptr;
    pItem = pRoot->FirstChildElement("item");
    while(pItem) {
        Item * item = new Item(pItem);
        this->items.push_back(item);
        pItem = pItem->NextSiblingElement("item");
    }

    /* Containers */
    XMLElement * pContainer = nullptr;
    pContainer = pRoot->FirstChildElement("container");
    while(pContainer) {
        Container * container = new Container(pContainer);
        this->containers.push_back(container);
        pContainer = pContainer->NextSiblingElement("container");
    }

}
void Game::ShowObjects( ) { /* Good debugging tool displays status */
    std::cout << "Displaying game components: "<<std::endl;
    for(auto i : this->rooms) {
        std::cout << "Room name: "<< i->getName( ) << std::endl;
        std::cout << "Room status: "<< i->getStatus( ) << std::endl;
        std::cout << "Room description: "<< i->getDescription( ) << std::endl;
        std::vector<std::string> iList = i->getItems( );
        std::cout << "Room items: ";
        for(auto j : iList) {
            std::cout << j << "  ";
        }
        std::cout << '\n';
        std::vector<std::string> conList = i->getContainers( );
        std::cout << "Room containers: ";
        for(auto j : conList) {
            std::cout << j << "  ";
        }
        std::cout << '\n';
        std::vector<std::string> creList = i->getCreatures( );
        std::cout << "Room creatures: ";
        for(auto j : creList) {
            std::cout << j << "  ";
        }
        std::cout << '\n';
        i->showBorders( );

        i->showTriggers( );
        std::cout << std::endl;
    }
    for(auto i : this->creatures) {
        std::cout << "Creature name: "<< i->getName( ) << std::endl;
        std::vector<std::string> vList = i->getVulnerabilities( );
        for(auto j : vList) {
            std::cout << "Creature vulnerability: "<< j << std::endl;
        }
        i->showTriggers( );
        std::cout << '\n';
    }
    for(auto i : this->items) {
        std::cout << "Item name: "<< i->getName( ) << std::endl;
        std::cout << "Item status: "<< i->getStatus( ) << std::endl;
        std::cout << "Item owner: "<< i->getOwner( ) << std::endl;
        std::cout << "Item turnon action: "<< i->getTurnOnAction( ) << std::endl;
        i->showTriggers( );
        std::cout << '\n';
    }
    for(auto i : this->containers) {
        std::cout << "Container name: "<< i->getName( ) << std::endl;
        std::cout << "Container status: "<< i->getStatus( ) << std::endl;
        std::cout << "Container description: "<< i->getDescription( ) << std::endl;
        std::vector<std::string> iList = i->getItems( );
        std::cout << "Container items: ";
        for(auto j : iList) {
            std::cout << j << "  ";
        }
        std::cout << '\n';
        i->showTriggers( );
    }
    std::cout << '\n';
}
void Game::Play( ) { /* Called afer constructing the game */
    curr_room = getRoomByName("Entrance"); // Games always start here
    std::cout <<"Current room: " << curr_room->getName() << '\n';
    std::cout << "Description: " << curr_room->getDescription() << '\n';
    std::string userInputStr = "";
    std::vector<std::string> userInputSplitted;
    std::string cmd = "";
    bool trigCheck = false;
    std::vector<Trigger *> trigs_ready;
    while(!game_over) { /* Handle user input. */
        std::cout << "\nEnter command: ";
        std::getline(std::cin, userInputStr);
        std::cout << std::endl;
        userInputSplitted = splitString(userInputStr, " ");
        cmd = userInputSplitted[0];

        if(checkInput(cmd)) {
            /* Do a preliminary check on triggers */
            trigs_ready = prelimTriggerCheck(userInputSplitted);
            trigCheck = trigs_ready.empty();
            if(trigCheck) {
                if(cmd == "i") { /* Display inventory */
                    displayInventory();

                } else if(moveCommand(cmd)) { /* Attempt to change room */
                    changeRoom(cmd);

                } else if(cmd == "take") { /* Attempt to add an item to inventory */
                    takeCommand(userInputSplitted);

                } else if(cmd == "open" && userInputSplitted[1] == "exit") { /* Attempt to exit game. */
                    if(curr_room->getType() == "exit") {
                        std::cout << "Game Over\n"; /* TODO: only exit if room type = 'exit' */

                        game_over = true;
                    } else {
                        std::cout << "Err: room not of type 'exit'" << '\n';
                    }
                } else if(cmd == "open") { /* Attempt to open a container. */
                    openCommand(userInputSplitted);

                } else if(cmd == "read") { /* Attempt to read writing on an item in inventory. */
                    readCommand(userInputSplitted);

                } else if(cmd == "drop") { /* Attempt to drop an item from inventory. */
                    dropCommand(userInputSplitted);

                } else if(cmd == "put") { /* Attempt to put an item in container. */
                    putCommand(userInputSplitted);

                } else if(cmd == "turn" && userInputSplitted[1] == "on") { /* Attempt to activate an item in inventory */
                    turnOnCommand(userInputSplitted);

                } else if(cmd == "attack") { /* Attempt to use an item on a creature. */
                    attackCommand(userInputSplitted);
                }

            } else if(!trigCheck) { /* Handle preliminary triggers */
                for(auto t : trigs_ready) {
                    handleTrigger(t);
                }
                trigCheck=false;
            }
            trigCheck = false;
            while(!trigCheck) {
                trigs_ready = postTriggerCheck();
                trigCheck = trigs_ready.empty();
                if(!trigCheck) { /* Handle post command execution triggers */
                    for(auto t : trigs_ready) {
                        handleTrigger(t);
                    }
                    trigs_ready = postTriggerCheck();
                    trigCheck = trigs_ready.empty();
                }
            }
        } else if(cmd == "q") { /* Quit game, game over. */
            std::cout << "Quitting game!" << std::endl;
            game_over = true;
        } else { /* Invalid command, prompt for user input again. */
            std::cout << "Invalid comand!" << std::endl;
        }
    }
}

/* Inventory methods */
bool Game::inventoryContains( std::string obj ) {
    for(auto i : this->inventory) {
        if(i == obj) return true;
    }
    return false;
}
void Game::addToInventory( std::string obj ) {
    this->inventory.push_back(obj);
}
void Game::removeFromInventory( std::string obj ) {
    for(unsigned i = 0; i < this->inventory.size(); i++) {
        if(this->inventory[i] == obj) {
            this->inventory.erase(this->inventory.begin()+i);
        }
    }
}
void Game::displayInventory( ) {
    unsigned int l = inventory.size();
    std::cout << "Inventory: ";
    for(auto i : this->inventory) {
        if(l == 1) {
            std::cout << i << '\n';
        } else {
            std::cout << i << ", ";
        }
        l -= 1;
    }
}

/* Game command methdos ( called from Game::Play() ) */
void Game::takeCommand( std::vector<std::string> cmdLine ) {
    std::string targetItemName = cmdLine[1];
    std::vector<std::string> roomItems = curr_room->getItems();
    std::vector<std::string> roomContainers = curr_room->getContainers();
    std::vector<std::string> containerAccepts;

    Item * targetItem = nullptr;
    Container * containerToCheck = nullptr;
    for(auto i : roomItems) {
        if(i == targetItemName) {
            targetItem = getItemByName(i);
            targetItem->setOwner("inventory");
            curr_room->removeItem(i);
            addToInventory(i);
            std::cout << "Added "<< i << " to inventory." << '\n';
            return;
        }
    }
    for(auto i : roomContainers) {
        containerToCheck = getContainerByName(i);
        if(containerToCheck->containerContains(targetItemName)) {
            if(containerToCheck->open == true) {
                if(containerToCheck->acceptAll) {
                    targetItem = getItemByName(targetItemName);
                    targetItem->setOwner("inventory");
                    containerToCheck->removeItem(targetItemName);
                    addToInventory(targetItemName);
                    std::cout << "Added "<< targetItemName << " to inventory." << '\n';
                    return;
                } else {
                    for(auto j : containerToCheck->accept) {
                        if(containerToCheck->containerContains(j)) {
                            targetItem = getItemByName(targetItemName);
                            targetItem->setOwner("inventory");
                            containerToCheck->removeItem(targetItemName);
                            addToInventory(targetItemName);
                            std::cout << "Added "<< targetItemName << " to inventory." << '\n';
                            return;
                        }
                    }
                }
            }
        }
    }
    std::cout << "Could not add "<<targetItemName<<" to your inventory." << '\n';
    std::cout << "Container must be open to take items from it..." << '\n';
    return;
}
void Game::openCommand( std::vector<std::string> cmdLine ) {
    std::string targetContainerName = cmdLine[1];
    std::vector<std::string> roomContainers = curr_room->getContainers();
    std::vector<std::string> containerItems;
    for(auto i : roomContainers) {
        if(i == targetContainerName) {
            Container * c = getContainerByName(i);
            if(c != nullptr) {
                c->open = true;
                if(c->acceptAll) {
                    if(c->items.empty()) {
                        std::cout << c->getName() << " is empty." << '\n';
                    } else {
                        std::cout << c->getName() <<" contains: ";
                        unsigned int l = c->items.size();
                        for(auto i : c->items) {
                            if(l == 1) {
                                std::cout << i << '\n';
                            } else {
                                std::cout << i << ", ";
                            }
                            l -= 1;
                        }
                    }

                    return;
            } else {
                for(auto k : c->accept) {
                    if(!c->containerContains(k)) {
                        std::cout << c->getName() <<" requires "<< k << " to be opened." << '\n';
                        return;
                    }
                }
                if(c->items.empty()) {
                    std::cout << c->getName() << " is empty." << '\n';
                } else {
                    std::cout  << c->getName() <<" contains: ";
                    unsigned int l = c->items.size();
                    for(auto i : c->items) {
                        if(l == 1) {
                            std::cout << i << '\n';
                        } else {
                            std::cout << i << ", ";
                        }
                        l -= 1;
                    }
                }
                c->open = true;
                return;

            }
        }
    }
}
}
void Game::dropCommand( std::vector<std::string> cmdLine ) {
    std::string itemName = cmdLine[1];
    if(inventoryContains(itemName)) {
        Item * itemObj = getItemByName(itemName);
        itemObj->setOwner(curr_room->getName());
        curr_room->addItem(itemName);
        removeFromInventory(itemName);
        std::cout << itemName <<" dropped." << '\n';
        return;
    } else {
        std::cout << "You do not have " << itemName << " in your inventory." << '\n';
        return;
    }
}
void Game::putCommand( std::vector<std::string> cmdLine ) {
    std::string itemName = cmdLine[1];
    std::string containerName = cmdLine[3];
    std::vector<std::string> room_containers = curr_room->getContainers();
    bool room_has_container = false;
    Container * targetContainer = nullptr;
    for(auto i : room_containers) {
        if(i == containerName) {
            room_has_container = true;
            targetContainer = getContainerByName(i);
        }
    }
    if(room_has_container == false) {
        std::cout << "Must be in same room as container to put items in it." << '\n';
        return;
    }

    if(inventoryContains(itemName)) {
        Item * itemObj = getItemByName(itemName);
        itemObj->setOwner(targetContainer->getName());
        targetContainer->addItem(itemName);
        removeFromInventory(itemName);
        std::cout << "Item " << itemName <<" added to " << targetContainer->getName() << "." << '\n';
        return;
    } else {
        std::cout << "You do not have " << itemName << " in your inventory." << '\n';
        return;
    }
}
void Game::turnOnCommand( std::vector<std::string> cmdLine ) {
    std::string itemName = cmdLine[2];
    Item * itemObj = nullptr;
    if(inventoryContains(itemName)) {
        itemObj = getItemByName(itemName);
        if(itemObj->getTurnOnPrint() == "NONE") {
            std::cout << "Item does not have a turn-on element." << '\n';
            return;
        }
        std::cout << itemObj->getTurnOnPrint() << '\n';
        itemObj->itemOn = true;
        handleAction(itemObj->getTurnOnAction());
        return;
    } else {
        std::cout << "You do not have " << itemName << " in your inventory." << '\n';
        return;
    }
}
void Game::attackCommand( std::vector<std::string> cmdLine ) {
    std::string itemName = cmdLine[3];
    std::string creatureName = cmdLine[1];
    std::vector<std::string> room_creatures = curr_room->getCreatures();
    bool roomHasCreature = false;
    bool creatureHasVulnerability = false;
    Creature * cToAttack = nullptr;
    if(inventoryContains(itemName)) {
        Item * itemObj = getItemByName(itemName);
    } else {
        std::cout << "You do not have " << itemName << " in your inventory." << '\n';
        return;
    }
    for(auto c : room_creatures) {
        if(c == creatureName) {
            roomHasCreature = true;
            cToAttack = getCreatureByName(c);
        }
    }
    if(roomHasCreature == false) {
        std::cout << "The creature must be in the same room as you." << '\n';
        return;
    }
    std::vector<std::string> cVulnerabilities = cToAttack->getVulnerabilities();
    for(auto v : cVulnerabilities) {
        if(v == itemName) {
            creatureHasVulnerability = true;
        }
    }
    if(creatureHasVulnerability == false) {
        std::cout << "Creature is not vulnerable to this attack." << '\n';
        return;
    }
    std::vector<Condition *> attackConds = cToAttack->getAttackConditions();
    std::vector<std::string> attackActions = cToAttack->getAttackActions();
    for(auto c : attackConds) {
        if(checkAttackCondition(c) == false) {
            std::cout << "Creature is not vulnerable to this attack." << '\n';
            return;
        }
    }
    std::cout << cToAttack->getAttackPrint() << '\n';
    for(auto a : attackActions) {
        handleAction(a);
    }
}
void Game::readCommand( std::vector<std::string> cmdLine ) {
    std::string itemName = cmdLine[1];
    if(inventoryContains(itemName)) {
        Item * itemObj = getItemByName(itemName);
        if(itemObj->getWriting() == "NONE") {
            std::cout << "Nothing written on item." << '\n';
            return;
        } else {
            std::cout << itemObj->getWriting() << '\n';
            return;
        }
    } else {
        std::cout << "You do not have " << itemName << " in your inventory." << '\n';
        return;
    }
}
bool Game::moveCommand( std::string cmd ) {
    for(auto i : this->movement_commands) {
        if(i == cmd) return true;
    }
    return false;
}
void Game::changeRoom( std::string cmd ) {
    std::string dir = "";
    std::string rName = "";
    std::string targetDir = "";

    if(cmd == "n") targetDir = "north";
    else if(cmd == "s") targetDir = "south";
    else if(cmd == "e") targetDir = "east";
    else if(cmd == "w") targetDir = "west";

    std::vector<std::tuple<std::string, std::string>> brdrs = curr_room->getBorders();
    for(auto i : brdrs) {
        std::tie(dir, rName) = i;
        if(targetDir == dir) {
            curr_room = getRoomByName(rName);
            std::cout  <<"Current room: " << rName << '\n';
            std::cout  << "Description: " << curr_room->getDescription() << "\n";
            return;
        }
    }
    std::cout << "Cannot go that direction." << "\n";
}

/* Helper methods when looking for game components */
Room * Game::getRoomByName( std::string roomName ) {
    for(auto i : this->rooms) {
        if(i->getName() == roomName) return i;
    }
    return nullptr;
}
Item * Game::getItemByName( std::string itemName ) {
    for(auto i : this->items) {
        if(i->getName() == itemName) return i;
    }
    return nullptr;
}
Container * Game::getContainerByName( std::string containerName ) {
    for(auto i : this->containers) {
        if(i->getName() == containerName) return i;
    }
    return nullptr;
}

Creature * Game::getCreatureByName( std::string creatureName ) {
    for(auto i : this->creatures) {
        if(i->getName() == creatureName) return i;
    }
    return nullptr;
}
std::string Game::searchAllForType(std::string objName) {
    if(getRoomByName(objName) != nullptr) return "room";
    if(getCreatureByName(objName) != nullptr) return "creature";
    if(getContainerByName(objName) != nullptr) return "container";
    if(getItemByName(objName) != nullptr) return "item";
    return "NONE";
}
Component * Game::getGameComponent( std::string componentName ) {
    for(auto i : this->rooms) {
        if(i->getName() == componentName) return i;
    }
    for(auto i : this->items) {
        if(i->getName() == componentName) return i;
    }
    for(auto i : this->containers) {
        if(i->getName() == componentName) return i;
    }
    for(auto i : this->creatures) {
        if(i->getName() == componentName) return i;
    }
    return nullptr;
}

//~~ Checking for triggers ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/******************************************************
 * === PRELIM ===
 * After a user enters a command, the prelim trig check
 * is called that scans over all contextually related
 * objects for triggers. This trig check looks for
 * triggers that have a command attribute. If the
 * command matches the user's command, and if the
 * condition(s) is/are met, we add that trigger to a
 * vector and process all triggers in that vector.
 * === POST ===
 * After the user's command is handled, the post trig
 * check looks over all triggers in the current
 * context and checks their conditions. Similarly, if
 * conditions are met we add the trigger object to a
 * vector and return that vector and process each
 * trigger inside it.
 *****************************************************/
std::vector<Trigger *> Game::prelimTriggerCheck( std::vector<std::string> cmdLine ) {
    /* Get context */
    std::vector<std::string> curr_creatures = curr_room->getCreatures();
    std::vector<std::string> curr_containers = curr_room->getContainers();
    std::vector<std::string> curr_items = curr_room->getItems();
    curr_items.insert(curr_items.end(), inventory.begin(), inventory.end());
    std::vector<Trigger *> trigger_vector;
    std::vector<Trigger *> triggers_ready;
    //std::cout << "prelimTriggerCheck(): begin" << '\n';

    /* Check creature triggers */
    if(!curr_creatures.empty()) {
        for(auto i : curr_creatures){
            Component * c = getGameComponent(i);
            if(c != nullptr) {
                trigger_vector = c->getTriggers();
                if(!trigger_vector.empty()) {
                    for(auto j : trigger_vector) {
                        if(j->getCommand() == cmdLine[0]) {
                            if(trigValid(j)) {
                                if(checkConditions(j)) {
                                    triggers_ready.push_back(j);
                                    j->incrTimesUsed();
                                }
                            }
                        }
                    }
                }
            }

        }
    }
    //std::cout << "prelimTriggerCheck(): completed creature checks" << '\n';

    /* Check current room triggers */
    trigger_vector = curr_room->getTriggers();
    if(!trigger_vector.empty()) {
        for(auto j : trigger_vector) {
            if(j->getCommand() == cmdLine[0]) {
                if(trigValid(j)) {
                    if(checkConditions(j)) {
                        triggers_ready.push_back(j);
                        j->incrTimesUsed();
                    }
                }
            }
        }
    }
    //std::cout << "prelimTriggerCheck(): completed room checks" << '\n';

    /* Check container triggers */
    if(!curr_containers.empty()) {
        for(auto i : curr_containers){
            Component * c = getGameComponent(i);
            if(c != nullptr) {
                trigger_vector = c->getTriggers();
                if(!trigger_vector.empty()) {
                    for(auto j : trigger_vector) {
                        if(j->getCommand() == cmdLine[0]) {
                            if(trigValid(j)) {
                                if(checkConditions(j)) {
                                    triggers_ready.push_back(j);
                                    j->incrTimesUsed();
                                }
                            }
                        }
                    }
                }
            }

        }
    }
    //std::cout << "prelimTriggerCheck(): completed container checks" << '\n';

    /* Check item triggers */
    if(!curr_items.empty()) {
        for(auto i : curr_items) {
            Component * it = getGameComponent(i);
            if(it != nullptr) {
                trigger_vector = it->getTriggers();
                if(!trigger_vector.empty()) {
                    for(auto j : trigger_vector) {
                        if(j->getCommand() == cmdLine[0]) {
                            if(trigValid(j)) {
                                if(checkConditions(j)) {
                                    triggers_ready.push_back(j);
                                    j->incrTimesUsed();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //std::cout << "prelimTriggerCheck(): completed item checks" << '\n';

    //std::cout << "prelimTriggerCheck(): end" << '\n';

    return triggers_ready;
}
std::vector<Trigger *> Game::postTriggerCheck( ) {
    /* Get context */
    std::vector<std::string> curr_creatures = curr_room->getCreatures();
    std::vector<std::string> curr_containers = curr_room->getContainers();
    std::vector<std::string> curr_items = curr_room->getItems();
    curr_items.insert(curr_items.end(), inventory.begin(), inventory.end());
    std::vector<Trigger *> trigger_vector;
    std::vector<Trigger *> triggers_ready;
    //std::cout << "postTriggerCheck(): begin" << '\n';

    /* Check current room triggers */
    trigger_vector = curr_room->getTriggers();
    for(auto j : trigger_vector) {
        if(j->getCommand() == "NONE") {
            if(trigValid(j)) {
                if(checkConditions(j)) {
                    triggers_ready.push_back(j);
                    j->incrTimesUsed();
                }
            }
        }
    }
    //std::cout << "postTriggerCheck(): completed rooms" << '\n';

    /* Check creature triggers */
    if(!curr_creatures.empty()) {
        for(auto i : curr_creatures) {
            //Creature * c = getCreatureByName(i);
            Component * c = getGameComponent(i);
            if(c != nullptr) {
                trigger_vector = c->getTriggers();
                for(auto j : trigger_vector) {
                    if(j->getCommand() == "NONE") {
                        if(trigValid(j)) {
                            if(checkConditions(j)) {
                                triggers_ready.push_back(j);
                                j->incrTimesUsed();
                            }
                        }
                    }
                }
            }
        }
    }
    //std::cout << "postTriggerCheck(): completed creatures" << '\n';

    /* Check container triggers */
    if(!curr_containers.empty()) {
        for(auto i : curr_containers) {
            //Container * c = getContainerByName(i);
            Component * c = getGameComponent(i);
            if(c != nullptr) {
                trigger_vector = c->getTriggers();
                for(auto j : trigger_vector) {
                    if(j->getCommand() == "NONE") {
                        if(trigValid(j)) {
                            if(checkConditions(j)) {
                                triggers_ready.push_back(j);
                                j->incrTimesUsed();
                            }
                        }
                    }
                }
            }
        }
    }
    //std::cout << "postTriggerCheck(): completed containers" << '\n';

    /* Check item triggers */
    if(!curr_items.empty()) {
        for(auto i : curr_items) {
            //Item * it = getItemByName(i);
            Component * it = getGameComponent(i);
            if(it != nullptr) {
                trigger_vector = it->getTriggers();
                for(auto j : trigger_vector) {
                    if(j->getCommand() == "NONE") {
                        if(trigValid(j)) {
                            if(checkConditions(j)) {
                                triggers_ready.push_back(j);
                                j->incrTimesUsed();
                            }
                        }
                    }
                }
            }
        }
    }
    //std::cout << "postTriggerCheck(): completed items" << '\n';

    return triggers_ready;
}

/* Helper methods for trigger related tasks */
bool Game::checkConditions(Trigger * t) {
    std::vector<Condition *> condition_vector = t->getConditions();
    if(condition_vector.empty()) return true;
    Component * baseComp = nullptr;
    std::string owner = "";
    Container * c = nullptr;
    Item * o = nullptr;
    for(auto k : condition_vector) {
        if(k->getStatus() != "NONE") {
            baseComp = getGameComponent(k->getObject());
            if(baseComp->getStatus() == k->getStatus()) return true;
            else return false;
        }
    }
    for(auto k : condition_vector) {
        if(k->getHas() == "yes") {
            owner = k->getOwner();
            if(owner == "inventory") {
                if(inventoryContains(k->getObject())) return true;
                else return false;
            } else {
                c = getContainerByName(owner);
                o = getItemByName(k->getObject());
                if(c) {
                    if(c->getName() == o->getOwner()) return true;
                    else return false;
                }
            }
        } else if(k->getHas() == "no") {
            owner = k->getOwner();
            if(owner == "inventory") {
                if(!inventoryContains(k->getObject())) return true;
                else return false;
            } else {
                c = getContainerByName(owner);
                o = getItemByName(k->getObject());
                if(c) {
                    if(c->getName() != o->getOwner()) return true;
                    else return false;
                }
            }
        }
    }
    return false;
}
bool Game::checkAttackCondition(Condition * cond) {
    Component * baseComp = nullptr;
    std::string owner = "";
    Container * c;
    Item * o;

    if(cond->getStatus() != "NONE") {
        baseComp = getGameComponent(cond->getObject());
        if(baseComp->getStatus() == cond->getStatus()) return true;
        else return false;
    }

    if(cond->getHas() == "yes") {
        owner = cond->getOwner();
        if(owner == "inventory") {
            if(inventoryContains(cond->getObject())) return true;
            else return false;
        } else {
            c = getContainerByName(owner);
            o = getItemByName(cond->getObject());
            if(c) {
                if(c->getName() == o->getOwner()) return true;
                else return false;
            }
        }
    } else if(cond->getHas() == "no") {
        owner = cond->getOwner();
        if(owner == "inventory") {
            if(!inventoryContains(cond->getObject())) return true;
            else return false;
        } else {
            c = getContainerByName(owner);
            o = getItemByName(cond->getObject());
            if(c) {
                if(c->getName() != o->getOwner()) return true;
                else return false;
            }
        }
    }
    return false;
}
bool Game::trigValid(Trigger * t) {
    //std::cout << "trigValid(t)" << '\n';
    std::string mode = t->getMode();
    int nTimesUsed = t->getTimesUsed();
    if(mode == "unlimited" || mode == "permanent") {
        return true;
    }
    else if(nTimesUsed < 1) {
        return true;
    }
    return false;
}
void Game::handleTrigger(Trigger * t) {
    //std::cout << "handleTrigger(t)" << '\n';
    std::cout << t->getPrint() << '\n';
    std::vector<std::string> triggerActionSplitted;
    if(t->getAction() == "NONE") return;
    triggerActionSplitted = splitString(t->getAction(), " ");
    std::string cmd = "";
    if(triggerActionSplitted[0] == "Update") { /* Update status of object */
        Component * baseComp = getGameComponent(triggerActionSplitted[1]);
        baseComp->setStatus(triggerActionSplitted[3]);

    } else if(triggerActionSplitted[0] == "Add") {
        Room * targetRoom = getRoomByName(triggerActionSplitted[3]);
        Container * targetContainer = getContainerByName(triggerActionSplitted[3]);
        if(targetRoom) {
            Item * newItem = getItemByName(triggerActionSplitted[1]);
            newItem->setOwner(targetRoom->getName());
            targetRoom->addItem(newItem->getName());
        } else if(targetContainer) {
            Item * newItem = getItemByName(triggerActionSplitted[1]);
            newItem->setOwner(targetContainer->getName());
            targetContainer->addItem(newItem->getName());
        }
    } else if(triggerActionSplitted[0] == "Delete") {
        //Removes that object from the current room
        std::string delObjectType = searchAllForType(triggerActionSplitted[1]);
        if(delObjectType == "creature") {
            curr_room->removeCreature(triggerActionSplitted[1]);
        }
        else if (delObjectType == "container"){
            curr_room->removeContainer(triggerActionSplitted[1]);
        }
        else if (delObjectType == "item"){
            curr_room->removeItem(triggerActionSplitted[1]);
        }
    }
}
void Game::handleAction( std::string actionStr ) {
    std::vector<std::string> actionSplitted = splitString(actionStr, " ");
    if(actionSplitted[0] == "Update") { /* Update status of object */
        std::string objType = searchAllForType(actionSplitted[1]);
        if(objType == "room") {
            Room * r = getRoomByName(actionSplitted[1]);
            r->setStatus(actionSplitted[3]);
        } else if(objType == "item") {
            Item * i = getItemByName(actionSplitted[1]);
            i->setStatus(actionSplitted[3]);
        } else if(objType == "creature") {
            Creature * c = getCreatureByName(actionSplitted[1]);
            c->setStatus(actionSplitted[3]);
        } else if(objType == "container") {
            Container * cn = getContainerByName(actionSplitted[1]);
            cn->setStatus(actionSplitted[3]);
        }

    } else if(actionSplitted[0] == "Add") {
        Room * targetRoom = getRoomByName(actionSplitted[3]);
        Container * targetContainer = getContainerByName(actionSplitted[3]);
        if(targetRoom) {
            Item * newItem = getItemByName(actionSplitted[1]);
            newItem->setOwner(targetRoom->getName());
            targetRoom->addItem(newItem->getName());
        } else if(targetContainer) {
            Item * newItem = getItemByName(actionSplitted[1]);
            newItem->setOwner(targetContainer->getName());
            targetContainer->addItem(newItem->getName());
        }

    } else if(actionSplitted[0] == "Delete") {
        //Identifies type and removes that object from the current room
        std::string delObjectType = searchAllForType(actionSplitted[1]);
        if(delObjectType == "creature") {
            curr_room->removeCreature(actionSplitted[1]);
        }
        else if (delObjectType == "container"){
            curr_room->removeContainer(actionSplitted[1]);
        }
        else if (delObjectType == "item"){
            curr_room->removeItem(actionSplitted[1]);
        }
    }
    else if(moveCommand(actionSplitted[0])) { /* Attempt to change room */
            changeRoom(actionSplitted[0]);
    } else if(actionSplitted[0] == "drop") {
        dropCommand(actionSplitted);
    }

}

/* Utilities */
bool Game::checkInput( std::string userInput ) {
    for(auto i : this->game_commands) {
        if(i == userInput) return true;
    }
    return false;
}
std::vector<std::string> Game::splitString(const std::string s, const std::string delim) {
    std::vector<std::string> splitted;
    size_t prev=0, pos=0;
    do {
        pos = s.find(delim, prev);
        if(pos == std::string::npos) pos = s.length();
        std::string spl = s.substr(prev, pos-prev);
        if(!spl.empty()) splitted.push_back(spl);
        prev = pos + delim.length();
    } while(pos < s.length() && prev < s.length());
    return splitted;
}
