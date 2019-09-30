#!/bin/bash

DataPath=~ee364/DataFolder/Lab10

CITY=$1
grep -l -r "$CITY" "$DataPath" | grep -Eo "[0-9]{5}"

