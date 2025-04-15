#------------------------------------------------------------------------------
# Developer---Cole Carter
# Course------CS1213-02
# Project-----Project #4
# Due---------October 29, 2021
#
# This program approximates the value of sin(x), where x is an angle given in 
# radians, with the Taylor series. 
#------------------------------------------------------------------------------

again = "yes"

while again == "yes":
    angle = float(input("Angle -------- "))
    total = 0
    n = 1

    for count in range(1, 21):
        numerator = angle ** n
        denominator = 1
        
        for item in range(1, n+1):
            denominator = denominator * item
        
        term = numerator / denominator

        if (count % 2) == 0:
            total = total - term
        else:
            total = total + term
            
        n = n + 2
        
    print("sin(angle) --- %.5f"%total)
    print()
    again = input("Again? ------- ")
    print()
