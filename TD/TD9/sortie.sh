#!/bin/bash
./sortie1
var=$?
if [ $var -eq 0 ];
	then
		echo "Le nombre est entre 5 et 10"
	else
		echo "Le nombre n'est pas entre 5 et 10."
fi

