#!/bin/bash
echo "Unesite IP adresu"
read ip

if [ ! -z $ip ]
	then
		ping -c 2 $ip
		if [ $? -eq 0 ]
		then
			echo "Dobio sam odgovor"
		else
			echo "Nema odgovora"
		fi
	else
		echo "Niste unesli nista"
fi
