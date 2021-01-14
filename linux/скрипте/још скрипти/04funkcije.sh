#!/bin/bash 

fun1() { 
	echo "Ovo je poruka iz funkcije1"
} 
#----------------------------- 
fun2() { 
	echo "Ovo je poruka iz funkcije2"
} 
#----------------------------- 
fun3() { 
	echo "Ovo je poruka iz funkcije3"
} 

# Glavni deo skripte
echo "Unesite broj od 1 do 3"
read izbor 

fun$izbor
echo ""
