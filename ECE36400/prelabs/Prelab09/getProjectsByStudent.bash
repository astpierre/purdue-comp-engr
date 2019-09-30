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
	echo "Usage: getProjectsByStudent.bash <LastName, FirstName>"
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

# Collect all project IDs that use these circuits
idPattern="[0-9a-zA-Z]{8}-{1}[0-9a-zA-Z]{4}-{1}[0-9a-zA-Z]{4}-{1}[0-9a-zA-Z]{4}-{1}[0-9a-zA-Z]{12}$"
declare -a studentProjects=()
for(( i=0; i<=${#studentCircuits[@]}; i++ ))
do
    pattern="^[' ']*${studentCircuits[i]}[' ']{10}$idPattern"
    moreProjects=$(grep -s -E "$pattern" $Projects | grep -Eo "$idPattern")
    if [ ! -z "$moreProjects" ]
    then
        studentProjects=("${moreProjects[@]}" "${studentProjects[@]}")
    fi
done

# Sort an ensure unique
studentProjects=($(echo "${studentProjects[@]}" | tr ' ' '\n' | sort -u))

# Show results
for(( i=0; i<=${#studentProjects[@]}; i++ ))
do
    if [ ! -z "${studentProjects[i]}" ]
    then
        echo "${studentProjects[i]}"
    fi
done
