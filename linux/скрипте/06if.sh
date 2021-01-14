#!/bin/bash
dat=$1
if [ -f $dat ]
then
	echo -e "Datoteka $dat postoji!"
else
	echo -e "Datoteka $dat ne postoji!"
fi
