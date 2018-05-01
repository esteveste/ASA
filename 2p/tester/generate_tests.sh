#!/bin/bash

# Read type as 1st argument
EXEC=./gera
FILES=./tests

ARCHES=3
mkdir tests

for v in `seq 2 10 122`; do
	a=$(expr $v \* $ARCHES)
	printf "Generating for $v vertices and approximately $(expr $v + $a) arches, of type $TYPE\n"
	$EXEC $v 0 > temp.in
	#a=$(cat temp.in | sed -n 1p | awk '{ printf( "%d", $2) }')
	mv temp.in $FILES/$v.in
done

exit 0
