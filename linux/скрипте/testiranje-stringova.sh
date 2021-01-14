#!/bin/bash

echo "Unesite neki string"
read mojstring1
echo "Unesite drugi string"
read mojstring2

#------------------------------------
echo "Da li je string 1 prazan? Vrednost 1 znaci FALSE"
test -z $mojstring1
echo $?

echo "Da li je string 2 neprazan? Vrednost 0 znaci TRUE;"
test -n $mojstring2
echo $?

#------------------------------------
mojaduzina1=${#mojstring1} 
mojaduzina2=${#mojstring2} 

if [ $mojaduzina1 -gt $mojaduzina2 ]
then
echo "String 1 je duzi od stringa 2"
else
if [ $mojaduzina2 -gt $mojaduzina1 ]
then
echo "String 2 je duzi od stringa 1" 
else 
echo "String 1 je iste duzine kao string 2"
fi
fi

#------------------------------------
if [ $mojstring1 == $mojstring2 ]
then
echo "String 1 je isti kao string 2"
else
	if [ $mojstring1 != $mojstring2 ]
		then
	echo "String 1 se razlikuje od stringa 2"
	fi
fi
