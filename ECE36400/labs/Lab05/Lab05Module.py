#!/usr/bin/env python3.7

#######################################################
#   Author:     Andrew St. Pierre
#   email:      astpier@purdue.edu
#   ID:         ee364b17
#   Date:       02/13/2019
#######################################################

import os
import sys
from collections import namedtuple

DataPath = os.path.expanduser("~ee364/DataFolder/Lab05")

def getPeople():
    Person = namedtuple("Person", ["name", "id"])
    personList = []
    with open(os.path.join(DataPath, "people.dat")) as f:
        lines = f.readlines()
        lines = lines[2:]
    for line in lines:
        name, id = line.split("|")
        name = name.strip()
        id = id.strip().strip("\n")
        newPerson= Person(name, id)
        personList.append(newPerson)
    return personList
def getPins():
    Entry = namedtuple("Entry", ["id", "code", "date"])
    entryList = []
    with open(os.path.join(DataPath, "pins.dat")) as f:
        lines = f.readlines()
        raw_dates = lines[1].strip("ID").split()
        dates = []
        for d in raw_dates:
            if d != 'ID':
                dates.append(d.strip())
        lines = lines[3:]
    for line in lines:
        data = line.split()
        IDnum = data[0]
        pins = [d.strip() for d in data[1:]]
        for i in range(len(pins)):
            newEntry= Entry(IDnum, pins[i], dates[i])
            entryList.append(newEntry)
    return entryList
def getValidDates():
    with open(os.path.join(DataPath, "pins.dat")) as f:
        lines = f.readlines()
        raw_dates = lines[1].strip("ID").split()
        dates = []
        for d in raw_dates:
            if d != 'ID':
                dates.append(d.strip())
    return dates
def getPinFor(name, date):
    # check employee name and date valid
    personList = getPeople()
    names = [p.name for p in personList]
    if name not in names:
        raise ValueError("Name not available: " + name)
    if date not in getValidDates():
        raise ValueError("Date requested not available: " + date)
    for p in personList:
        if p.name == name:
            userID = p.id
    pinEntries = getPins()
    for pin in pinEntries:
        if pin.id == userID:
            if pin.date == date:
                return pin.code
    return None
def getUserOf(pin, date):
    if date not in getValidDates():
        raise ValueError("Date requested not available: " + date)
    personList = getPeople()
    pinEntries = getPins()
    entryByDate = []
    for entry in pinEntries:
        if entry.date == date:
            if entry.code == pin:
                userID = entry.id
                break
    for person in personList:
        if person.id == userID:
            return person.name

    raise ValueError("Pin requested not available: " + pin)
def getLogs():
    Entry = namedtuple("Entry", ["date", "time", "dept", "code"])
    entryList = []
    with open(os.path.join(DataPath, "log.dat")) as f:
        lines = f.readlines()
        lines = lines[3:]
    for line in lines:
        date, time, dept, code = line.split()
        date = date.strip()
        time = time.strip()
        dept = dept.strip()
        code = code.strip().strip('\n')
        newEntry = Entry(date, time, dept, code)
        entryList.append(newEntry)
    return entryList



def getUsersOn(date):
    valDates = getValidDates()
    if date not in valDates:
        raise ValueError("Date requested not available: " + date)
    personList = getPeople()
    pinEntries = getPins()
    logData = getLogs()
    userIDList = []
    userNameList = []
    pinCodeList = []
    for log in logData:
        if log.date == date:
            pinCodeList.append(log.code)
    for code in pinCodeList:
        for entry in pinEntries:
            if entry.date == date:
                if entry.code == code:
                    for person in personList:
                        if person.id == entry.id:
                            userNameList.append(person.name)
    return set(userNameList)
def getResourcesOn(date):
    valDates = getValidDates()
    if date not in valDates:
        raise ValueError("Date requested not available: " + date)
    logData = getLogs()
    resourceList = []
    for log in logData:
        if log.date == date:
            resourceList.append(log.dept)
    return set(resourceList)
def getMostAccessedOn(dates):
    valDates = getValidDates()
    for date in dates:
        if date not in valDates:
            raise ValueError("Date requested not available: " + date)
    logData = getLogs()
    resourceDict = {}
    for log in logData:
        if log.date in dates:
            try:
                resourceDict[log.dept] += 1
            except KeyError:
                resourceDict[log.dept] = 0
    maxUsage = -1
    maxDept = ""
    for dept in resourceDict:
        if resourceDict[dept] > maxUsage:
            maxUsage = resourceDict[dept]
            maxDept = dept
    return maxDept
def getMostActiveUserOn(dates):
    valDates = getValidDates()
    for date in dates:
        if date not in valDates:
            raise ValueError("Date requested not available: " + date)
    logData = getLogs()
    pinEntries = getPins()
    personList = getPeople()
    userDict = {}
    for log in logData:
        if log.date in dates:
            for entry in pinEntries:
                if entry.date == log.date:
                    if log.code == entry.code:
                        userID = entry.id
            for person in personList:
                if person.id == userID:
                    try:
                        userDict[person.name] += 1
                    except KeyError:
                        userDict[person.name] = 0
    maxUsage = -1
    maxUser = ""
    for user in userDict:
        if userDict[user] > maxUsage:
            maxUsage = userDict[user]
            maxUser = user
    return maxUser
def getSlots():
    #Entry = namedtuple("Entry", ["date", "time", "dept", "code"])
    entryList = []
    with open(os.path.join(DataPath, "slots.dat")) as f:
        lines = f.readlines()
        rtimes= lines[1].split()
        times = []
        for t in rtimes:
            if t != "ID":
                t = t.strip().strip("\n")
                times.append(t)
        lines = lines[3:]
    i=0
    j=0
    while i<len(times):
        if slot1 == times[i]
            break
        else: i += 1
    while j<len(times):
        if slot2 == times[j]
            break
        else: j += 1
    count1 = 0
    count2 = 0
    for line in lines:
        line = line.split()
        if line[i+1] == '1':

            if line[j+1] == '0':
                count1 += 1
    return count1


    '''
    for line in lines:
        date, time, dept, code = line.split()
        date = date.strip()
        time = time.strip()
        dept = dept.strip()
        code = code.strip().strip('\n')
        newEntry = Entry(date, time, dept, code)
        entryList.append(newEntry)
    return entryList
    '''
def getDifference(slot1, slot2):
    getSlots()
    return None

if __name__ == "__main__":
    #personList = getPeople()
    #getPinByIDandDate(0,0)
    print(getPinFor("Bailey, Catherine", "03/18"))
    print(getPinFor("Roberts, Teresa", "01/17"))
    print(getUserOf("710", "03/18"))
    print(getUserOf("60006", "01/17"))
    users = getUsersOn("04/15")
    for u in users:
        print(f"username: {u}")
    resources = getResourcesOn("03/03")
    for r in resources:
        print(f"resource: {r}")
    print(getMostAccessedOn({'01/20','03/26'}))
    print(getMostActiveUserOn({'01/05','01/27'}))
    #auser = getAbsentUsers()
    print(getDifference(1,2))
    #getLogs()
