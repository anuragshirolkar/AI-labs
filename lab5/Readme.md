#Hidden Markov Model Assignment
##Graphene to Phoneme and Phoneme to Graphene

Details of Files:
* isolator.py - Used to isolate the words for which no of graphene = no of phoneme and generate 5 fold cross validation files
* r_viterbi.py - Phoneme to Graphene Conversion
* viterbi.py - Viterbi for Graphene to phoneme
* results.sh - Run Accuracy files for 5 fold validations
* results.txt - Final output results of results.sh
* train.py - Used to train HMM
* runner.sh - runs all viterbi
* trainer.sh - used in training
* main.sh - This isolates and then trains and then runs the script


To run the code-
./main.sh

To get the results-
./results.sh

To speak a word-
python viterbi.py | python speak.py


