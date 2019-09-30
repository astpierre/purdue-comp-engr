
###############################################################################
#   Author:	Andrew St. Pierre
#   email: 	astpier@purdue.edu
#   ID: 	ee364b17
#   Date: 	Sunday, February 17, 2019
###############################################################################

import os
import sys
import re
from pprint import pprint as pp
from uuid import UUID

# Module level variables
DataPath = os.path.expanduser('~ee364/DataFolder/Prelab06')
#DataPath = os.path.expanduser('~/prelabs-astpierre/Prelab06/')

# Required methods
def getUrlParts(url):
    pattern = r"(?:\w+:/{2})(\w{3}.{1}\w+.{1}\w{3})"
    base = re.search(pattern, url)
    base = base.group(1)

    pattern = r"(?:\w+:/{2}\w{3}.{1}\w+.{1}\w{3}/{1})(\w+)/{1}"
    controller =re.search(pattern, url)
    controller = controller.group(1)

    pattern = r"(?:\w+:/{2}\w{3}.{1}\w+.{1}\w{3}/{1}\w+/{1})(\w+)\?{1}"
    action = re.search(pattern, url)
    action = action.group(1)

    return base,controller,action
def getQueryParameters(url):
    pattern = r"([\w\-\_\.]+)\=([\w\-\_\.]+)"
    queryParams = re.findall(pattern, url)
    tupleList = []
    for qp in queryParams:
        field = qp[0]
        value = qp[1]
        tupleList.append((field, value))
    return tupleList
def getSpecial(sentence, letter):
    matches = []
    #pattern = r""+re.escape(letter)+r"+\w+\b|\w+"+re.escape(letter)+r"+\b"
    #pattern = r"(?(?=^"+re.escape(letter)+r")+\w+\b)|\w+"+re.escape(letter)+r"+\b)"
    #pattern = r"(^"+re.escape(letter)+r")?\w+(?\b|\b\w+"+re.escape(letter)+r"(?(1)(?!)))"
    #pattern = r"^" + re.escape(letter) + r"\w+(?!" + re.escape(letter) + r")"
    #matches = re.findall(pattern, sentence, re.IGNORECASE)
    #pp(matches)
    return 0
def getRealMac(sentence):
    pattern = r".*(\w{2}[-:]\w{2}[-:]\w{2}[-:]\w{2}[-:]\w{2}[-:]\w{2}).*"
    matches = re.search(pattern, sentence)
    if matches:
        return matches.group(1)
    else:
        return None
def getRawEmployees():
    with open(os.path.join(DataPath, "Employees.txt")) as f:
        lines = f.readlines()
    return lines
def getRejectedEntries():
    # returns a list of rejected employee names <First> <Last>
    rejects = []
    rawEmployeeData = getRawEmployees()
    pattern1 = r"^([A-Za-z]+)[, ]{2}([A-Za-z]+)[;, ]+$"
    for line in rawEmployeeData:
        match = re.search(pattern1, line)
        if match:
            properFormat = match.group(2)+" "+match.group(1)
            rejects.append(properFormat)
        else:
            patternAlt = r"^([A-Za-z]+)[ ]{1}([A-Za-z]+)[;, ]+$"
            match2 = re.search(patternAlt, line)
            if match2:
                properFormat = match2.group(1)+" "+match2.group(2)
                rejects.append(properFormat)
    return sorted(rejects)
def getEmployeesWithIDs():
    # returns a {string: string} dictionary with key=name, val=ID
    employeeDict = {}
    rawEmployeeData = getRawEmployees()
    pattern_name1 = r"^([A-Za-z]+)[, ]{2}([A-Za-z]+)[;, ]"
    pattern_name2 = r"^([A-Za-z]+)[ ]{1}([A-Za-z]+)[;, ]"
    pattern_ID = r"(\w{8}[-\s]?\w{4}[-\s]?\w{4}[-\s]?\w{4}[-\s]?\w{12})"
    for line in rawEmployeeData:
        match = re.search(pattern_name1, line)
        if match:
            properNameFormat = match.group(2)+" "+match.group(1)
            matchID = re.search(pattern_ID, line)
            if matchID:
                properIDFormat = str(UUID(matchID.group(1)))
                employeeDict[properNameFormat] = properIDFormat
        else:
            match2 = re.search(pattern_name2, line)
            if match2:
                properNameFormat = match2.group(1)+" "+match2.group(2)
                matchID2 = re.search(pattern_ID, line)
                if matchID2:
                    properIDFormat = str(UUID(matchID2.group(1)))
                    employeeDict[properNameFormat] = properIDFormat
    return employeeDict
