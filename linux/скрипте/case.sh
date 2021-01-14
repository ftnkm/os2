#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Greska. Unesite broj izmedju 1 i 12"
	exit 1
fi

br=$1

case $br in
1)
echo "Januar"
;;
2)
echo "Februar"
;;
3) 
echo "Mart"
;;
4) 
echo "April"
;;
5)
echo "Maj"
;;
6)
echo "Jun"
;;
7)
echo "Jul"
;;
8)
echo "Avgust"
;;
9)
echo "Septembar" 
;; 
10)
echo "Octobar"
;;
11)
echo "Novembar"
;;
12)
echo "Decembar"
;;
*)
	echo "Greska. Nema meseca koji odgovara tom broju."
	echo "Unesite broj izmedju 1 i 12"
	exit 2
	;;
esac

exit 0
				 
