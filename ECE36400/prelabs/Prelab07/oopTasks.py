###############################################################################
#   Author:	Andrew St. Pierre
#   email: 	astpier@purdue.edu
#   ID: 	ee364b17
#   Date: 	Thursday, February 21, 2019
###############################################################################

import os
import sys
import itertools
from enum import Enum
from pprint import pprint as pp

# Required methods / classes
class Level(Enum):
    Freshman = 1
    Sophomore = 2
    Junior = 3
    Senior = 4
class ComponentType(Enum):
    Resistor = 1
    Capacitor = 2
    Inductor = 3
    Transistor = 4
class Student:
    # special methods
    def __init__(self, id, firstName, lastName, level):
        # attributes -- member vars -- fields -- properties
        self.id = id
        self.firstName = firstName
        self.lastName = lastName
        self._validateLevel(level)

    def _validateLevel(self, level):
        if not isinstance(level, Level):
            raise TypeError("The argument must be an instance of the 'Level' Enum")
        else: self.level = level

    def __str__(self):
        return f"{self.id}, {self.firstName} {self.lastName}, {self.level.name}"
class Component:
    # special methods
    def __init__(self, id, price, ctype):
        # attributes -- member vars -- fields -- properties
        self.id = id
        self.price = price
        self._validateType(ctype)

    def _validateType(self, ctype):
        if not isinstance(ctype, ComponentType):
            raise TypeError("The argument must be an instance of the 'ComponentType' Enum")
        else: self.ctype = ctype

    def __str__(self):
        return f"{self.ctype.name}, {self.id}, ${format(self.price, '.2f')}"

    def __hash__(self):
        return hash(self.id)
class Circuit:
    # special methods
    def __init__(self, id, components):
        # attributes -- member vars -- fields -- properties
        self.id = id
        self._validateComponents(components)

    def _validateComponents(self, components):
        self.components = set()
        for comp in components:
            if not isinstance(comp, Component):
                raise TypeError("The argument must be an instance of the 'Component' Class")
            else: self.components.add(comp)
        self._updateCost()
        self._updateComponentTypes()

    def __str__(self):
        return f"{self.id}: (R = {self.numR}, C = {self.numC}, I = {self.numI}, T = {self.numT}), Cost = ${format(self.cost, '.2f')}"

    def __contains__(self, component):
        if not isinstance(component, Component):
            raise TypeError("The argument must be an instance of the 'Component' Class")
        return value in self.components

    def _updateCost(self):
        self.cost = 0.0
        for comp in self.components:
            self.cost += comp.price

    def _updateComponentTypes(self):
        self.numR = 0
        self.numC = 0
        self.numI = 0
        self.numT = 0
        for comp in self.components:
            if comp.ctype.name == "Resistor":
                self.numR += 1
            elif comp.ctype.name == "Capacitor":
                self.numC += 1
            elif comp.ctype.name == "Transistor":
                self.numT += 1
            elif comp.ctype.name == "Inductor":
                self.numI += 1
        return

    def __add__(self, anotherComponent):
        if not isinstance(anotherComponent, Component):
            raise TypeError("The argument must be an instance of the 'Component' Class")
        if anotherComponent in self.components:
            return self
        self.components.add(anotherComponent)
        self._updateCost()
        self._updateComponentTypes()
        return self

    def __sub__(self, anotherComponent):
        if not isinstance(anotherComponent, Component):
            raise TypeError("The argument must be an instance of the 'Component' Class")
        if anotherComponent not in self.components:
            return self
        self.components.remove(anotherComponent)
        self._updateCost()
        self._updateComponentTypes()
        return self

    def __eq__(self, anotherCircuit):
        if not isinstance(anotherCircuit, Circuit):
            raise TypeError("The argument must be an instance of the 'Circuit' Class")
        return self.cost == anotherCircuit.cost

    def __lt__(self, anotherCircuit):
        if not isinstance(anotherCircuit, Circuit):
            raise TypeError("The argument must be an instance of the 'Circuit' Class")
        return self.cost < anotherCircuit.cost

    def __gt__(self, anotherCircuit):
        if not isinstance(anotherCircuit, Circuit):
            raise TypeError("The argument must be an instance of the 'Circuit' Class")
        return self.cost > anotherCircuit.cost
