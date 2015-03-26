#!/usr/bin/python

import sys
import os.path
import json

if len(sys.argv) < 2:
    filename = 'data/tables.txt'
else:
    filename = sys.argv[1]

if not os.path.isfile(filename) :
    print "Unable to open file"
    sys.exit()

f = open(filename)
transition_table = json.loads(f.readline().strip())
emission_table = json.loads(f.readline().strip())

inp =raw_input()
inp = inp.upper().split(" ")
for s in inp:
    final_word=s
    
    if s=="":
        continue

    class ViterbiNode(object):
        """docstring for ViterbiNode"""
        def __init__(self):
            self.parent = None
            self.state = None
            self.prob = 1
            
    states = {"AA":0,"AE":0,"AH":0,"AO":0,"AW":0,"AY":0,"B":0,"CH":0,"D":0,"DH":0,"EH":0,"ER":0,"EY":0,"F":0,"G":0,"HH":0,"IH":0,"IY":0,"JH":0,"K":0,"L":0,"M":0,"N":0,"NG":0,"OW":0,"OY":0,"P":0,"R":0,"S":0,"SH":0,"T":0,"TH":0,"UH":0,"UW":0,"V":0,"W":0,"Y":0,"Z":0,"ZH":0,"SIL":0}

    # Root Node
    root = ViterbiNode()
    root.state = "START"

    s = list(s)

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

    print final_word + "\t" + " ".join(l)
