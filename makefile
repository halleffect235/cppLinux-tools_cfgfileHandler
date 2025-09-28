##
#
# Makefile for cfgfileHandler c++ object module
# 
# Written and Maintained by :
#  JP Langan
#  13186 15th Sreet S. 
#  Afton, MN 55001
#  www.dyn-eng.com
#  (651)206-5955
#
#
# 2025-09-15 - jpl; Initial file created to build a test routine and link to libraries
#						Code tested and deeemed operational for beta release on GitHub
#
# 2025-09-27 - jpl; Added flags for warnings and unused variables to assist in final code cleanup
#
#
all: test_cfgfileHandler cfgfileHandler.o test_cfgfileHandler.o

CXX = g++
CFLAGS = -c -Wall -Wunused 


cfgfileHandler.o 	: cfgfileHandler.cpp cfgfileHandler.h
		 	   $(CXX) $(CFLAGS) cfgfileHandler.cpp 

test_cfgfileHandler.o	: test_cfgfileHandler.cpp cfgfileHandler.h
			   $(CXX) $(CFLAGS) test_cfgfileHandler.cpp

test_cfgfileHandler 	: test_cfgfileHandler.o cfgfileHandler.o
			   $(CXX)  -o test_cfgfileHandler test_cfgfileHandler.o   cfgfileHandler.o -Wl,-Map=test_cfgfile.map