def getEmployeesWithoutIDs():
    # returns a sorted list of employee names
    employeesWOID = []
    rawEmployeeData = getRawEmployees()
    rejects = getRejectedEntries()
    pattern_name1 = r"^([A-Za-z]+)[, ]{2}([A-Za-z]+)[;, ]"
    pattern_name2 = r"^([A-Za-z]+)[ ]{1}([A-Za-z]+)[;, ]"
    pattern_ID = r"(\w{8}[-\s]?\w{4}[-\s]?\w{4}[-\s]?\w{4}[-\s]?\w{12})"
    for line in rawEmployeeData:
        noGood = 0
        match = re.search(pattern_name1, line)
        if match:
            properNameFormat = match.group(2)+" "+match.group(1)
            if properNameFormat in rejects:
                noGood = 1
            else:
                matchID = re.search(pattern_ID, line)
                if matchID:
                    noGood = 1
        else:
            match2 = re.search(pattern_name2, line)
            if match2:
                properNameFormat = match2.group(1)+" "+match2.group(2)
                if properNameFormat in rejects:
                    noGood = 1
                else:
                    matchID2 = re.search(pattern_ID, line)
                    if matchID2:
                        noGood = 1
        if noGood == 0:
            employeesWOID.append(properNameFormat)
    return sorted(employeesWOID)
def helpFormatPhoneNumber(phoneNumber):
    pattern_good = r"[\(]{1}\d{3}[\)]{1}[\s]{1}\d{3}[-\s]{1}\d{4}"
    pattern_bad1 = r"(\d{3})[-]{1}(\d{3})[-]{1}(\d{4})"
    pattern_bad2 = r"(\d{3})(\d{3})(\d{4})"
    match_good = re.search(pattern_good, phoneNumber)
    if match_good:
        return phoneNumber
    match_bad1 = re.search(pattern_bad1, phoneNumber)
    if match_bad1:
        properPhoneFormat = "("+match_bad1.group(1)+") "+match_bad1.group(2)+ "-"+match_bad1.group(3)
        return properPhoneFormat
    match_bad2 = re.search(pattern_bad2, phoneNumber)
    if match_bad2:
        properPhoneFormat = "("+match_bad2.group(1)+") "+match_bad2.group(2)+ "-"+match_bad2.group(3)
        return properPhoneFormat
    return None
def getEmployeesWithPhones():
    # returns a {string: string} dictionary with key=name, val=phone#
    employeeDict = {}
    rawEmployeeData = getRawEmployees()
    pattern_name1 = r"^([A-Za-z]+)[, ]{2}([A-Za-z]+)[;, ]"
    pattern_name2 = r"^([A-Za-z]+)[ ]{1}([A-Za-z]+)[;, ]"
    pattern_phone = r"([\(]?\d{3}[\)]?[\s]?[-]?\d{3}[-\s]?\d{4})[;,\s]+"
    for line in rawEmployeeData:
        match1 = re.search(pattern_name1, line)
        if match1:
            properNameFormat = match1.group(2)+" "+match1.group(1)
            matchPhone1 = re.search(pattern_phone, line)
            if matchPhone1:
                properPhoneFormat = helpFormatPhoneNumber(matchPhone1.group(1))
                if properPhoneFormat != None:
                    employeeDict[properNameFormat] = properPhoneFormat
        else:
            match2 = re.search(pattern_name2, line)
            if match2:
                properNameFormat = match2.group(1)+" "+match2.group(2)
                matchPhone2 = re.search(pattern_phone, line)
                if matchPhone2:
                    properPhoneFormat = helpFormatPhoneNumber(matchPhone2.group(1))
                    if properPhoneFormat != None:
                        employeeDict[properNameFormat] = properPhoneFormat
    return employeeDict
def getEmployeesWithStates():
    # returns a {string: string} dictionary with key=name, val=state
    employeeDict = {}
    rawEmployeeData = getRawEmployees()
    pattern_name1 = r"^([A-Za-z]+)[, ]{2}([A-Za-z]+)[;, ]"
    pattern_name2 = r"^([A-Za-z]+)[ ]{1}([A-Za-z]+)[;, ]"
    pattern_state = r"([A-Za-z]+[\s]?[A-Za-z]*)\b$"
    for line in rawEmployeeData:
        match1 = re.search(pattern_name1, line)
        if match1:
            properNameFormat = match1.group(2)+" "+match1.group(1)
            matchState1 = re.search(pattern_state, line)
            if matchState1:
                properStateFormat = matchState1.group(1)
                employeeDict[properNameFormat] = properStateFormat
        else:
            match2 = re.search(pattern_name2, line)
            if match2:
                properNameFormat = match2.group(1)+" "+match2.group(2)
                matchState2 = re.search(pattern_state, line)
                if matchState2:
                    properStateFormat = matchState2.group(1)
                    employeeDict[properNameFormat] = properStateFormat
    return employeeDict
def getCompleteEntries():
    employeeCompleteDict = {}
    employeesWithStates = getEmployeesWithStates()
    employeesWithIDs = getEmployeesWithIDs()
    employeesWithPhones = getEmployeesWithPhones()
    for key in employeesWithIDs:
        if key in employeesWithStates:
            if key in employeesWithPhones:
                id = employeesWithIDs[key]
                phone = employeesWithPhones[key]
                state = employeesWithStates[key]
                tempTuple = (id, phone, state)
                employeeCompleteDict[key] = tempTuple
    return employeeCompleteDict

if __name__ == "__main__":
    # Test calls
    None
