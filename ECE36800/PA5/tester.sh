#!/bin/bash

for i in 10 20 100 500 1000 2000 5000 10000 20000 100000 200000 500000 1000000
do
    echo "Generating $i random numbers"
    ./generate "$i" "input/$i.b"
done

for i in 10 20 100 500 1000 2000 5000 10000 20000 100000 200000 500000 1000000
do
    echo "Running quick sort on $i longs"
    ./pa5 "-q" "input/$i.b" "output/Q$i.txt"
done

for i in 10 20 100 500 1000 2000 5000 10000 20000 100000 200000 500000 1000000
do
    echo "Running merge sort on $i longs"
    ./pa5 "-m" "input/$i.b" "output/M$i.txt"
done
