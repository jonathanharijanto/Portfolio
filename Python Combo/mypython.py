# CS 344 program 5 created by Jonathan Harijanto
# Credits to stackoverflow and codecademy
# The objective from this assignment is to give a feel about new programming language to student
# with no help either from TA or instructor.
# Reason: Student must able to learn how to handle any language thrown at him/her

# This program will create 3 different files in the same directory as this script. It will then
# be appended with 10 random lowercase character no space like (werufkcngp). Then it must also display
# to the screen (the random characters in each file). After that, this script must generate &display 2 
# random number with range 1 to 42 (inclusive). Finally, print out the product of these number too.  

# Import modules
import string 
import random
import os
import errno
import sys

# Function that will loop 3 times, in each loop it will create a file in order (file_1, file_2, etc). 
# Then it will generate random characters for range of 10 (means 10 characters).
# It will then close the file, reopen it but for read only! Read what's inside the file. Then close it again.   
def generateFiles():
	for i in range(3):
		# open the file, if not exist then create new one
		file = open("file_" + str(i+1) + ".txt", "w+")
		# variable that contain 10 random characters
		randomChar = ''.join(random.choice(string.ascii_lowercase)for _ in range (10))
		# write or 'append' to the newly create file	
		file.write(randomChar)
		file.close()
		print
		print "Content of the file_%d is: " % (i+1)
		# reopen it again
		file = open("file_" + str(i+1) + ".txt", "r")
		# read the one entire line from the file 
		print file.readline()
		file.close()
	print("\n3 files created and printed successfully! \n")

# Function that will generate 2 different random numbers with range from 1 to 42. Print both then
# do multiplication and display it
def randomNumb():
	# generate two random number in variable a and b. Randint endpoint is inclusive, so no need
	# n+1 for the endpoint.
	a = random.randint(1,42)
	b = random.randint(1,42)
	print ("First random integer is: %d\n" % a)
	print ("Second random integer is: %d\n" % b)
	print ("The product of the two numbers is: %d\n" % (a*b))

# Call both functions
generateFiles()

randomNumb()	
