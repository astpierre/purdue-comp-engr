#!/bin/bash
###########################################################
# Author:  Andrew St. Pierre
# email:   astpier@purdue.edu
# ID:      ee364b17
###########################################################

DataPath=~ee364/DataFolder/Lab09

# Data files
Projects=$DataPath"/maps/projects.dat"
Students=$DataPath"/maps/students.dat"

# Find the largest circuit
FilesAndSizes=($(ls -S -l -h $DataPath"/circuits/" | cut -d ' ' -f 9,5))
declare -a largeCircuits=()
for(( i=0; i<=${#FilesAndSizes[@]}-1; i+=2 ))
do
    fsize=${FilesAndSizes[i]}
    fname=${FilesAndSizes[i+1]}

    if [ $fsize -ge 200 ]
    then
         circuitID=$(echo $fname | grep -Eo "[0-9]{2}-[0-9]{1}-[0-9]{2}")
         largeCircuits+=($(printf "%s\n" $circuitID))
    fi
done

largeCircuits=($(echo "${largeCircuits[@]}" | tr ' ' '\n' | sort -u))
for(( i=0; i<=${#largeCircuits[@]}; i++ ))
do
    if [[ ${largeCircuits[i]} != '' ]]
    then
        echo ${largeCircuits[i]}
    fi
done
