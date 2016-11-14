#!/bin/bash

make

var=$1
COUNTER=0
while [ $COUNTER -lt 10 ]; do	
	./main "$var"
	var=$((var+60))
	COUNTER=$((COUNTER+1))
done
