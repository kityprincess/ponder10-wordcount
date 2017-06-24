###############################################################
# Program:
#     Week 10, Map
#     Brother JonesL, CS235
# Author:
#     Kimberly Stowe - 5 hours
#     Matt Burr -      5 hours
#     Shayla Nelson -  6 hours
#     Bryan Lopez -    5 hours
# Summary:
#     Creates a binary tree and balances it using the red/black
#     algorithm. 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week10.o wordCount.o
	g++ -o a.out week10.o wordCount.o 
	tar -cf week10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week10.o       : the driver program
#      wordCount.o    : the wordCount() function
##############################################################
week10.o: bnode.h bst.h pair.h map.h wordCount.h week10.cpp
	g++ -c week10.cpp

wordCount.o: map.h wordCount.h wordCount.cpp bnode.h bst.h pair.h
	g++ -c wordCount.cpp 
