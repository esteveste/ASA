#!/bin/bash

# Read type as 1st argument
EXEC=./gerador
FILES=./tests

ARCHES=3

for v in `seq 1000000 1000000 15000000`; do
	a=$(expr $v \* $ARCHES)
	printf "Generating for $v vertices and approximately $(expr $v + $a) arches, of type $TYPE\n"
	$EXEC $v $a 1000 1 $v > temp.in
	#a=$(cat temp.in | sed -n 1p | awk '{ printf( "%d", $2) }')
	mv temp.in $FILES/$v\_$a.in
done

exit 0
