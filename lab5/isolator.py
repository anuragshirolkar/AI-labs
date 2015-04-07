#!/usr/bin/python

import sys
import os.path

if len(sys.argv) < 2:
    print "Usage: python isolator.py <input-file>"
    sys.exit()
    pass

filename = sys.argv[1]

if not os.path.isfile(filename) :
    print "Unable to open file"
    sys.exit()

f = open(filename)

lines = []
for l in f:
    l1 = l.strip().split('\t')

    if '(' in list(l1[0]):
        continue
        
    if len(l1) !=2:
        continue
    
    if len(l1[0]) == len(l1[1].split(' ')):
        lines.append([l1[0],l.strip()])

mainfile = open("data/training_data","w")
training_data_files =[open("data/training_data_1","w"),open("data/training_data_2","w"),open("data/training_data_3","w"),open("data/training_data_4","w"),open("data/training_data_5","w")]    
test_data_files =[open("data/test_data_1","w"),open("data/test_data_2","w"),open("data/test_data_3","w"),open("data/test_data_4","w"),open("data/test_data_5","w")]    
r_test_data_files =[open("data/r_test_data_1","w"),open("data/r_test_data_2","w"),open("data/r_test_data_3","w"),open("data/r_test_data_4","w"),open("data/r_test_data_5","w")]    
answer_files =[open("data/answer_1","w"),open("data/answer_2","w"),open("data/answer_3","w"),open("data/answer_4","w"),open("data/answer_5","w")]    

length = len(lines)
for i in xrange(0,length):
    l = lines[i]
    mainfile.write(l[1]+'\n')
    index = int((i*5)/length)
    for x in xrange(0,5):
        if x == index:
            answer_files[x].write(l[1]+'\n')
            test_data_files[x].write(l[0]+' ')
            r_test_data_files[x].write(l[1].split('\t')[1]+'\n')
        else:
            training_data_files[x].write(l[1]+'\n')

for x in xrange(0,5):
    r_test_data_files[x].write('exit\n')