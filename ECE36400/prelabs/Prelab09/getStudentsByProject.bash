#!/bin/bash
# ######################################################
# Author :  Andrew St. Pierre
# email :   astpier@purdue.edu
# ID :      ee364b17
# Date :    Saturday, March 16, 2019
# ######################################################

# Data Path
DataPath=~ee364/DataFolder/Prelab09
#DataPath=DataFolder/

# Check input
if (( $# < 1 ))
then
	echo "Usage: getStudentsByProject.bash <PROJECT-ID>"
	exit 1
else
    PROJ=$1
fi

# Data files
Projects=$DataPath"/maps/projects.dat"
Students=$DataPath"/maps/students.dat"

# Query regex matching circuits
pattern="\K([0-9a-zA-Z]{2}-[0-9a-zA-Z]-[0-9a-zA-Z]{2})(?=.*$PROJ)"
circuits=($(grep -oP $pattern $Projects | sort | uniq))

# Use the circuits used in project given to get participants for each
idPattern="^[0-9]{5}-[0-9]{5}"
studentIDs=()
for(( i=0; i<=${#circuits[@]}; i++ ))
do
	if [[ ${circuits[i]} =~ [0-9]{2}-[0-9]{1}-[0-9]{2} ]]
	then
		moreStudentIDs=($(grep -E ${idPattern} $DataPath/circuits/circuit_${circuits[i]}.dat))
		studentIDs=("${moreStudentIDs[@]}" "${studentIDs[@]}")
	fi
done

# Declare an array and use IDs to get the student names
declare -a studentNames=()
for(( i=0; i<=${#studentIDs[@]}; i++ ))
do
	if [[ ${studentIDs[i]} =~ [0-9]{5}-[0-9]{5} ]]
	then
		namePattern="\K([A-Za-z]{1,},{1}\s{1}[A-Za-z]{1,})(?=.*${studentIDs[i]})"
		anotherName=$(grep -oP $namePattern $Students)
		studentNames+=($(printf "(%s%s)\n" ${anotherName[@]}))
	fi
done

# Sort and ensure names are unique
studentNames=($(echo "${studentNames[@]}" | tr ' ' '\n' | sort -u)) # | tr '\n' ' '))
studentNames=($(echo "${studentNames[@]}" | sed 'y/(/ /' | sed 'y/)/ /' ))

# Show results
for(( i=0; i<=${#studentNames[@]}; i++ ))
do
	first=$(echo ${studentNames[i]} | cut -d',' -f1)
	last=$(echo ${studentNames[i]} | cut -d',' -f2)
	if [[ $first != '' ]]
	then
		echo $first, $last
	fi

done

# Check number of names
#echo ${#studentNames[@]}
