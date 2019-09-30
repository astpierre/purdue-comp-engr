###############################################################################
#   Author:	Andrew St. Pierre
#   email: 	astpier@purdue.edu
#   ID: 	ee364b17
#   Date: 	Wednesday, April 17, 2019
###############################################################################
import os
import re
from pprint import pprint as pp
from enum import Enum
from measurement import calculateDistance

# Data path to .dat files
DataPath=os.path.expanduser('~ee364/DataFolder/Lab14')

# Required classes
class Direction(Enum):
    Incoming = 1
    Outgoing = 2
    Both = 3
class Leg():
    def __init__(self, src: str, dest: str) -> None:
        self.source = src
        self.destination = dest
    def __str__(self) -> str:
        return f"<{self.source[-5:]}> => <{self.destination[-5:]}>"
    def calculateLength(self, locationMap: dict) -> float:
        srcLongLat = locationMap[self.source[-5:]]
        destLongLat = locationMap[self.destination[-5:]]
        miles = calculateDistance(srcLongLat, destLongLat)
        return float(format(miles, '.2f'))
class Trip():
    def __init__(self, personName: str, listOfLegs: list) -> None:
        self.person = personName
        self.legs = listOfLegs
    def calculateLength(self, locationMap: dict) -> float:
        totalDistance = 0.0
        for idx in range(len(self.legs)):
            leg = self.legs[idx]
            totalDistance += leg.calculateLength(locationMap)
        return float(format(totalDistance, '.2f'))
    def getLegsByZip(self, zipCode: str, dir: Direction) -> list:
        relevantLegs = []
        for idx in range(len(self.legs)):
            leg = self.legs[idx]
            if dir == Direction.Incoming:
                if(zipCode in leg.destination):
                    relevantLegs.append(leg)
            elif dir == Direction.Outgoing:
                if(zipCode in leg.source):
                    relevantLegs.append(leg)
            elif dir == Direction.Both:
                if(zipCode in leg.source):
                    relevantLegs.append(leg)
                elif(zipCode in leg.destination):
                    relevantLegs.append(leg)
        return relevantLegs
    def getLegsByState(self, stateAbbr: str, dir: Direction) -> list:
        relevantLegs = []
        for idx in range(len(self.legs)):
            leg = self.legs[idx]
            if dir == Direction.Incoming:
                if(stateAbbr in leg.destination):
                    relevantLegs.append(leg)
            elif dir == Direction.Outgoing:
                if(stateAbbr in leg.source):
                    relevantLegs.append(leg)
            elif dir == Direction.Both:
                if(stateAbbr in leg.source):
                    relevantLegs.append(leg)
                elif(stateAbbr in leg.destination):
                    relevantLegs.append(leg)
        return relevantLegs
    def addLegHelper(self, leg):
        lastLeg = self.legs[-1]
        if(lastLeg.destination != leg.source):
            raise ValueError("Destination of last leg in trip must equal source of next trip.")
        tmpLegs = self.legs
        tmpName = self.person
        tmpLegs.append(leg)
        newTrip = Trip(tmpName, tmpLegs)
        return newTrip
    def addTripHelper(self, trip):
        if(self.person != trip.person):
            raise ValueError("Person of both trips must be same.")
        tmpLegs = [ l for l in self.legs ]
        for l in trip.legs: tmpLegs.append(l)
        tmpName = self.person
        newTrip = Trip(tmpName, tmpLegs)
        return newTrip
    def __add__(self, other):
        newTrip = None
        if(isinstance(other, Leg)):
            newTrip = self.addLegHelper(other)
        elif(isinstance(other, Trip)):
            newTrip = self.addTripHelper(other)
        else:
            raise TypeError("Operands must be of correct types of Leg or Trip")
        return newTrip
