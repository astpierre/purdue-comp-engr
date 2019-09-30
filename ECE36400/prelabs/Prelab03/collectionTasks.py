###############################################################################
#   Author:	Andrew St. Pierre
#   email: 	astpier@purdue.edu
#   ID: 	ee364b17
#   Date: 	Sunday, January 27, 2019
###############################################################################

import os
import sys
from collections import namedtuple

# Module level variables
DataPath = os.path.expanduser('~ee364/DataFolder/Prelab03')
#DevDataPath = os.path.expanduser('~/prelabs-astpierre/Prelab03/data')

# Required methods
def getComponentCountByProject(projectID, componentSymbol):
    """
    Input:  projectID and single letter "R","I","C","T"
    Output: Count of # of distinct components of requested type
    If projectID DNE, raise ValueError
    """
    # Check that projectID is valid
    if not isProjectValid(projectID):
        raise ValueError(f"Invalid project ID: {projectID}")

    # Get the project data and retrieve
    # the corresponding circuit ID number
    circuitIDs = getProjectCircuits(projectID)

    # Get all the distinct components from component.dat
    componentsOfType = getComponentsOfType(componentSymbol)

    compSet = []
    # Use the circuit ID number to get its components
    for circuit in circuitIDs:
        circuitComponents = getComponentsByCircuit(circuit)
        for component in circuitComponents:
            if component in componentsOfType:
                compSet.append(component)

    return len(set(compSet))
def getComponentCountByStudent(studentName, componentSymbol):
    """
    Input:  Student full name and component type given as "R","T","I","C"
    Output: Number of distinct components a student used accross all projects
    """
    # Check that student exists
    if not isStudentValid(studentName):
        raise ValueError(f"Invalid student name: {studentName}")

    # StudentName --> StudentID
    studentID = getStudentIDByName(studentName)

    # StudentID --> Look through each circuit's participants
    studentCircuits = getStudentCircuits(studentID)

    # Add comps if in getComponentsOfType(componentSymbol)
    componentTypeLib,studentComponents = getComponentsOfType(componentSymbol),[]
    for circuit in studentCircuits:
        circuitComponents = getComponentsByCircuit(circuit)
        for component in circuitComponents:
            if component in componentTypeLib:
                studentComponents.append(component)
    return len(set(studentComponents))
def getParticipationByStudent(studentName):
    # Check that student exists
    if not isStudentValid(studentName):
        raise ValueError(f"Invalid student name: {studentName}")
    studentID = getStudentIDByName(studentName)
    circuits = getStudentCircuits(studentID)
    projects, studentProjects = getProjectIDs(), []
    for proj in projects:
        projCircs = getProjectCircuits(proj)
        if intersectCheck(set(circuits),set(projCircs)):
            studentProjects.append(proj)
    if len(studentProjects) == 0:
        return set()
    else:
        return set(studentProjects)
def getParticipationByProject(projectID):
    if not isProjectValid(projectID):
        raise ValueError(f"Invalid project ID: {projectID}")
    listOfCircuits = getProjectCircuits(projectID)
    participantIDs = set()
    for circuit in listOfCircuits:
        participantIDs |= set(getParticipantsByCircuit(circuit))
    participantIDs.remove("")
    participantNames = []
    participantIDsToNames = getStudentNamesByID()
    for participantID in participantIDs:
        participantNames.append(participantIDsToNames[participantID])
    return set(participantNames)
def getCostOfProjects():
    # Get projectIDs
    # TODO: change DataPath
    projectCostDict, projects = {}, []
    with open(os.path.join(DataPath,"maps/projects.dat")) as f:
        lines = f.readlines()
        lines = lines[2:]
    for line in lines:
        line = line.split()
        projectID = line[1].strip().strip("\n")
        projects.append(projectID)

    # Call getProjCost for each
    for proj in projects:
        # Add new key val pair to dictionary
        projectCostDict[str(proj)] = getProjCost(proj)

    return projectCostDict
def getProjectByComponent(componentIDs):
    projects, projectsUsingComponents = getProjectIDs(), []
    for project in projects:
        projCircs = getProjectCircuits(project)
        for circ in projCircs:
            components = getComponentsByCircuit(circ)
            if intersectCheck(set(components),set(componentIDs)):
                projectsUsingComponents.append(project)
    return set(projectsUsingComponents)
