#ifndef COMPONENT_H
#define COMPONENT_H
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


class Component {
public:
    Component( );
    virtual ~Component( );

    virtual std::string getName( void );
    virtual std::string getStatus( void );
    virtual std::string getDescription( void );

    virtual void setName( std::string );
    virtual void setStatus( std::string );
    virtual void setDescription( std::string );
    virtual void addTrigger( Trigger * );
    virtual void showTriggers( );
    std::vector<Trigger *> getTriggers( );

private:
    std::string name = "";
    std::string status = "";
    std::string description = "";
    std::vector<Trigger *> triggers;
};

#endif /* COMPONENT_H */
