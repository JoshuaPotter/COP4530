CC=gcc
CXXFLAGS=-std=c++11 -lcrypt -Wall -pedantic

.SUFFIXES: .x

.PHONY : clean

clean:
	rm -f proj5.x proj5.o passserver.o
  
proj5.x: proj5.o passserver.o
	$(CXX) $(CXXFLAGS) -o $@ $^
