#ifndef GAME_H
#define GAME_H
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


class Game {
public:
	Game( const char * xmlfile );
	virtual ~Game( );
	void ShowObjects( );
	void Play( );

	void addToInventory( std::string obj );
	void displayInventory( );
	bool inventoryContains( std::string obj );
	void removeFromInventory(std::string obj);

	Room * getRoomByName( std::string roomName );
	Item * getItemByName( std::string itemName );
	Container * getContainerByName( std::string containerName );
	Creature * getCreatureByName( std::string creatureName );
	Component * getGameComponent(std::string n);
	std::string searchAllForType( std::string objName );

	void takeCommand( std::vector<std::string> cmdLine );
	void openCommand( std::vector<std::string> cmdLine );
	void dropCommand( std::vector<std::string> cmdLine );
	void readCommand( std::vector<std::string> cmdLine );
	void putCommand( std::vector<std::string> cmdLine );
	void attackCommand( std::vector<std::string> cmdLine );
	void turnOnCommand( std::vector<std::string> cmdLine );
	bool moveCommand( std::string cmd );
	void changeRoom( std::string cmd );

	std::vector<Trigger *> prelimTriggerCheck( std::vector<std::string> cmdLine );
	std::vector<Trigger *> postTriggerCheck( );

	void handleTrigger(Trigger * t);
	void handleAction( std::string actionStr );
	bool trigValid(Trigger * t);
	bool checkConditions(Trigger * t);
	bool checkAttackCondition(Condition *);

	bool checkInput( std::string userInput );
	std::vector<std::string> splitString( const std::string s, const std::string delim );

	/* Game attributes / variables */
	std::vector<Room *> rooms;
	std::vector<Item *> items;
    std::vector<Container *> containers;
	std::vector<Creature *> creatures;
	bool game_over = false;
	std::vector<std::string> inventory;
	std::vector<std::string> game_commands = {  "n", "s", "e", "w", "i",
                                    			"take", "open", "open exit",
                                    			"read", "drop", "put", "turn", "attack"
                                 			 };
	std::vector<std::string> movement_commands = { "n", "s", "e", "w" };
	Room * curr_room = nullptr;
};

#endif /* GAME_H */
