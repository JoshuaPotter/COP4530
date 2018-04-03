CC=gcc
CXXFLAGS=-std=c++11 -Wall -pedantic

.SUFFIXES: .x

.PHONY : clean

clean:
	rm -f bet.x
  
bet.x: bet.h proj4_driver.cpp
	$(CXX) $(CXXFLAGS) -o $@ proj4_driver.cpp

%.x : %.c
	$(CC) -o $@ $<
%.x : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
