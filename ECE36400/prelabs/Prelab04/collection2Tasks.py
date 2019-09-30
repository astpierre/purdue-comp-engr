###############################################################################
#   Author:	Andrew St. Pierre
#   email: 	astpier@purdue.edu
#   ID: 	ee364b17
#   Date: 	Wednesday, January 30, 2019
###############################################################################

import os
import sys
from collections import namedtuple

# Module level variables
DataPath = os.path.expanduser('~ee364/DataFolder/Prelab04')
#DataPath = os.path.expanduser('~/prelabs-astpierre/Prelab04/')

# Required methods
def getTechWork(techName):
    techsByName = getTechsByName()
    techID = techsByName[techName].techID
    reportByTech = getReportByTech()
    techData = reportByTech.get(techID)
    virusByID = getVirusesByID()
    virusUsage = {}
    if techData == None:
        return {}
    for report in techData:
        for trial in report.trials:
            virusName = virusByID.get(trial.virusID).virusName
            try:
                virusUsage[virusName] += trial.virusUnits
            except KeyError:
                virusUsage[virusName] = trial.virusUnits
    return virusUsage
def getStrainConsumption(virusName):
    viruses = getVirusesByName()
    vID = viruses.get(virusName).virusID
    techsByID = getTechsByID()
    reportData = getReportByStrain()
    virusData = reportData.get(vID)
    strainConsumption = {}
    for trial in virusData:
        technician = techsByID.get(trial.techID)
        try:
            strainConsumption[technician.techName] += trial.virusUnits
        except KeyError:
            strainConsumption[technician.techName] = trial.virusUnits
    return strainConsumption
def getTechSpending():
    techsByName = getTechsByName()
    virusByName = getVirusesByName()
    techSpending = {}
    for tech in techsByName:
        techName = techsByName[tech].techName
        techWork = getTechWork(techName)
        if techWork != None:
            if techWork != {}:
                techSpending[techName] = 0.0
                for strain in techWork:
                    virusData = virusByName.get(strain)
                    quantity = techWork[strain]
                    costPerUnit = virusData.virusUnitCost
                    techSpending[techName] += getCost(quantity, costPerUnit)
    for entry in techSpending:
        techSpending[entry] = round(techSpending[entry], 2)
    return techSpending
def getStrainCost():
    virusByName = getVirusesByName()
    reportByStrain = getReportByStrain()
    strainCost = {}
    for v in virusByName:
        vID = virusByName[v].virusID
        vUnitCost = virusByName[v].virusUnitCost
        strainTrials = reportByStrain.get(vID)
        if strainTrials != None:
            strainCost[virusByName[v].virusName] = 0.0
            for trial in strainTrials:
                trialCost = getCost(trial.virusUnits, vUnitCost)
                strainCost[virusByName[v].virusName] += trialCost
    for entry in strainCost:
        strainCost[entry] = round(strainCost[entry], 2)
    return strainCost
def getAbsentTechs():
    techsByName = getTechsByName()
    reportByTech = getReportByTech()
    absenteeList = []
    for tech in techsByName:
        techName = techsByName[tech].techName
        techID = techsByName[tech].techID
        techWork = reportByTech.get(techID)
        if techWork == None:
            absenteeList.append(techName)
    return set(absenteeList)
def getUnusedStrains():
    virusByName = getVirusesByName()
    reportByStrain = getReportByStrain()
    unusedList = []
    for strain in virusByName:
        strainName = virusByName[strain].virusName
        strainID = virusByName[strain].virusID
        strainTrials = reportByStrain.get(strainID)
        if strainTrials == None:
            unusedList.append(strainName)
    return set(unusedList)
# Helper Methods
def getReportFiles():
    fileList = []
    with os.scandir(os.path.join(DataPath, "reports")) as dir:
        for f in dir:
            if not f.name.startswith('.') and f.is_file():
                fileList.append(f.name)
    return fileList
def getVirusesByID():
    Virus = namedtuple("Virus", ["virusName", "virusID", "virusUnitCost"])
    virusDict = {}
    with open(os.path.join(DataPath, "maps/viruses.dat")) as f:
        lines = f.readlines()
        lines = lines[2:]
    for line in lines:
        line = line.split("|")
        vName = line[0].strip()
        vID = line[1].strip()
        vUnitCost = float(line[2].strip().strip("\n").strip("$"))
        newEntry = Virus(vName, vID, vUnitCost)
        virusDict[vID] = newEntry
    return virusDict
