CC=gcc
CXXFLAGS=-std=c++11 -Wall -pedantic

.SUFFIXES: .x

.PHONY : clean

clean:
	rm -f hashtable.x
  
hashtable.x: hashtable.h test_hashtable.cpp
	$(CXX) $(CXXFLAGS) -o $@ test_hashtable.cpp

%.x : %.c
	$(CC) -o $@ $<
%.x : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
