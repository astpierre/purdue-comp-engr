#ifndef CREATURE_H
#define CREATURE_H

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


class Creature: public Component {
public:
    Creature(XMLElement *);

    virtual ~Creature();

    std::vector<std::string> getVulnerabilities();

    std::string getAttackPrint();

    void addVulnerability(std::string);

    bool hasVulnerability(std::string);

    void addAttackAction(std::string);

    std::vector<std::string> getAttackActions();

    std::vector<Condition *> getAttackConditions();
private:
    std::vector<std::string> vulnerabilities;
    std::vector<Condition *> attackConditions;
    std::vector<std::string> attackActions;
    std::string attackPrint;

};

#endif /* CREATURE_H */