class Project:
    # special methods
    def __init__(self, id, participants, circuits):
        # attributes -- member vars -- fields -- properties
        self.id = id
        self._validateParticipants(participants)
        self._validateCircuits(circuits)
    def _validateParticipants(self, participants):
        self.participants = []
        for p in participants:
            if not isinstance(p, Student):
                raise TypeError("The argument must be an instance of the 'Student' Class")
            else: self.participants.append(p)
    def _validateCircuits(self, circuits):
        self.circuits = []
        for c in circuits:
            if not isinstance(c, Circuit):
                raise TypeError("The argument must be an instance of the 'Circuit' Class")
            else: self.circuits.append(c)
        self._updateCost()
    def __str__(self):
        return f"{self.id}: ({len(self.circuits)} Circuits, {len(self.participants)} Participants), Cost = ${format(self.cost, '.2f')}"
    def _updateCost(self):
        self.cost = 0.0
        for circuit in self.circuits:
            self.cost += circuit.cost
    def __contains__(self, object):
        if isinstance(object, Component):
            allComponents = [circuit.components for circuit in self.circuits]
            allComponents = list(itertools.chain(*allComponents))
            return object in allComponents
        elif isinstance(object, Student):
            allStudentIDs = [student.id for student in self.participants]
            return object.id in allStudentIDs
        elif isinstance(object, Circuit):
            allCircuitIDs = [circuit.id for circuit in self.circuits]
            return object.id in allCircuitIDs
        else:
            raise TypeError("The argument must be an instance of the 'Component', 'Student', or 'Circuit' Class")
    def __add__(self, object):
        if isinstance(object, Circuit):
            if object in self.circuits:
                return self

            self.circuits.append(object)
            self._updateCost()
            return self
        else:
            raise TypeError("The argument must be an instance of the 'Circuit' Class")
    def __sub__(self, object):
        if isinstance(object, Circuit):
            if object in self.circuits:
                return self

            self.circuits.remove(object)
            self._updateCost()
            return self
        else:
            raise TypeError("The argument must be an instance of the 'Circuit' Class")
    def __getitem__(self, circuitID):
        for circuit in self.circuits:
            if circuit.id == circuitID:
                return circuit
        raise KeyError("The requested circuit does not belong to this project.")
class Capstone(Project):
    def __init__(self, *args):
        if len(args) == 1: # Usage: <project-object>
            project = args[0] # for readability
            self.id = project.id
            self._validateParticipants(project.participants)
            self.circuits = project.circuits
            self._updateCost()
        else: # Usage: <id> <participants> <circuits>
            self.id = args[0]
            self._validateParticipants(args[1])
            self.circuits = args[2]
            self._updateCost()

    def _validateParticipants(self, participants):
        self.participants = []
        for p in participants:
            if not isinstance(p, Student):
                raise TypeError("The argument must be an instance of the 'Student' Class")
            if p.level.name != "Senior":
                raise ValueError("For a Capstone project, all participants must be seniors.")
            self.participants.append(p)

# Test methods
def __TEST_1( ):
    andrewLevel = Level(4)
    Andrew = Student("astpier", "Andrew", "St. Pierre", andrewLevel)
    print(Andrew)
def __TEST_2( ):
    compType = ComponentType(4)
    newComponent = Component("123-432", 4.9999, compType)
    print(newComponent)
    print(hash(newComponent))
def __TEST_3( ):
    compType = ComponentType(4)
    newComponent = Component("123-432", 4.9999, compType)
    compSet = set([newComponent])
    newCircuit = Circuit("2042-1341", compSet)
    print(newCircuit)
def __TEST_4( ):
    compType1 = ComponentType(4)
    newComponent1 = Component("123-432", 4.9999, compType1)
    compSet = set([newComponent1])
    newCircuit = Circuit("2042-1341", compSet)
    print(newCircuit)
    newCircuit = newCircuit - newComponent1
    print(newCircuit)
    compType2 = ComponentType(3)
    newComponent2 = Component("467-843", 10.9999, compType2)
    newCircuit + newComponent2
    print(newCircuit)
    newCircuit + newComponent1
    print(newCircuit)
def __TEST_5( ):
    transistor = ComponentType(4)
    tcomp = Component("123-432", 4.9999, transistor)
    circuitA = Circuit("circuitA", set([tcomp]))
    print(circuitA)

    inductor = ComponentType(3)
    icomp = Component("284-612", 4.9999, inductor)
    circuitB = Circuit("circuitB", set([icomp]))
    print(circuitB)

    if circuitA == circuitB:
        pp("circuits are equal in cost!")
    else: pp("err: circuits should have same costs...")
