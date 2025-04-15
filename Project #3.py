#------------------------------------------------------------------------------
# Developer---Cole Carter
# Course------CS1213-02
# Project-----Project #3
# Due---------October 20, 2021
#
# This program tests the Collatz conjecture problem.
#------------------------------------------------------------------------------
entry = int(input("First term ------- "))
while entry > 0:
    largest = entry
    count = 1
    while entry > 1: 
        if (entry % 2) == 0:
            entry //= 2
        elif (entry % 2) != 0:
            entry = (entry * 3) + 1
        if entry > largest:
            largest = entry
        count += 1
    print("Number of terms --", count)
    print("Largest term -----", largest)
    print()
    entry = int(input("First term ------- "))