class RoundTrip(Trip):
    def __init__(self, personName: str, listOfLegs: list) -> None:
        self.person = personName
        self._validateLegs(listOfLegs)
    def _validateLegs(self, listOfLegs: list) -> None:
        if(len(listOfLegs) < 2):
            raise ValueError("List of legs must contain 2 or more legs where the source zip of the first leg is equal to the destination zip of the last leg.")
        sourceZipOfFirstLeg = listOfLegs[0].source[-5:]
        destZipOfLastLeg = listOfLegs[-1].destination[-5:]
        if(sourceZipOfFirstLeg != destZipOfLastLeg):
            raise ValueError("List of legs must contain 2 or more legs where the source zip of the first leg is equal to the destination zip of the last leg.")
        self.legs = listOfLegs # All clear

# Required module functions
def getShortestTrip(source: str, destination: str, stops: list) -> Trip:
    sourceZip = source[-5:]
    destZip = destination[-5:]
    stopZips = [ s[-5:] for s in stops ]
    stopZips.append(sourceZip)
    stopZips.append(destZip)
    locationMap = getLocationMap(stopZips)
    shortestTrip = -1.0
    recordStop = ""
    for stop in stops:
        srcLongLat = locationMap[source[-5:]]
        stopLongLat = locationMap[stop[-5:]]
        destLongLat = locationMap[destination[-5:]]
        milesToStop = calculateDistance(srcLongLat, stopLongLat)
        milesToDest = calculateDistance(stopLongLat, destLongLat)
        if(milesToStop + milesToDest < shortestTrip or shortestTrip == -1.0):
            recordStop = stop
            shortestTrip = milesToStop + milesToDest
    L1 = Leg(source, recordStop)
    L2 = Leg(recordStop, destination)
    T = Trip("", [L1, L2])
    return T
def getTotalDistanceFor(person: str) -> float:
    personTrips = getTripsFor(person)
    totalDistance = 0.0
    for trip in personTrips:
        tripZips = [ place[-5:] for place in trip ]
        locationMap = getLocationMap(tripZips)
        for idx in range(len(trip)-1):
            tripLeg = Leg(trip[idx], trip[idx+1])
            totalDistance += tripLeg.calculateLength(locationMap)
    return format(totalDistance, '.2f')
def getRoundTripCount() -> int:
    tripsPath = os.path.join(DataPath, "trips.dat")
    with open(tripsPath) as f:
        lines = f.readlines()
    roundTripCount = 0
    stopPattern = r"\"([A-Z\sa-z]+,\s[A-Z]{2}\s[A-Z0-9]{5})\""
    for line in lines:
        tripLegs = []
        results = re.findall(stopPattern, line)
        if(len(results) == 2):
            pass
        else:
            for idx in range(0, len(results)-1):
                tripLegs.append(Leg(results[idx], results[idx+1]))
            try:
                rT = RoundTrip(" ", tripLegs)
                roundTripCount = roundTripCount + 1 # if initialization passed
            except ValueError:
                roundTripCount = roundTripCount # if error thrown
    return roundTripCount
def getTrafficCount(**kwargs) -> int:
    direction = None
    code = None
    state = None
    try:
        direction = kwargs["direction"]
        if not isinstance(direction, Direction):
            raise ValueError("Arguments 'direction', 'code'||'state' must be present.")
    except KeyError:
        raise ValueError("Arguments 'direction', 'code'||'state' must be present.")
    try:
        code = kwargs["code"]
    except KeyError:
        try:
            state = kwargs["state"]
        except KeyError:
            raise ValueError("Arguments 'direction', 'code'||'state' must be present.")

    count = 0
    if(code != None):
        count = getTrafficCountByCode(direction, code)
    else:
        count = getTrafficCountByState(direction, state)
    return count
def getTrafficCountByCode(direction: Direction, code: str) -> int:
    tripsPath = os.path.join(DataPath, "trips.dat")
    with open(tripsPath) as f:
        lines = f.readlines()
    trafficCount = 0
    stopPattern = r"\"([A-Z\sa-z]+,\s[A-Z]{2}\s[A-Z0-9]{5})\""
    pattern = code
    for line in lines:
        matches = re.search(pattern, line)
        if matches:
            results = re.findall(stopPattern, line)
            if(direction == Direction.Incoming):
                for idx in range(0, len(results) - 1):
                    if code in results[idx + 1]:
                        trafficCount += 1
            elif(direction == Direction.Outgoing):
                for idx in range(0, len(results) - 1):
                    if code in results[idx]:
                        trafficCount += 1
            elif(direction == Direction.Both):
                for idx in range(0, len(results) - 1):
                    if code in results[idx] or code in results[idx+1]:
                        trafficCount += 1
    return trafficCount
