#!/bin/bash 
# 1) let
# 2) expr 
# 3) $(( . .... )  
 
sabiranje() {
	# metoda 1. let
	let odg1=($br1 + $br2) 
	# metoda 2. expr 
	odg2=`expr $br1 + $br2`
	# metoda 3. $((...) 
	odg3=$(($br1 + $br2)) 
}  
#--------------------------- 
oduzimanje() {
	# metoda 1. let
	let odg1=($br1 - $br2) 
	# metoda 2. expr 
	odg2=`expr $br1 - $br2`
	# metoda 3 $((...) 
	odg3=$(($br1 - $br2)) 
} 
#--------------------------- 
mnozenje() { 
	# metoda 1. let
	let odg1=($br1 * $br2) 
	# metoda 2.  expr
	odg2=`expr $br1 \* $br2` 
	# metoda 3 $((...) 
	odg3=$(($br1 * $br2)) 
} 
#--------------------------- 
deljenje() { 
	# metoda 1. let
	let odg1=($br1 / $br2) 
	# metoda 2.  expr
	odg2=`expr $br1 / $br2` 
	# metoda 3 $((...) 
	odg3=$(($br1 / $br2)) 
} 
#--------------------------- 


if [ $# -lt 3 ]
then 
	echo "Neispravan poziv skripte" 
	echo "Nakon imena skripte unesite koju operaciju zelite: (s,o,m,d) i dva broja"
	echo "" 
	exit 1 
fi 
#---------------------------------------------------------- 
br1=$2
br2=$3 
if [ $1 == "s" ]
	then
		sabiranje
fi

if [ $1 == "o" ] 
	then 
		oduzimanje
fi

if [ $1 == "m" ] 
	then
		mnozenje
fi

if [ $1 == "d" ] 
	then
		deljenje
fi 
#----------------------------------------------- 
													 
echo "Metoda1 odgovor je $odg1"
echo "Metoda2 odgovor je $odg2"
echo "Metoda3 odgovor je $odg3"

