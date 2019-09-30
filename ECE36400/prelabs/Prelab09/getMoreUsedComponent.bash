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
if (( $# < 2 ))
then
	echo "Usage: getMoreUsedComponent.bash <Component1-ID> <Component2-ID>"
	exit 1
else
    COMPONENT1=$1
    COMPONENT2=$2
fi

# Data files
CircuitFiles=($(ls $DataPath"/circuits" | sort -u))

# Search component1 ID accross all circuits
pattern1="^[' ']*$COMPONENT1"
USES1=($(grep -r -c $COMPONENT1 $DataPath | grep -v :0 | grep -Eo "[0-9]{1,}$"))
numUsesComp1=${#USES1[@]}

# Search component2 ID accross all circuits
pattern2="^[' ']*$COMPONENT2"
USES2=($(grep -r -c $COMPONENT2 $DataPath | grep -v :0 | grep -Eo "[0-9]{1,}$"))
numUsesComp2=${#USES2[@]}

# Echo the component used in more circuits
if [[ "$numUsesComp1" -gt "$numUsesComp2" ]]
then
    echo $COMPONENT1
    #echo $COMPONENT1:$numUsesComp1 vs. $COMPONENT2:$numUsesComp2
else
    echo $COMPONENT2
    #echo $COMPONENT1:$numUsesComp1 vs. $COMPONENT2:$numUsesComp2
fi
