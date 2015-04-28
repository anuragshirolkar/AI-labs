learning_speed = 0.1
weights = [0, 0, 0]
training_set = []

n = int(input())
for i in range(n) :
    inp = raw_input().split()
    inp = [int(x) for x in inp]
    inp = (inp[:-1]+[1], inp[-1])
    training_set.append(inp)
 
def dot_product(values, weights):
    return sum(value * weight for value, weight in zip(values, weights))
 
while True:
    error_count = 0
    for input_vector, desired_output in training_set:
        result = dot_product(input_vector, weights) > 0
        error = desired_output - result
        if error != 0:
            error_count += 1
            for index, value in enumerate(input_vector):
                weights[index] += error * value
            print(weights)
    if error_count == 0:
        break
