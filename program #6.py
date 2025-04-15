#------------------------------------------------------------------------------
# Developer---Cole Carter
# Course------CS1213-02
# Project-----Project #6
# Due---------December 1, 2021
#
# This program converts English words to Herd Latin, in which an English word is
# interleaved with the letters of the word "purple", starting with the first
# letter of English, then alternating between the letters of "purple" and the
# letters of English, and finally ending with "gold" following the last letter
# of the English word. 
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# English to Herd Latin conversion
#
# This function takes the user's entry of an English word and converts it to
# Herd Latin.
#------------------------------------------------------------------------------

def herd_conversion(english):
    purple = "purplepurplepurplepurplepurplepurplepurplepurplepurplepurple"
    length = len(english)
    total = ""
    n = 0
    while n < (length - 1):
        conversion = english[n] + purple[n]
        total += conversion
        n += 1
    total += english[length-1] + "gold"
    return total

#------------------------------------------------------------------------------
# main program
#------------------------------------------------------------------------------
entry = input("English ----- ")
while entry != "":
    herd_latin = herd_conversion(entry)
    print("Herd Latin -- %s"%herd_latin)
    print()
    entry = input("English ----- ")
    
