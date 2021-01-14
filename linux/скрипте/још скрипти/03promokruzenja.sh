#!/bin/bash
ne="NE"
da="DA"
nepoznato="NEPOZNATO"

echo ""
echo "Ovaj program prihvata vrednost koja se prosledjuje promenjivoj okruzenja MOJODG"
echo ""
echo "Unesite broj 1 ili 2"
read vred

if [ $vred -eq 1 ]
then
	MOJODG=$da
else
	if [ $vred -eq 2 ]
	then
		MOJODG=$ne
	else
		MOJODG=$nepoznato
	fi
fi

export MOJODG
echo "Vrednost promenjive MOJODG je: $MOJODG"
