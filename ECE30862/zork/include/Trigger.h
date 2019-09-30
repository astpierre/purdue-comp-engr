#ifndef TRIGGER_H
#define TRIGGER_H
#include "Condition.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <tuple>
#include <string>
using namespace tinyxml2;


class Trigger {
public:
    Trigger( XMLElement * triggerElement );
    virtual ~Trigger( );

    virtual std::string getCommand( void );
    virtual bool getReadyStatus( void );
    virtual std::string getMode( void );
    virtual int getTimesUsed( void );
    virtual std::string getPrint( void );

    virtual void setCommand( std::string );
    virtual void setReady( bool );
    virtual void setPrint( std::string );
    virtual void changeMode( std::string );
    virtual void incrTimesUsed( );
    std::vector<Condition *> getConditions( );
    virtual std::string getAction(void);
    virtual void setAction(std::string);


private:
    std::string action = "";
    std::string command = "";
    std::string print = "";
    std::string mode = "single"; // Default
    int times_used = 0;
    bool ready = false;
    std::vector<Condition *> conditions;
};

#endif /* TRIGGER_H */
