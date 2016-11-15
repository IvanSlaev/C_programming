#!/bin/bash

make

var=$1
COUNTER=0
while [ $COUNTER -lt 4 ]; do	
	echo
	echo "START TEST *******************************************"
	./main "$var"
	var=$((var+2))
	COUNTER=$((COUNTER+1))
	echo "Code Coverage ****************************************"
	gcov -b main.c
	cat main.c.gcov
	echo "END OF TEST ******************************************"
	echo
done

rm main main.gcda main.gcno main.c.gcov
echo "main removed"
echo "main.c.gcov removed"
echo "main.gcda removed"
echo "main.gcno removed"
