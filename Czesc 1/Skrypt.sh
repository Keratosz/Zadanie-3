#!/bin/bash

A=( 4 -3 22 4 -23 -21 32 35 22 -13 0 -22 )
B=( 2 4 7 3 44 10 23 -33 33 10 -3 2 )
C=( 4 5 6 75 34 -23 32 54 1 0 8 -23 ) 
D=( 6 5 12 15 35 23 43 67 2 -11 2 32 )
E=( 2 0 32 2 4 0 42 -23 12 -32 23 -10 ) 
F=( 24 2 3 -24 21 12 13 17 22 32 -122 )
G=( 13 24 -32 221 -23 -32 23 21 34 10 23 234 )
H=( 10 88 -123 23 24 32 98 21 19 54 23 156 ) 
OutPut=( 0 0 1 0 0 0 0 0 0 0 0 0 )

for ind in `seq 0 11`; do
	out=`./Warunek ${A[$ind]} ${B[$ind]} ${C[$ind]} ${D[$ind]} ${E[$ind]} ${F[$ind]} ${G[$ind]} ${H[$ind]}`
	if [ "$out" != "${OutPut[$ind]}" ]
	then
		echo "input" ${A[$ind]} ${B[$ind]} ${C[$ind]} ${D[$ind]} ${E[$ind]} ${F[$ind]} ${G[$ind]} ${H[$ind]}
		echo "output actual" $out
		echo "output expeccted" ${OutPut[$ind]}
	fi
done
