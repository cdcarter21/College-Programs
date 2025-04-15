#------------------------------------------------------------------------------
# Developer---Cole Carter
# Course------CS1213-02
# Project-----Project #2
# Due---------October 1, 2021
#
# This program computes an itemized invoice for a load of scrap metal.
#------------------------------------------------------------------------------

type_metal = input("Type of metal (A or C)---- ")
weight = float(input("Weight of load (pounds)--- "))

if type_metal == "A":
    price_pound = 0.81
elif type_metal == "C":
    price_pound = 3.04

if weight >= 200:
    price_pound = price_pound + 0.25

total_price = weight * price_pound
cop_total_price = total_price - 5.00

print()
print("Your Itemized NashTrash Invoice")
print()
if type_metal == "A":
    print("Metal.............. Aluminum")
elif type_metal == "C":
    print("Metal.............. Copper")
print("Weight............. %.1f pounds"%weight)
print()
if weight >= 200:
    print("Price per pound.... $%7.2f (includes weight premium)"%price_pound)
else:
    print("Price per pound.... $%7.2f"%price_pound)
print("Total price........ $%7.2f"%total_price)
if type_metal == "C":
    print("Background check... $  (5.00)")
    print()
    print("Your payment....... $%7.2f"%cop_total_price)
else:
    print()
    print("Your payment....... $%7.2f"%total_price)
