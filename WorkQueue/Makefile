CXX = g++
# Clang
#CXXFLAGS += -std=c++20 -stdlib=libc++ -fexperimental-library
# Gcc
CXXFLAGS += -std=c++20


DSTS = WorkQueue StoppableWorkQueue

all: $(DSTS)

clean:
	rm $(DSTS)

WorkQueue:	WorkQueue.cpp
StoppableWorkQueue: StoppableWorkQueue.cpp
