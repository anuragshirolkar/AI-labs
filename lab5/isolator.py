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

for l in f:
    l1 = l.strip().split('\t')

    if '(' in list(l1[0]):
        continue
        
    if len(l1) !=2:
        continue
    
    if len(l1[0]) == len(l1[1].split(' ')):
        print l.strip()