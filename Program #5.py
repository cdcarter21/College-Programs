#------------------------------------------------------------------------------
# Developer---Cole Carter
# Course------CS1213-02
# Project-----Project #5
# Due---------November 8, 2021
#
# This program simulates firing a 19th century cannon by having the user choose
# the distance of the target, the amount of gunpowder, and the angle of barrel
# elevation for each shot. The target is hit when the cannonball lands within
# 20 feet of the target. 
#------------------------------------------------------------------------------

from math import pi, sin

#------------------------------------------------------------------------------
# distance
#
# This function computes the distance a cannonball travels using the amount of
# gunpowder and the angle of elevation. 
#------------------------------------------------------------------------------

def shot_distance(powder, angle_degrees):
    angle_degrees = (angle_degrees * (pi/180)) * 2
    sine = sin(angle_degrees)
    velocity = (powder * 594) ** 2
    numerator = velocity * sine
    distance = numerator / 32.2
    distance = round(distance, 0)
    return distance

#-------------------------------------------------------------------------------
# Main program
#-------------------------------------------------------------------------------

target_distance = int(input("Target distance (feet) ------- "))
lower_bound = target_distance - 20
upper_bound = target_distance + 20
sentinel = 1

while sentinel != 0:
    print()
    charge = float(input("Powder charge (pounds) ------- "))
    elevation = float(input("Barrel elevation (degrees) --- "))
    print()

    distance = shot_distance(charge, elevation)
    

    if distance > upper_bound:
        distance = distance - target_distance
        print("Result of shot --------------- %d feet too long"%distance)

    elif distance < lower_bound:
        distance = target_distance - distance
        print("Result of shot --------------- %d feet too short"%distance)

    else:
        print("Result of shot --------------- HIT!!")
        sentinel = 0

