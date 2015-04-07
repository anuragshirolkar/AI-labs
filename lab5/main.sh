#! /bin/bash
rm -rf data/answer_* data/r_test_data_* data/test_data_* data/training_data_* data/r_answer_* data/expected_answer_*
rm -rf tables_*.txt r_tables_*.txt
python isolator.py data/main_data.txt
./trainer.sh
./runner.sh
./results.sh > results.txt

echo "Stored results in results.txt"