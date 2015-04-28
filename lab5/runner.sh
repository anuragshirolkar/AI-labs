#!/bin/bash

rm -rf data/answer_*
rm -rf data/r_answer_*

for i in `seq 1 5`
do
	python viterbi.py data/tables_$i.txt < data/test_data_$i > data/answer_$i &
done

for i in `seq 1 5`
do
	python r_viterbi.py data/r_tables_$i.txt < data/r_test_data_$i > data/r_answer_$i &
done