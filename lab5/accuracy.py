#!/usr/bin/python

import sys
import os.path

GRAPHENE_TO_PHONEME = True

if len(sys.argv) < 3:
    print "Usage: python accuracy.py <file1> <file2> <mode optional>"
    print "Mode : 0 for Graphene to Phoneme"
    print "Mode : 1 for Phoneme to Graphene"
    sys.exit()

if len(sys.argv) ==4:
    if sys.argv[3] == "1":
        GRAPHENE_TO_PHONEME = False


filename1 = sys.argv[1]
filename2 = sys.argv[2]

if not os.path.isfile(filename1) :
    print "Unable to open file" , filename1
    sys.exit()

if not os.path.isfile(filename2) :
    print "Unable to open file" , filename2
    sys.exit()

f1 = open(filename1)
f2 = open(filename2)
i = 0
lines1 = f1.readlines()
lines2 = f2.readlines()

if len(lines2) != len(lines1):
    print "No of lines don't match in two files"
    sys.exit()

l = len(lines1)
c1 = 0
c2 = 0
t1 = 0
t2 = 0
while i < l:
    try:       
        if GRAPHENE_TO_PHONEME:
            l1 = lines1[i].strip().split('\t')[1].split(' ')
            l2 = lines2[i].strip().split('\t')[1].split(' ')
        else:
            l1 = list(lines1[i].strip().split('\t')[0])
            l2 = list(lines2[i].strip().split('\t')[0])
        #print l1 , " : " , l2
        if l1 == l2 :
            c1 = c1 + 1
        t1 = t1 + 1

        j = 0
        while j < max(len(l1) , len(l2)):
            if l1[j] == l2[j]:
                c2 = c2 + 1
            t2 = t2 + 1
            j = j + 1
    except Exception, e:
        pass
    i = i +1

print str((c1*100.0)/t1)+"%" 
print str((c2*100.0)/t2)+"%"