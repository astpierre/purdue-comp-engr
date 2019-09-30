#!/bin/bash
###########################################################
# Author:  Andrew St. Pierre
# email:   astpier@purdue.edu
# ID:      ee364b17
# Date:    Tuesday, March 19, 2019
###########################################################

DataPath=~ee364/DataFolder/Lab09

# Check input
if (( $# < 1 ))
then
    echo "Usage: getComponentsByStudent.bash <LAST, FIRST>"
    exit 1
else
    STUDENT=$1
fi

# Data files
Projects=$DataPath"/maps/projects.dat"
Students=$DataPath"/maps/students.dat"

# Search for student's ID
idPattern="$STUDENT.*[0-9]{5}-[0-9]{5}"
studentID=($(grep -s -E -h $idPattern $Students | grep -Eo "[0-9]{5}-[0-9]{5}"))

# echo $studentID
CircuitFiles=($(ls $DataPath"/circuits/" | sort -u))
declare -a studentCircuits=()
for(( i=0; i<=${#CircuitFiles[@]}; i++ ))
do
    anotherFile=$(grep -E -l -s $studentID $DataPath"/circuits/"${CircuitFiles[i]} | grep -Eo "[0-9]{2}-{1}[0-9]{1}-{1}[0-9]{2}")
    if [ ! -z "$anotherFile" ]
    then
        studentCircuits+=($(printf "%s" ${anotherFile}))
    fi
done

studentCircuits=($(echo "${studentCircuits[@]}" | tr ' ' '\n' | sort -u))
declare -a studentComponents=()
for(( i=0; i<=${#studentCircuits[@]}; i++ ))
do
    if [ ! -z "${studentCircuits[i]}" ]
    then
        moreComponents=($(grep -E -s "[A-Z]{3}-[0-9]{3}" $DataPath"/circuits/circuit_"${studentCircuits[i]}".dat"))
        if [ ! -z "$moreComponents" ]
        then
            for(( j=0; j<=${#moreComponents[@]}; j++ ))
            do
                studentComponents+=($(printf "%s" ${moreComponents[j]}))
            done
        fi
    fi
done

studentComponents=($(echo "${studentComponents[@]}" | tr ' ' '\n' | sort -u))
for(( i=0; i<=${#studentComponents[@]}; i++ ))
do
    if [ ! -z "${studentComponents[i]}" ]
    then
        echo "${studentComponents[i]}"
    fi
done

#echo ${#studentComponents[@]}







