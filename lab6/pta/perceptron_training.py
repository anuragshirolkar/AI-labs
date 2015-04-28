n = int(input())
inputs = []
outputs = []
for i in range(n) :
    inp = raw_input().split()
    out = int(inp[-1])
    inp = [int(x) for x in inp[:-1]]
    inp.append(-11)
    inputs.append(inp)
    outputs.append(out)


def is_valid(inp, out, weights) :
    tot = 0
    for i in range(len(inp)) :
        tot += inp[i] * weights[i]
    print inp, out, tot
    if tot > 0 and out == 1:
        return True
    elif tot > 0:
        return False
    elif out == 1:
        return False
    else :
        return True

def iterate(weights) :
    ind = -1
    for i in range(len(inputs)):
        if not is_valid(inputs[i], outputs[i], weights) :
            weights = [weights[j] + inputs[i][j] for j in range(len(weights))]
            ind = i
    return ind, weights

ind1 = -1
count = 0
weights = [0]*len(inputs[0])

while True:
    print weights
    ind, weights = iterate(weights)
    if ind == -1:
        print ind1
    else :
        ind1 = count*len(inputs) + ind
    count += 1
        
        
    
