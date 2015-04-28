#!/bin/bash

python train.py data/training_data > data/tables.txt 
python train.py data/training_data 1 > data/r_tables.txt 

for i in `seq 1 5`
do
	python train.py data/training_data_$i > data/tables_$i.txt 
done

for i in `seq 1 5`
do
	python train.py data/training_data_$i 1 > data/r_tables_$i.txt 
done