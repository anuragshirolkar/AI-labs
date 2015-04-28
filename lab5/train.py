#!/usr/bin/python

import sys
import os.path
import json

GRAPHENE_TO_PHONEME = True

if len(sys.argv) < 2:
    print "Usage: python isolator.py <input-file>"
    sys.exit()
    pass

if len(sys.argv) ==3:
    if sys.argv[2] == "1":
        GRAPHENE_TO_PHONEME = False

filename = sys.argv[1]

if not os.path.isfile(filename) :
    print "Unable to open file"
    sys.exit()

f = open(filename)

transition_table = {"START":{}}
emission_table = {}

for line in f:
    part = line.strip().split('\t')
    if GRAPHENE_TO_PHONEME:
        obs = list(part[0])
        states = part[1].split(' ')
    else:
        obs = part[1].split(' ')
        states = list(part[0])

    l = len(states)
    i = 0
    while i < l:
        if not (states[i] in emission_table.keys()):
            emission_table[states[i]] = {}

        if not (obs[i] in emission_table[states[i]].keys()):
            emission_table[states[i]][obs[i]] = 1
        
        emission_table[states[i]][obs[i]] =  emission_table[states[i]][obs[i]] + 1
        i = i+1

    states.append("END")
    l = len(states)
    i = 0
    last = "START"
    while i < l:
        if not (last in transition_table.keys()):
            transition_table[last] = {}

        if not (states[i] in transition_table[last].keys()):
            transition_table[last][states[i]] = 1
        
        transition_table[last][states[i]] = transition_table[last][states[i]] + 1
        last = states[i]
        i = i+1



for state, table in emission_table.iteritems():
    tot = 0.0
    for key , value in table.iteritems():
        tot = tot + value

    for key , value in table.iteritems():
        emission_table[state][key] = value/tot
        

for state, table in transition_table.iteritems():
    tot = 0.0
    for key , value in table.iteritems():
        tot = tot + value

    for key , value in table.iteritems():
        transition_table[state][key] = value/tot

print json.dumps(transition_table)
print json.dumps(emission_table)



