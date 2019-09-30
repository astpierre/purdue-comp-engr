#!/bin/bash
# ######################################################
# Author :  Andrew St. Pierre
# email :   astpier@purdue.edu
# ID :      ee364b17
# Date :    Sunday, March 17, 2019
# ######################################################

# Data Path
DataPath=~ee364/DataFolder/Prelab09
#DataPath=DataFolder/

# Check input
if (( $# < 1 ))
then
	echo "Usage: getCircuitsByStudent.bash <LastName, FirstName>"
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

# Search student ID accross all circuits
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

# Sort an ensure unique
studentCircuits=($(echo "${studentCircuits[@]}" | tr ' ' '\n' | sort -u))

# Print to std out
for(( i=0; i<=${#studentCircuits[@]}; i++ ))
do
    if [ ! -z "${studentCircuits[i]}" ]
    then
        echo ${studentCircuits[i]}
    fi
done
