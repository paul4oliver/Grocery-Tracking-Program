import re
import string
import collections
import os

# All functions currently accesing test "Test_List.txt" for file input.

# Function opens text-based input file, reads each line, copies contents,
# and creates text file frequency.dat with the name of each item on input file once and
# a numerical value to represnt its frequency. No return value.
def WriteFile():
    complete_list = [] # This list holds all items on input file
    single_list = [] # This list holds only each item on list once
    inputFile = open("Test_List.txt", "r") 
    f = open("frequency.dat.txt", "w")
    contents = inputFile.readlines()
    for line in contents:
        line = line.replace("\n", "") # Remove "\n" from item name
        complete_list.append(line) # Add item to list
        if line not in single_list: # If item is not in the single list, add it (only once)
            single_list.append(line)

    for item in single_list: # Write item name and count to frequency.dat 
        f.write(item)
        f.write(" ")
        f.write(str(complete_list.count(item)))
        f.write("\n")
    inputFile.close() #Close both files
    f.close()

# Function opens input file and counts frequency of specific item that is passed as string parameter
# Function returns count of item.
def SpecificFrequency(v):
    complete_list = [] # List is used to hold all items on input file
    inputFile = open("Test_List.txt")
    contents = inputFile.readlines()
    for line in contents:
        line = line.replace("\n", "")
        complete_list.append(line)

    inputFile.close() # Close file
    return complete_list.count(v) # Returns how many times specific item is in complete_list

# Function displays a complete list of each item on input file and numerical value of how many
# times it is on the list. Relfects how many times item was purchased. 
def TotalFrequency():
    complete_list = [] # List holds all items on input file
    single_list = [] # List holds each item on list, once.
    inputFile = open("Test_List.txt", "r")
    contents = inputFile.readlines()
    for line in contents:
        line = line.replace("\n", "") # Remove "\n" from item name
        complete_list.append(line) # Add item to list
        if line not in single_list: # If item is not in the single list, add it (only once)
            single_list.append(line)
    
    for item in single_list: # Print each item on single_list and the count of item on complete_list
        print(item, complete_list.count(item))
    inputFile.close() # Close file