def getCommonByProject(projectID1, projectID2):
    # Check if projects given exist
    if not isProjectValid(projectID1):
        raise ValueError(f"Invalid project ID: {projectID1}")
    if not isProjectValid(projectID2):
        raise ValueError(f"Invalid project ID: {projectID2}")
    # Get components for each project, take the intersection
    Project = namedtuple("Project","projectID components")
    proj1 = Project(projectID1,[])
    proj2 = Project(projectID2,[])

    for proj in [proj1, proj2]:
        projCircs = getProjectCircuits(proj.projectID)
        for circ in projCircs:
            circComps = getComponentsByCircuit(circ)
            for c in circComps:
                proj.components.append(c)
    commonComponents = []
    for i in proj1.components:
        if i in proj2.components:
            commonComponents.append(i)
    commonComponents = list(set(commonComponents))
    if len(commonComponents) == 0:
        return []
    else:
        commonComponents = sorted(commonComponents)
        return commonComponents
def getComponentReport(componentIDs):
    projects = getProjectIDs()
    componentReport = {}
    for id in componentIDs:
        componentReport[id] = 0
        for project in projects:
            componentsUsed = getComponentsByProject(project)
            componentReport[id] += componentsUsed.count(id)
    return componentReport
def getCircuitByStudent(studentNames):
    circuitSet = set()
    for student in studentNames:
        studentID = getStudentIDByName(student)
        studentCircuits = getStudentCircuits(studentID)
        for c in studentCircuits:
            circuitSet.add(c)
    return circuitSet
def getCircuitByComponent(componentIDs):
    projectIDs = getProjectIDs()
    circuits = set()
    for pid in projectIDs:
        circuits |= set(getProjectCircuits(pid))
    circuitsUsingComponents = []
    for circuit in circuits:
        components = getComponentsByCircuit(circuit)
        if intersectCheck(components, componentIDs):
            circuitsUsingComponents.append(circuit)
    return set(circuitsUsingComponents)

# Helper Methods
def getComponentsOfType(componentSymbol):
    """
    Input:  componentSymbol char
    Output: The components of respective type
    If componentSymbol DNE, raise ValueError
    """
    compSymbs = {
    "R": "resistors.dat",
    "T": "transistors.dat",
    "C": "capacitors.dat",
    "I": "inductors.dat"
    }
    components = {}
    target = compSymbs.get(componentSymbol)
    with open(os.path.join(DataPath,"maps/"+target)) as f:
        for line in f.readlines():
            if not line.startswith("-"):
                line = line.split()
                if line[0] != "ID" and line[1] != "Price":
                    components[line[0]] = line[1]
    return list(components.keys())
def isProjectValid(projectID):
    """
    Input:  projectID number
    Output: True if valid, False if DNE
    """
    projects = {}
    with open(os.path.join(DataPath,"maps/projects.dat")) as f:
        for line in f.readlines():
            if not line.startswith("-"):
                line = line.split()
                if line[0] != "Circuit" and line[1] != "Project":
                    # project["PROJ-ID"] = "CIRCUIT"
                    projects[line[1]] = line[0]
    if projectID in list(projects.keys()):
        return True
    else: return False
def getComponentsByCircuit(circuitID):
    """
    Input:  circuitID string
    Output: list of components from circuit_XX-X-XX.dat file
    """
    components = []
    with open(os.path.join(DataPath,"circuits/circuit_"+circuitID+".dat")) as f:
        line = f.readline()
        while not line.startswith("Components"):
            line = f.readline()
        for line in f.readlines():
            if not line.startswith("-"):
                components.append(line.strip(" ").strip("\n"))
    return components
def getParticipantsByCircuit(circuitID):
    """
    Input:  circuitID string
    Output: list of participants ID's from circuit_XX-X-XX.dat file
    """
    participants = []
    with open(os.path.join(DataPath,"circuits/circuit_"+circuitID+".dat")) as f:
        line = f.readline()
        while not line.startswith("Participants:"):
            line = f.readline()
        for line in f.readlines():
            if line.startswith("Components:"):
                break
            elif not line.startswith("-"):
                participants.append(line.strip(" ").strip("\n"))
    return participants
def getStudentIDByName(studentName):
    studentDict = {}
    with open(os.path.join(DataPath,"maps/students.dat")) as f:
        lines = f.readlines()
        lines = lines[2:]
        for line in lines:
            line = line.split("|")
            line[0] = line[0].strip()
            line[1] = line[1].strip().strip("\n")
            studentDict[line[0]] = line[1]
    return studentDict[studentName]
def getStudentCircuits(studentID):
    path = os.path.join(DataPath, "circuits/")
    studentCircuits = []
    with os.scandir(path) as dir:
        for f in dir:
            if not f.name.startswith('.') and f.is_file():
                circuitQuery = f.name.strip("circuit_").strip(".dat")
                circuitParticipants = getParticipantsByCircuit(circuitQuery)
                if studentID in circuitParticipants:
                    studentCircuits.append(circuitQuery)
    return studentCircuits