def getVirusesByName():
    Virus = namedtuple("Virus", ["virusName", "virusID", "virusUnitCost"])
    virusDict = {}
    with open(os.path.join(DataPath, "maps/viruses.dat")) as f:
        lines = f.readlines()
        lines = lines[2:]
    for line in lines:
        line = line.split("|")
        vName = line[0].strip()
        vID = line[1].strip()
        vUnitCost = float(line[2].strip().strip("\n").strip("$"))
        newEntry = Virus(vName, vID, vUnitCost)
        virusDict[vName] = newEntry
    return virusDict
def getTechsByID():
    Tech = namedtuple("Tech", ["techName", "techID"])
    techDict = {}
    with open(os.path.join(DataPath, "maps/technicians.dat")) as f:
        lines = f.readlines()
        lines = lines[2:]
    for line in lines:
        line = line.split("|")
        tName = line[0].strip()
        tID = line[1].strip().strip("\n")
        newEntry = Tech(tName, tID)
        techDict[tID] = newEntry
    return techDict
def getTechsByName():
    Tech = namedtuple("Tech", ["techName", "techID"])
    techDict = {}
    with open(os.path.join(DataPath, "maps/technicians.dat")) as f:
        lines = f.readlines()
        lines = lines[2:]
    for line in lines:
        line = line.split("|")
        tName = line[0].strip()
        tID = line[1].strip().strip("\n")
        newEntry = Tech(tName, tID)
        techDict[tName] = newEntry
    return techDict
def getReportByTech():
    Report = namedtuple("Report", ["techID", "trials"])
    Trial = namedtuple("Trial", ["trialNum","virusID","virusUnits"])
    reportDict = {}
    reportFiles = getReportFiles()
    for report in reportFiles:
        trialList = []
        with open(os.path.join(DataPath, "reports/"+report)) as f:
            lines = f.readlines()
            tID = lines[0].strip("User ID:").strip()
            if tID not in reportDict:
                reportDict[tID] = []
            lines = lines[4:]
        for line in lines:
            line = line.split()
            tNum = int(line[0].strip())
            vID = line[1].strip()
            vUnits = int(line[2].strip().strip("\n"))
            newTrial = Trial(tNum, vID, vUnits)
            trialList.append(newTrial)
        newReport = Report(tID, trialList)
        reportDict[tID].append(newReport)
    return reportDict
def getReportByStrain():
    Trial = namedtuple("Trial", ["techID", "trialNum","virusID","virusUnits"])
    reportDict = {}
    reportFiles = getReportFiles()
    for report in reportFiles:
        with open(os.path.join(DataPath, "reports/"+report)) as f:
            lines = f.readlines()
            tID = lines[0].strip("User ID:").strip()
            lines = lines[4:]
        for line in lines:
            line = line.split()
            tNum = int(line[0].strip())
            vID = line[1].strip()
            vUnits = int(line[2].strip().strip("\n"))
            newTrial = Trial(tID, tNum, vID, vUnits)
            if vID not in reportDict:
                reportDict[vID] = []
            reportDict[vID].append(newTrial)
    return reportDict
def getCost(quantity, costPerUnit):
    product = float(quantity) * float(costPerUnit)
    return product

if __name__ == "__main__":
    # Test calls
    # 1.
    print("TEST 1: ")
    techName = "Campbell, Eugene"
    techWork = getTechWork(techName)
    for i in techWork:
        print(f"Strain: {i}    Units: {techWork[i]}")
    print("==============================================================")

    # 2.
    print("TEST 2: ")
    virusName = "Zikavirus"
    strainConsumption = getStrainConsumption(virusName)
    for tech in strainConsumption:
        print(f"Name: {tech}    Units: {strainConsumption[tech]}")
    print("==============================================================")

    # 3.
    print("TEST 3: ")
    techSpending = getTechSpending()
    for tech in techSpending:
        print(f"Name: {tech}    Spent: {techSpending[tech]}")
    print("==============================================================")

    # 4.
    print("TEST 4: ")
    strainCost = getStrainCost()
    for strain in strainCost:
        print(f"Strain: {strain}    Spent: {strainCost[strain]}")
    print("==============================================================")


    # 5.
    print("TEST 5: ")
    absentees = getAbsentTechs()
    for tech in absentees:
        print(f"Name: {tech}")
    print("==============================================================")

    # 6.
    print("TEST 6: ")
    unused = getUnusedStrains()
    for u in unused:
        print(f"Strain: {u}")
    print("==============================================================")
