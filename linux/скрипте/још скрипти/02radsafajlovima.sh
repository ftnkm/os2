#!/bin/bash
echo "Koje ime zelite da date direktorijumu?"
read ime

mkdir $ime

cd $ime

echo "Ovo je direktorijum `pwd`"

touch dat1 dat2 dat3

echo "Ovo je $ime/dat1" > dat1
echo "Ovo je $ime/dat2" > dat2
echo "Ovo je $ime/dat3" > dat3

echo "Imena datoteka u direktorijumu $ime su:"
ls -hl

echo "Sadrzaj datoteka:"
cat dat1
cat dat2
cat dat3

echo "Dovidjenja"
