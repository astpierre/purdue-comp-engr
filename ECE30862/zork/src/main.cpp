#include "Component.h"
#include "Creature.h"
#include "Condition.h"
#include "Container.h"
#include "Game.h"
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


// Main entrypoint
int main(void) {
    /* GAME SETUP */
    Game * game = new Game("triggersample.xml");
    //game->ShowObjects( );

    /* RUN GAME */
    game->Play( );

    /* EXIT */
    return EXIT_SUCCESS;
}
