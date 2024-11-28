CXX = clang++ -std=c++11 -Wall
CC  = $(CXX)

DSTS = SimpleEchoClient SimpleEchoServer

all: $(DSTS)

clean:
	rm $(DSTS)

SimpleEchoClient:	SimpleEchoClient.o
SimpleEchoServer:	SimpleEchoServer.o

SimpleEchoClient.o:	 SimpleEchoClient.cpp Datagram.h
SimpleEchoServer.o:	 SimpleEchoServer.cpp Datagram.h
