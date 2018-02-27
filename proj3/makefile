CC=gcc
CXXFLAGS=-std=c++11 -Wall -pedantic

.SUFFIXES: .x

.PHONY : clean

clean:
	rm -f proj3.x
  
proj2.x: stack.h test_stack1.cpp
	$(CXX) $(CXXFLAGS) -o $@ test_stack1.cpp

%.x : %.c
	$(CC) -o $@ $<
%.x : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
