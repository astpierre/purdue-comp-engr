#ifndef ITEM_H
#define ITEM_H
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


class Item: public Component {
public:
    Item( );
    Item( XMLElement * );
    virtual ~Item( );

    void setOwner( std::string );
    std::string getOwner( );

    void setWriting( std::string );
    std::string getWriting( );

    void setTurnOnPrint( std::string );
    std::string getTurnOnPrint( );

    void setTurnOnAction( std::string );
    std::string getTurnOnAction( );

    bool itemOn = false;

private:
    std::string owner = "";
    std::string writing = "";
    std::string turn_on_print = "";
    std::string turn_on_action = "";
};

#endif /* ITEM_H */
