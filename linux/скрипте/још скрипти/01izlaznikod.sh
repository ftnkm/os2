#!/bin/bash
ls nepostojecadatoteka > /dev/null 2>&1
status=`echo $?`
echo "Izlazni kod je $status"

touch nepostojecadatoteka

ls nepostojecadatoteka > /dev/null 2>&1
status=`echo $?`
echo "Izlazni kod je sada $status"

rm nepostojecadatoteka
