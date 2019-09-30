#!/usr/bin/env python3.7

#######################################################
#   Author:     Andrew St. Pierre
#   email:      astpier@purdue.edu
#   ID:         ee364b17
#   Date:       02/05/2019
#######################################################

import os
import sys
from collections import namedtuple

DataPath = os.path.expanduser("~ee364/DataFolder/Lab04")

def getProviderFiles():
    fileList = []
    with os.scandir(os.path.join(DataPath, "providers")) as dir:
        for f in dir:
            if not f.name.startswith('.') and f.is_file():
                fileList.append(f.name)
    return fileList

def getProviderData(fileName):
    Item = namedtuple("Item", ["provider", "board", "price"])
    itemList = []
    with open(os.path.join(DataPath, "providers/"+fileName)) as f:
        lines = f.readlines()
        lines = lines[3:]
    provider = fileName.strip(".dat")
    for line in lines:
        board, price = line.split(",")
        board = board.strip()
        price = float(price.strip().strip("\n").strip("$"))
        newItem = Item(provider, board, price)
        itemList.append(newItem)
    return itemList

def getDifference(provider1, provider2):
    providers = [i.strip(".dat") for i in getProviderFiles()]
    if provider1 not in providers:
        raise ValueError("Provider data not availible: "+provider1)
    if provider2 not in providers:
        raise ValueError("Provider data not availible: "+provider2)
    provider1_file = provider1+".dat"
    provider2_file = provider2+".dat"
    provider1_data = getProviderData(provider1_file)
    provider1_boards = [i.board for i in provider1_data]
    provider2_data = getProviderData(provider2_file)
    provider2_boards = [i.board for i in provider2_data]
    diffSet = set()
    for sbc in provider1_boards:
        if sbc not in provider2_boards:
            diffSet.add(sbc)
    return diffSet

def getPriceOf(sbc, provider):
    providers = [i.strip(".dat") for i in getProviderFiles()]
    if provider not in providers:
        raise ValueError("Provider data not availible: " + provider)
    provider_file = provider + ".dat"
    provider_data = getProviderData(provider_file)
    provider_boards = [i.board for i in provider_data]
    if sbc not in provider_boards:
        raise ValueError("Provider does not carry board: " + sbc)
    for item in provider_data:
        if item.board == sbc:
            return item.price

def checkAllPrices(sbcSet):
    priceReport = {}
    provider_files = getProviderFiles()
    for sbc in sbcSet:
        prices = {}
        for provider_file in provider_files:
            provider_data = getProviderData(provider_file)
            provider_boards = [i.board for i in provider_data]
            if sbc in provider_boards:
                for item in provider_data:
                    if item.board == sbc: prices[provider_file.strip(".dat")] = item.price
        minPrice = -1.0
        for p in prices:
            if minPrice == -1.0:
                minPrice = prices[p]
                minProvider = p
            else:
                if prices[p] < minPrice:
                    minPrice = prices[p]
                    minProvider = p
        priceReport[sbc] = (minPrice, minProvider)
    return priceReport


if __name__ == "__main__":
    print("Hello World.")
    '''
    diffBoards = getDifference("provider1","provider2")
    for board in diffBoards:
        print(f"{board} DNE in provider2, but exists in provider1 || type(boards)={type(diffBoards)}, type(board)={type(board)}")

    board = "Rasp. Pi-5500U"
    provider = "provider3"
    priceOf = getPriceOf(board, provider)
    print(f"Price of {board} from {provider}= {priceOf} || type(priceOf)={type(priceOf)}")

    sbcSet = set(["Rasp. Pi-4700EQ", "Rasp. Pi-5500U", "Rasp. Pi-6920HQ"])
    priceReport = checkAllPrices(sbcSet)
    for result in priceReport:
        print(f"board= {result}, price= {priceReport[result][0]}, provider= {priceReport[result][1]}")
        print(f"type(priceReport[result])={type(priceReport[result])},type(priceReport[result][0])={type(priceReport[result][0])},type(priceReport[result][1])={type(priceReport[result][1])}")
    '''