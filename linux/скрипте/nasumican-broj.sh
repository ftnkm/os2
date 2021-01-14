#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Unesite neku rec"
	exit 1
fi

randomBroj=$RANDOM

echo "$1-$randomBroj"

########################################

exit 0 
