#!/bin/bash

## Read input from stdin (given as parameter during execution)
EXEC=${1:-/dev/stdin}
FILES=tests/*
REPETITIONS=1

for f in $FILES; do
	## Start the clock!
	START=$(($(date +%s%N)/1000000))

	## Run the test
	for ((j=1; j<=$REPETITIONS; j++)); do
		$EXEC < $f > /dev/null
	done

	## Stop the clock!
	END=$(($(date +%s%N)/1000000))

	## Calculate time difference
	DIFF=$(( $END - $START ))

	#printf "Input $f benchmark took $DIFF milliseconds for $REPETITIONS repetitions\n"
	printf "$f, $DIFF\n"
done
exit 0
