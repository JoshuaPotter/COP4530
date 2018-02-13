CC=gcc
CXXFLAGS=-std=c++11 -Wall -pedantic

.SUFFIXES: .x

.PHONY : clean

clean:
	rm -f proj2.x
  
proj2.x: List.h test_list.cpp
	$(CXX) $(CXXFLAGS) -o $@ test_list.cpp

%.x : %.c
	$(CC) -o $@ $<
%.x : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