def __TEST_6( ):
    transistor = ComponentType(4)
    tcomp = Component("123-432", 4.9999, transistor)
    circuitA = Circuit("circuitA", set([tcomp]))
    print(circuitA)
    inductor = ComponentType(3)
    icomp = Component("284-612", 8.9999, inductor)
    circuitB = Circuit("circuitB", set([icomp]))
    print(circuitB)
    if circuitA < circuitB:
        pp("circuitA costs less than circuitB!")
    else: pp("err: circuitB should cost more...")
def __TEST_7( ):
    transistor = ComponentType(4)
    tcomp = Component("123-432", 4.9999, transistor)
    circuitA = Circuit("circuitA", set([tcomp]))
    print(circuitA)

    inductor = ComponentType(3)
    icomp = Component("284-612", 2.9999, inductor)
    circuitB = Circuit("circuitB", set([icomp]))
    print(circuitB)
    if circuitA > circuitB:
        pp("circuitA costs more than circuitB!")
    else: pp("err: circuitA should cost more...")
def __TEST_8( ):
    transistor = ComponentType(4)
    tcomp = Component("123-432", 4.9999, transistor)
    circuitA = Circuit("circuitA", set([tcomp]))
    print(circuitA)

    inductor = ComponentType(3)
    icomp = Component("284-612", 2.9999, inductor)
    circuitB = Circuit("circuitB", set([icomp]))
    print(circuitB)

    andrewLevel = Level(4)
    andrew = Student("astpier", "Andrew", "St. Pierre", andrewLevel)

    projectA = Project("proj-A", [andrew], [circuitA, circuitB])
    print(projectA)
    if icomp in projectA: pp("projectA contains component you querried")
    if andrew in projectA: pp("projectA contains the participant you querried")
    if circuitA in projectA: pp("projectA contains the circuit you querried")
    circuitC = Circuit("circuitC", set([icomp]))
    if circuitC not in projectA: pp("projectA does not contain the circuit you querried")
def __TEST_9( ):
    transistor = ComponentType(4)
    tcomp = Component("123-432", 4.9999, transistor)
    circuitA = Circuit("circuitA", set([tcomp]))
    print(circuitA)

    inductor = ComponentType(3)
    icomp = Component("284-612", 2.9999, inductor)
    circuitB = Circuit("circuitB", set([icomp]))
    print(circuitB)

    andrewLevel = Level(4)
    andrew = Student("astpier", "Andrew", "St. Pierre", andrewLevel)

    projectA = Project("proj-A", [andrew], [circuitB])
    print(projectA)
    projectA += circuitA
    print(projectA)
    projectA -= circuitB
    print(projectA)
def __TEST_10( ):
    transistor = ComponentType(4)
    tcomp = Component("123-432", 4.9999, transistor)
    circuitA = Circuit("circuitA", set([tcomp]))
    print(circuitA)

    inductor = ComponentType(3)
    icomp = Component("284-612", 2.9999, inductor)
    circuitB = Circuit("circuitB", set([icomp]))
    print(circuitB)

    andrewLevel = Level(4)
    andrew = Student("astpier", "Andrew", "St. Pierre", andrewLevel)

    projectA = Project("proj-A", [andrew], [circuitB])
    print(projectA)
    projectA += circuitA
    print(projectA)

    print(projectA["circuitA"])
    print(projectA["circuitB"])
def __TEST_11( ):
    transistor = ComponentType(4)
    tcomp = Component("123-432", 4.9999, transistor)
    circuitA = Circuit("circuitA", set([tcomp]))

    inductor = ComponentType(3)
    icomp = Component("284-612", 2.9999, inductor)
    circuitB = Circuit("circuitB", set([icomp]))

    andrewLevel = Level(4)
    andrew = Student("astpier", "Andrew", "St. Pierre", andrewLevel)
    andyLevel = Level(4)
    andy = Student("andy", "Andy", "St. Pierre", andyLevel)

    projectA = Project("proj-A", [andrew, andy], [circuitB, circuitA])

    # Initializer method 1
    capstoneA = Capstone(projectA.id, projectA.participants, projectA.circuits)
    print(capstoneA)
    print(capstoneA["circuitA"]) # checking inheritance worked

    # Initializer method 2
    capstoneB = Capstone(projectA)
    print(capstoneB)
    print(capstoneB["circuitB"])

if __name__ == "__main__":
    # Test calls
    __TEST_1( )
    __TEST_2( )
    __TEST_3( )
    __TEST_4( )
    __TEST_5( )
    __TEST_6( )
    __TEST_7( )
    __TEST_8( )
    __TEST_9( )
    __TEST_10( )
    __TEST_11( )
