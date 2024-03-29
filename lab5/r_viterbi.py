#!/usr/bin/python

import sys
import os.path
import json


if len(sys.argv) < 2:
    filename = 'data/r_tables.txt'
else:
    filename = sys.argv[1]
if len(sys.argv) == 3:
    GRAPHENE_TO_PHONEME = False

if not os.path.isfile(filename) :
    print "Unable to open file"
    sys.exit()

f = open(filename)
transition_table = json.loads(f.readline().strip())
emission_table = json.loads(f.readline().strip())

class ViterbiNode(object):
    """docstring for ViterbiNode"""
    def __init__(self):
        self.parent = None
        self.state = None
        self.prob = 1

def tr_val(a,b):
    if not (a in transition_table.keys()):
        transition_table[a] = {}
    if not (b in transition_table[a].keys()):
        return 0

    return transition_table[a][b]

def em_val(a,b):
    if not (a in emission_table.keys()):
        emission_table[a] = {}
    if not (b in emission_table[a].keys()):
        return 0
    return emission_table[a][b]


inp =raw_input()
while inp!="exit":

    inp = inp.upper()
    
    states = {"'":0,"-":0,".":0,"2":0,"A":0,"B":0,"C":0,"D":0,"E":0,"F":0,"G":0,"H":0,"I":0,"J":0,"K":0,"L":0,"M":0,"N":0,"O":0,"P":0,"Q":0,"R":0,"S":0,"T":0,"U":0,"V":0,"W":0,"X":0,"Y":0,"Z":0}


    # Root Node
    root = ViterbiNode()
    root.state = "START"

    s = inp.split(' ')

    #Looping over all observation sequence
    for obv in s:  
        prevStates = {}
        for state, node in states.iteritems():
            if node != 0:
                temp = ViterbiNode()
                temp.parent = node.parent
                temp.state = node.state
                temp.prob = node.prob
            else:
                temp = 0
            prevStates[state] = temp

        count = 0

        for state, node in prevStates.iteritems():
            
            maxNode = ViterbiNode()
            maxNode.prob = 0
            mn1 = 0

            for stateTr, nodeTR in prevStates.iteritems():
                if node == 0:
                    Tnode = ViterbiNode()
                    Tnode.parent = root
                    Tnode.state = state
                    Tnode.prob = tr_val("START" , state) * em_val(state,obv)
                    maxNode = Tnode
                else :
                    tempNode = ViterbiNode()
                    tempNode.state = state
                    tempNode.prob = nodeTR.prob * tr_val(stateTr , state) * em_val(state,obv)
                    if tempNode.prob > maxNode.prob:
                        tempNode.parent = nodeTR
                        maxNode = tempNode
            
            if maxNode.prob == 0:
                count = count + 1
            states[state] = maxNode
        #print obv , count

    # modifying probablitites for endstate transmission
    for stateTr, nodeTR in states.iteritems():
       nodeTR.prob = nodeTR.prob * tr_val(stateTr , "END")

    maxNode = ViterbiNode()
    maxNode.prob = 0

    for stateTr, nodeTR in states.iteritems():
        if nodeTR.prob > maxNode.prob:
            maxNode = nodeTR

    l = []
    while maxNode.parent != None :
        l.append(maxNode.state)
        maxNode = maxNode.parent

    l.reverse()

    print "".join(l)+ "\t" + inp
    inp =raw_input()
