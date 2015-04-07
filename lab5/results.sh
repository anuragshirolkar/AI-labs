#!/bin/bash

for i in `seq 1 5`
do
	echo ""
	echo "Result for Fold no $i"
	./accuracy.py data/answer_$i data/output_$i
done