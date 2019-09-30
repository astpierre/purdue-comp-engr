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
	echo "Usage: getComponentUses.bash <Component-ID>"
	exit 1
else
    COMPONENT=$1
fi

# Data files
CircuitFiles=($(ls $DataPath"/circuits" | sort -u))

# Search component ID accross all circuits
USES=($(grep -r -c $COMPONENT $DataPath | grep -v :0 | grep -Eo "[0-9]{1,}$"))

# Echo the number of circuits component is used in
echo ${#USES[@]}
