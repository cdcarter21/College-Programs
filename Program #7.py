#--------------------------------------------------------------------------------
# Developer---Cole Carter
# Course------CS1213-02
# Project-----Project #7
# Due---------December 8, 2021
#
# This program computes grades for students in a college class by taking a
# student's exam scores from a text file and computing their weighted semester
# average and letter grade. 
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# semester_average
#
# This function takes the exam scores from a line of the text file and computes
# the weighted semester average for that specific student. 
#--------------------------------------------------------------------------------

def semester_average(list):
    sum = (float(list[2]) * .25) + (float(list[3]) * .35) + (float(list[4]) * .4)
    return sum

#--------------------------------------------------------------------------------
# letter_grade
#
# This function takes the previously computed semester average for a student
# and checks for which lettter grade the average falls under. 
#--------------------------------------------------------------------------------

def letter_grade(semester):
    if semester >= 90:
        return "A"
    elif semester >= 80:
        return "B"
    elif semester >= 70:
        return "C"
    elif semester >= 60:
        return"D"
    else:
        return "F"

#--------------------------------------------------------------------------------
# Main program
#--------------------------------------------------------------------------------

def main():
    file_name = input("Enter name of text file: ")
    file = open(file_name, "r")
    print()
    print("Student       Average Grade")
    print("------------  ------- -----")
    class_average = 0
    count = 0
    for line in file:
        datalist = line.split(",")
        lastname = str(datalist[0])
        average = semester_average(datalist)
        grade = letter_grade(average)
        class_average += average
        count += 1
        print("%-12s     %4.1f     %s"%(lastname, average, grade))
    class_average = class_average / count
    class_grade = letter_grade(class_average)
    print()
    print("Class            %4.1f     %s"%(class_average, class_grade))
    file.close()
    
#--------------------------------------------------------------------------------
# Execution begins here.
#--------------------------------------------------------------------------------

main()
