 
all: test_cfgfileHandler cfgfileHandler.o test_cfgfileHandler.o

CXX = g++
CFLAGS = -c -Wall -Wunused 


cfgfileHandler.o 	: cfgfileHandler.cpp cfgfileHandler.h
		 	   $(CXX) $(CFLAGS) cfgfileHandler.cpp 

test_cfgfileHandler.o	: test_cfgfileHandler.cpp cfgfileHandler.h
			   $(CXX) $(CFLAGS) test_cfgfileHandler.cpp

test_cfgfileHandler 	: test_cfgfileHandler.o cfgfileHandler.o
			   $(CXX)  -o test_cfgfileHandler test_cfgfileHandler.o   cfgfileHandler.o -Wl,-Map=test_cfgfile.map
