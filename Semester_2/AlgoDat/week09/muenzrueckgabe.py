# set variables
x = 1
y = 10

S = [1, 5, 10]

# set left border
difference = y - x 

solution_array = [] # declare emptyarray

# create loop until left is equal to 0
while difference != 0:

    # set take and boolean
    take = 0
    found = False 

    # loop through the S array
    for element in S[::-1]:

        # if we find an element that matches then set boolean to true 
        # and take the element and break out of the loop because element is found
        if element <= difference:
            found = True 
            take = element
            break 
    
    # if element is not found then exit with -1
    if not found:
        exit(-1)

    difference -= take

    solution_array.append(take)

print(solution_array)
