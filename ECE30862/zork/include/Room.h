#ifndef ROOM_H
#define ROOM_H
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


class Room: public Component {
public:
    Room( XMLElement * );
    virtual ~Room( );

    virtual void addItem( std::string item );
    virtual void removeItem( std::string item );
    virtual std::vector<std::string> getItems( );

    virtual void setType( std::string type );
    virtual std::string getType( );

    virtual void addContainer( std::string container );
    virtual void removeContainer( std::string container );
    virtual std::vector<std::string> getContainers( );

    virtual void addCreature( std::string creature );
    virtual void removeCreature( std::string creature );
    virtual std::vector<std::string> getCreatures( );

    void addBorder( std::string dir, std::string name );
    std::string checkBorder( std::string dir );
    void showBorders( );
    std::vector<std::tuple<std::string, std::string>> getBorders( );

private:
    std::string roomType = "regular";
    std::vector<std::string> items;
    std::vector<std::string> containers;
    std::vector<std::string> creatures;
    std::vector<std::tuple<std::string, std::string>> borders;
};

#endif /* ROOM_H */
