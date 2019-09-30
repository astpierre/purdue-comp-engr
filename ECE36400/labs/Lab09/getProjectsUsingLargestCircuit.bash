#!/bin/bash
###########################################################
# Author:  Andrew St. Pierre
# email:   astpier@purdue.edu
# ID:      ee364b17
# Date:    Tuesday, March 19, 2019
###########################################################

DataPath=~ee364/DataFolder/Lab09

# Data files
Projects=$DataPath"/maps/projects.dat"
Students=$DataPath"/maps/students.dat"

# Find the largest circuit
top10=($(ls -S -l -h $DataPath"/circuits/" | head | cut -d ' ' -f 9))
LargestCircuitFile=${top10} # first element is the largest file name
pattern="[0-9]{2}-[0-9]{1}-[0-9]{2}"
LargestCircuitID=$(echo $LargestCircuitFile | grep -Eo $pattern)
projectID="[0-9A-Z]{8}-[0-9A-Z]{4}-[0-9A-Z]{4}-[0-9A-Z]{4}-[0-9A-Z]{12}"
grep -E $LargestCircuitID $Projects | grep -Eo $projectID | sort -u

#echo ${#LargestCircuit[@]}








