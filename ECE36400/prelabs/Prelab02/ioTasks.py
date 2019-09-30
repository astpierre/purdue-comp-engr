###############################################################################
#   Author:	Andrew St. Pierre
#   email: 	astpier@purdue.edu
#   ID: 	ee364b17
#   Date: 	Tuesday, January 15, 2019
###############################################################################

import os
import sys
from datetime import datetime

# Module level variables
DataPath = os.path.expanduser('~ee364/DataFolder/Prelab02')
DevDataPath = os.path.expanduser('~/prelabs-astpierre/Prelab02')

def getFilesList(isDev=False) -> list:
    if isDev:
        path = os.path.join(DevDataPath, "stocks/")
    else:
        path = DataPath
    fileList = []
    with os.scandir(path) as dir:
            for f in dir:
                if not f.name.startswith('.') and f.is_file():
                    fileList.append(f.name)
    return fileList

def checkSymbolExists(symbol: str) -> bool:
    """
    Takes in a company symbol and returns True if the file exists on path.
    Returns False otherwise.
    """
    fileList = getFilesList()
    for file in fileList:
        if symbol == file.strip(".dat"): return True
    return False

def getDataDict(symbol: str) -> dict:
    """
    Takes in a company symbol and returns the data from the *.dat file in
    the form of a dictionary.
    dataDict = {"<date-str": ["close","volume","open","high","low"]}
    """
    #TODO: fix path variable b4 submission
    with open(os.path.join(DataPath, symbol+".dat")) as f:
        data = [line.strip().split(",") for line in f.readlines()]
        dataDict = {d[0]:d[1:] for d in data[2:]}
    return dataDict

def getMaxDifference(symbol: str) -> str:
    """
    Takes in a company symbol and returns the date as a string,
    where the diff between high and low values is the largest for that company.
    """
    # Check symbol given is valid
    if not checkSymbolExists(symbol): return None
    dataDict,maxDiff,maxDate = getDataDict(symbol),0,""
    for date in dataDict:
        # High - low = diff
        if float(dataDict[date][3]) - float(dataDict[date][4]) > maxDiff:
            maxDiff = float(dataDict[date][3]) - float(dataDict[date][4])
            maxDate = date
    return maxDate

def getGainPercent(symbol: str) -> float:
    """
    Takes in a company symbol and returns the percentage of days
    where the company's closing price is higher than its opening price.
    """
    # Check symbol given is valid
    if not checkSymbolExists(symbol): return None
    dataDict = getDataDict(symbol)
    gainCount,totalCount = 0,len(dataDict)
    for date in dataDict:
        # if Close - Open > 0.00, then gainCount += 1
        if float(dataDict[date][0]) - float(dataDict[date][2]) > 0.00:
            gainCount += 1
    return format(float(float(gainCount)/float(totalCount) * 100.00), '.4f')

def getVolumeSum(symbol: str, date1: str, date2: str) -> int:
    """
    Takes in a company symbol and two date strings and returns the
    sum of transaction volumes between these dates, inclusively.
    """
    # Check symbol given is valid
    if not checkSymbolExists(symbol): return None
    # Check the dates given are valid [assuming they exist in file]
    dateList1,dateList2 = date1.split("/"),date2.split("/")
    dateObj1 = datetime(int(dateList1[0]),int(dateList1[1]),int(dateList1[2]))
    dateObj2 = datetime(int(dateList2[0]),int(dateList2[1]),int(dateList2[2]))
    if dateObj1 >= dateObj2: return None

    # Begin processing dataset
    dataDict,volSum,valid = getDataDict(symbol),0,False
    for date in dataDict:
        if date == date1:
            valid = False
        if date == date2:
            valid = True
        if (valid == True) or (date == date1):
            volSum = volSum + float(dataDict[date][1])
        else: pass
    return int(volSum)

def getBestGain(date: str) -> float:
    """
    Takes in a date string and returns the highest positive gain
    percentage, calculated as ((close - open)/(open)) * (100).
    """
    # Check the contents of the directory containing the *.dat's
    fileList,bestGain = getFilesList(),0.00
    for company in fileList:
        dataDict = getDataDict(company.strip(".dat"))
        open,close = float(dataDict[date][2]),float(dataDict[date][0])
        if (((close - open)/open)*100.00) > bestGain:
            bestGain = (((close - open)/open)*100.00)
    return format(bestGain, '.4f')

def getAveragePrice(symbol: str, year: int) -> float:
    """
    Takes in a symbol string and year integer and returns the average
    price of the company's stock over that year.
    """
    # Check symbol given is valid
    if not checkSymbolExists(symbol): return None
    dataDict = getDataDict(symbol)
    averageTotal,dayCount = 0,0
    for date in dataDict:
        # if year in date, then find daily avg and add it to total and +1count
        if str(year) in date:
            open,close = float(dataDict[date][2]),float(dataDict[date][0])
            averageTotal += (close + open) / 2.0
            dayCount += 1
            print(f"yearRequested={year} | date={date} | dayCount={dayCount} | averageTotal={averageTotal}")
    return format(averageTotal/dayCount, '.4f')

def getCountOver(symbol: str, price: float) -> int:
    """
    Takes in a symbol string and stock price as a float and returns the num
    of days where all trade values [opening,closing,low,high] are above
    or equal to the given price.
    """
    # Check symbol given is valid
    if not checkSymbolExists(symbol): return None
    dataDict,dayCount = getDataDict(symbol),0
    for date in dataDict:
        if float(dataDict[date][0]) < price:
            break
        elif float(dataDict[date][2]) < price:
            break
        elif float(dataDict[date][3]) < price:
            break
        elif float(dataDict[date][4]) < price:
            break
        else: dayCount += 1
    return dayCount

if __name__ == "__main__":
    # Write anything here to test your code
    #print(getMaxDifference("FB"))
    #print(str(getGainPercent("AAPL")))
    #print(str(getVolumeSum("AAPL","2014/03/14","2014/04/25")))
    #print(str(getBestGain("2014/03/14")))
    #print(checkSymbolExists("FB"))
    #print(getAveragePrice("FB",2017))
    print(getCountOver("FB",52.00))
