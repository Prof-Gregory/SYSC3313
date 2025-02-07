CXX = g++ -std=c++11 -Wall -g
CC  = $(CXX)

DSTS = SimpleEchoClient SimpleEchoServer
OBJS = SimpleEchoClient.o SimpleEchoServer.o
all: $(DSTS)

clean:
	rm $(DSTS) $(OBJS)

SimpleEchoClient:	SimpleEchoClient.o
SimpleEchoServer:	SimpleEchoServer.o

SimpleEchoClient.o:	 SimpleEchoClient.cpp Datagram.h
SimpleEchoServer.o:	 SimpleEchoServer.cpp Datagram.h
