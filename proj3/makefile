CC=gcc
CXXFLAGS=-std=c++11 -Wall -pedantic

.SUFFIXES: .x

.PHONY : clean

clean:
	rm -f stack1.x; rm -f in2post.x
  
stack1.x: stack.h test_stack1.cpp
	$(CXX) $(CXXFLAGS) -o $@ test_stack1.cpp
	
in2post.x: stack.h in2post.cpp
	$(CXX) $(CXXFLAGS) -o $@ in2post.cpp

%.x : %.c
	$(CC) -o $@ $<
%.x : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
