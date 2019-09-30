#!/bin/bash
# ######################################################
# Author :  Andrew St. Pierre
# email :   astpier@purdue.edu
# ID :      ee364b17
# Date :    Wednesday, March 6, 2019
# ######################################################

# Data Path
DataPath=~ee364/DataFolder/Prelab09
#DataPath=DataFolder/

# Check input
if (( $# < 1 ))
then
	echo "Usage: getCircuitsByProject.bash <PROJECT-ID>"
	exit 1
fi

# Input var
PROJ=$1

# Data files
Projects=$DataPath"/maps/projects.dat"
Students=$DataPath"/maps/students.dat"
CircuitFiles=$(ls $DataPath"/circuits/")

# Querry regex matching
pat="[0-9a-zA-Z]{2}-[0-9a-zA-Z]-[0-9a-zA-Z]{2}.*$PROJ"
circuits=($(grep -E $pat $Projects | sort | uniq))

# Loop to display
for(( i=0; i<=${#circuits[@]}; i++ ))
do
    if [[ ${circuits[i]} =~ [0-9a-zA-Z]{2}-[0-9a-zA-Z]-[0-9a-zA-Z]{2} ]]
    then
    echo ${circuits[i]}
    fi
done
