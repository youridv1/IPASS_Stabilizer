#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := MPU6050.cpp steppermotor.cpp stepper28BYJ48.cpp
# header files in this project
HEADERS := MPU6050.hpp steppermotor.hpp stepper28BYJ48.hpp

# other places to look for files for this project
SEARCH  := ../lib 

# set RELATIVE to the next higher directory 
# and defer to the Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
