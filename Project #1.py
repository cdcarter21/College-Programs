#------------------------------------------------------------------------------
# Developer---Cole Carter
# Course------CS1213-02
# Project-----Project #1
# Due---------September 22, 2021
#
# This program computes an itemized receipt for a campsite at a state park.
#------------------------------------------------------------------------------

nightly_rate = float(input("Nightly rate-------- "))
number_nights = int(input("Number of nights---- "))
number_campers = int(input("Number of campers--- "))

campsite_cost = (nightly_rate * number_nights)
electricity_cost = 10.00
tax = (campsite_cost*0.07) + (electricity_cost*0.07)
tip = (campsite_cost + electricity_cost + tax) * 0.15
total = campsite_cost + electricity_cost + tax + tip
camper_cost = (total / number_campers)

print()
print("Campsite------------ $%6.2f"%campsite_cost)
print("Electricity--------- $%6.2f"%electricity_cost)
print("Tax----------------- $%6.2f"%tax)
print("Ranger-------------- $%6.2f"%tip)
print("Total--------------- $%6.2f"%total)
print()
print("Cost per camper----- $%6.2f"%camper_cost)