def getTrafficCountByState(direction: Direction, state: str) -> int:
    tripsPath = os.path.join(DataPath, "trips.dat")
    with open(tripsPath) as f:
        lines = f.readlines()
    trafficCount = 0
    stopPattern = r"\"([A-Z\sa-z]+,\s[A-Z]{2}\s[A-Z0-9]{5})\""
    pattern = state
    for line in lines:
        matches = re.search(pattern, line)
        if matches:
            results = re.findall(stopPattern, line)
            if (direction == Direction.Incoming):
                for idx in range(0, len(results) - 1):
                    if state in results[idx + 1]:
                        trafficCount += 1
            elif (direction == Direction.Outgoing):
                for idx in range(0, len(results) - 1):
                    if state in results[idx]:
                        trafficCount += 1
            elif (direction == Direction.Both):
                for idx in range(0, len(results) - 1):
                    if state in results[idx] or state in results[idx + 1]:
                        trafficCount += 1
    return trafficCount

# Helper module functions
def getLocationMap(listOfZips: list) -> dict:
    locationsPath = os.path.join(DataPath, "locations.dat")
    with open(locationsPath) as f:
        lines = f.readlines()
    pattern = r"([\.\-\+\d]+)"
    locationMap = {}
    for line in lines[1:]:
        line = line.split(",")
        if line[0].strip("\"") in listOfZips:
            latitude = line[2]
            matches = re.search(pattern, latitude)
            latitude = matches.group(0)
            longitude = line[3]
            matches = re.search(pattern, longitude)
            longitude = matches.group(0)
            locationMap[line[0].strip("\"")] = (float(latitude), float(longitude))
    return locationMap
def getTripsFor(person: str) -> list:
    relevantTrips = []
    tripsPath = os.path.join(DataPath, "trips.dat")
    with open(tripsPath) as f:
        lines = f.readlines()
    pattern = person
    stopPattern = r"\"([A-Z\sa-z]+,\s[A-Z]{2}\s[A-Z0-9]{5})\""
    for line in lines:
        matches = re.search(pattern, line)
        if(matches):
            results = re.findall(stopPattern, line)
            relevantTrips.append(results)
    return relevantTrips

# Test methods
def __TEST_1( ):
    print("TEST 1: Leg and str representation of Leg")
    srcTest = "Packwood, WA 98361"
    destTest = "Naples, FL 34108"
    c = Leg(srcTest, destTest)
    print(c)
def __TEST_2( ):
    pp("TEST 2: getShortestTrip( )")
    stops = ["Plantation, FL 33317", "Johnstown, OH 43031", "Sumner, MO 64681"]
    T = getShortestTrip("Wallingford, PA 19086", "Packwood, WA 98361", stops)
    for l in T.legs:
        print(l)
def __TEST_3( ):
    pp("TEST 3: getTotalDistanceFor( person )")
    distance1 = getTotalDistanceFor("Coleman, Lori")
    pp(distance1)
    distance2 = getTotalDistanceFor("Garcia, Martha")
    pp(distance2)
def __TEST_4( ):
    pp("TEST 4: getRoundTripCount( )")
    count = getRoundTripCount()
    pp(count)
def __TEST_5( ):
    pp("TEST 5: getTrafficCount( )")
    count = getTrafficCount(**{"direction": Direction.Incoming, "code": "01450"})
    pp(count)
    count = getTrafficCount(**{"direction": Direction.Incoming, "state": "MA"})
    pp(count)

if __name__ == "__main__":
    __TEST_1()
    __TEST_2()
    __TEST_3()
    __TEST_4()
    __TEST_5()
