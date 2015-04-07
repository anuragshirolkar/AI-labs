#!/bin/bash
echo "========================"
echo "GRAPHENE TO PHONEME"
echo "========================"
sum=0
for i in `seq 1 5`
do
	echo ""
	echo "Result for Fold no $i"
	a=`./accuracy.py data/answer_$i data/output_$i`
	echo $a
	sum=`python -c "print $a+$sum"`
done

echo ""
echo "Average Accuracy"
python -c "print $sum/5.0"
echo ""
echo "========================"
echo "PHONEME TO GRAPHENE"
echo "========================"
sum=0
for i in `seq 1 5`
do
	echo ""
	echo "Result for Fold no $i"
	a=`./accuracy.py data/r_answer_$i data/output_$i 1`
	echo $a
	sum=`python -c "print $a+$sum"`
done

echo ""
echo "Average Accuracy"
python -c "print $sum/5.0"
echo ""