def isStudentValid(studentName):
    """
    Input:  studentName string
    Output: True if exists/valid, False if DNE
    """
    with open(os.path.join(DataPath,"maps/students.dat")) as f:
        lines = f.readlines()
        lines = lines[2:]
        for line in lines:
            line = line.split("|")
            line[0] = line[0].strip()
            if studentName == line[0]: return True
    return False
def getProjectCircuits(projectID):
    """
    Input:  projectID number
    Output: List of circuitIDs corresponding to projectID
    """
    ProjCircs = namedtuple("ProjCircs", "circuitIDs")
    circuits = ProjCircs([])
    path = os.path.join(DataPath,"maps/projects.dat")
    with open(path) as f:
        lines = [line for line in f.readlines()]
        lines = lines[2:]
    for l in lines:
        l = l.split()
        cID, pID = l[0].strip(), l[1].strip()
        if pID == projectID:
            circuits.circuitIDs.append(cID)
    return circuits.circuitIDs
def getStudentNamesByID():
    studentDict = {}
    with open(os.path.join(DataPath,"maps/students.dat")) as f:
        lines = f.readlines()
        lines = lines[2:]
    for line in lines:
        line = line.split("|")
        line[0] = line[0].strip()
        line[1] = line[1].strip().strip("\n")
        studentDict[line[1]] = line[0]
    return studentDict
def getComponents():
    """
    Output: The components and respective costs
    """
    compSymbs = {
    "R": "resistors.dat",
    "T": "transistors.dat",
    "C": "capacitors.dat",
    "I": "inductors.dat"
    }
    components = {}
    for key in compSymbs:
        target = compSymbs.get(key)
        with open(os.path.join(DataPath,"maps/"+target)) as f:
            lines = [line for line in f.readlines()]
            lines = lines[3:]
        for l in lines:
            l = l.split()
            comp = l[0].strip()
            cost = l[1].strip()
            components[comp] = cost
    return components
def getProjCost(projectID):
    componentDict = getComponents()
    circuits = getProjectCircuits(projectID)
    totalCost = 0.00
    for circ in circuits:
        ccomps = getComponentsByCircuit(circ)
        for comp in ccomps:
            totalCost += float(componentDict[comp].strip("$"))
    twoDecimalFloatString = format(totalCost, ".2f")
    return float(twoDecimalFloatString)
def intersectCheck(set1,set2):
    for i in set1:
        if i in set2:
            return True
    return False
def getProjectIDs():
    projects, projectsUsingComponents = [], []
    with open(os.path.join(DataPath,"maps/projects.dat")) as f:
        lines = f.readlines()
        lines = lines[2:]
    for line in lines:
        line = line.split()
        projectID = line[1].strip().strip("\n")
        projects.append(projectID)
    return list(set(projects))
def getComponentsByProject(projectID):
    projectCircuits = getProjectCircuits(projectID)
    components = []
    for circuit in projectCircuits:
        comps = getComponentsByCircuit(circuit)
        for c in comps: components.append(c)
    return components


if __name__ == "__main__":
    # Test calls
    # 1.
    print("TEST 1: ")
    print(getComponentCountByProject("082D6241-40EE-432E-A635-65EA8AA374B6","T"))
    print("==============================================================")

    # 2.
    print("TEST 2: ")
    print(getParticipationByStudent("Robinson, Pamela"))
    print("==============================================================")

    # 3.
    print("TEST 3: ")
    print(getComponentCountByStudent("Robinson, Pamela","R"))
    print("==============================================================")

    # 4.
    print("TEST 4: ")
    print(getParticipationByProject("082D6241-40EE-432E-A635-65EA8AA374B6"))
    print("==============================================================")

    # 5.
    print("TEST 5: ")
    print(getCostOfProjects())
    print("==============================================================")

    # 6.
    print("TEST 6: ")
    print(getProjectByComponent(["CLQ-971","OPL-704"]))
    print("==============================================================")

    # 7.
    print("TEST 7: ")
    print(getCommonByProject("082D6241-40EE-432E-A635-65EA8AA374B6","4C5B295B-58E1-4CFB-80DF-88938B9A6300"))
    print("==============================================================")

    # 8.
    print("TEST 8: ")
    print(getComponentReport(["CLQ-971","OPL-704"]))
    print("==============================================================")

    # 9.
    print("TEST 9: ")
    print(getCircuitByStudent(["Barnes, Sean"]))
    print("==============================================================")

    # 10.
    print("TEST 10: ")
    print(getCircuitByComponent(["CLQ-971","OPL-704"]))
    print("==============================================================")

