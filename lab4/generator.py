import random, string

def randomvariable():
   return ''.join(random.choice(string.lowercase) for i in range(5))
   
list_gates = {}
num_inputs = int(input("Enter number of inputs: "))
gates = raw_input("Enter list of Gates: ")
gates = gates.split()

symbol_table = {}

for gate in gates :
    if gate in list_gates:
        list_gates[gate] += 1
    else :
        list_gates[gate] = 1
gates = []
for gate in list_gates:
    for i in range(list_gates[gate]):
        gates.append(gate+str(i))

signals = []
for i in range(num_inputs) :
    signals.append('w'+str(i))

input_signals = signals

count_signals = num_inputs
inputs = {}
outputs = {}
for gate in gates:
    if gate[:3] == "not":
        w0 = 'w' + str(count_signals)
        w1 = 'w' + str(count_signals+1)
        signals.append(w0)
        signals.append(w1)
        count_signals+=2
        inputs[gate] = [w0]
        outputs[gate] = w1
    elif gate[:3] == "and" or gate[:2] == "or" or gate[:3] == 'xor':
        w0 = 'w' + str(count_signals)
        w1 = 'w' + str(count_signals+1)
        w2 = 'w' + str(count_signals+2)
        signals.append(w0)
        signals.append(w1)
        signals.append(w2)
        count_signals+=3
        inputs[gate] = [w0,w1]
        outputs[gate] = w2
    print gate
    print "inputs: ",
    for i in inputs[gate]:
        print i,
    print
    print "output: ",outputs[gate]
    print

for signal in signals:
    symbol_table[signal] = randomvariable()

for gate in gates:
    symbol_table[gate] = randomvariable()

connected_code = "\n%% Connected Code\n:- multifile connected/2.\n"
print "Enter connections:"
while True:
    a = raw_input()
    if a == "done":
        break
    w0, w1 = a.split()
    connected_code += "connected("+symbol_table[w0]+","+symbol_table[w1]+").\n"
connected_code += "\n\n"

output_signal = raw_input("Enter name of output signal: ")

signal_code = "\n%% Signal Code\n:- multifile signal/1.\n"
for signal in signals:
    signal_code += "signal("+symbol_table[signal]+").\n"
signal_code += "\n\n"

type_code = "\n%% Type Code\n:- multifile type/2.\n"
for gate in gates:
    if gate[:3] == 'and' or gate[:3] == 'not' or gate[:3] == 'xor':
        tp = gate[:3]
    elif gate[:2] == 'or':
        tp = gate[:2]
    type_code += "type("+symbol_table[gate]+","+tp+").\n"
type_code += "\n\n"

in_code = "\n%% In Code\n:- multifile in/3.\n"
for gate in gates:
    for i in range(len(inputs[gate])):
        print gate, inputs[gate][i]
        in_code += "in("+str(i)+","+symbol_table[gate]+","+symbol_table[inputs[gate][i]]+").\n"
in_code += "\n\n"

out_code = "\n%% Out Code\n:- multifile out/2.\n"
for gate in gates:
    out_code += "out("+symbol_table[gate]+","+symbol_table[outputs[gate]]+").\n"
out_code += "\n\n"

function_name = raw_input("Enter new Function name: ")

output_predicate = "\n%% output predicate\n"
output_predicate += function_name+"("+','.join([x.upper() for x in input_signals[:num_inputs]])+","+output_signal.upper()+") :- "+','.join(["valid("+x.upper()+"), asserta(value("+symbol_table[x]+","+x.upper()+"))" for x in input_signals[:num_inputs]])+",value("+symbol_table[output_signal]+","+output_signal.upper()+")."

f = open(function_name+'.pl', 'w')


#print >>f, ":- module("+function_name+",["+function_name+"/"+str(num_inputs+1)+"])."
print >>f, type_code, signal_code, in_code, out_code, connected_code, output_predicate


   

    

