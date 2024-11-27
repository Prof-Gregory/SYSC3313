// SimpleEchoClient.java
// This class is the client side for a simple echo server based on
// UDP/IP. The client sends a character string to the echo server, then waits 
// for the server to send it back to the client.
// Last edited January 9th, 2016

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h> 
#include "Datagram.h"

#define PORT    5000
   
class SimpleEchoClient {
public:
    SimpleEchoClient() : sendReceiveSocket() {}
    
private:
    DatagramSocket sendReceiveSocket;

public:
    void sendAndReceive() {

	// Prepare a DatagramPacket and send it via sendReceiveSocket
	// to port 5000 on the destination host.
 
	const std::string s = "Anyone there?";
	std::cout << "Client: sending a packet containing: " << s << std::endl;

	// Construct a datagram packet that is to be sent to a specified port 
	// on a specified host.
	// The arguments are:
	//  msg - the message contained in the packet (the byte array)
	//  msg.length - the length of the byte array
	//  InetAddress.getLocalHost() - the Internet address of the 
	//     destination host.
	//     In this example, we want the destination to be the same as
	//     the source (i.e., we want to run the client and server on the
	//     same computer). InetAddress.getLocalHost() returns the Internet
	//     address of the local host.
	//  5000 - the destination port number on the destination host.
	std::vector<uint8_t> out( s.begin(), s.end() );
	DatagramPacket sendPacket( out, out.size(), InetAddress::getLocalHost(), PORT );

	std::cout << "Client: Sending packet:" << std::endl;
	std::cout << "To host: " << sendPacket.getAddress() << std::endl;
	std::cout << "Destination host port: " << sendPacket.getPort() << std::endl;
	int len = sendPacket.getLength();
	std::cout << "Length: " << len << std::endl;
	std::cout << "Containing: " 
		  << std::string(static_cast<const char *>(sendPacket.getData()), sendPacket.getLength()) // or could print "s"
		  << std::endl;

	// Send the datagram packet to the server via the send/receive socket. 

	try {
	    sendReceiveSocket.send(sendPacket);
	} catch (const std::runtime_error& e) {
	    std::cerr << e.what();
	    exit(1);
	}

	std::cout << "Client: Packet sent." << std::endl;

	// Construct a DatagramPacket for receiving packets up 
	// to 100 bytes long (the length of the byte array).

	std::vector<uint8_t> in(100);
	DatagramPacket receivePacket(in, in.size());

	try {
	    // Block until a datagram is received via sendReceiveSocket.  
	    sendReceiveSocket.receive(receivePacket);
	} catch(const std::runtime_error& e) {
	    std::cerr << e.what();
	    exit(1);
	}

	// Process the received datagram.
	std::cout << "Client: Packet received:" << std::endl;
	std::cout << "From host: " << receivePacket.getAddress() << std::endl;
	std::cout << "Host port: " << receivePacket.getPort() << std::endl;
	len = receivePacket.getLength();
	std::cout << "Length: " << len << std::endl;
	std::cout << "Containing: ";

	// Form a String from the byte array.
	std::cout << std::string( static_cast<const char *>(receivePacket.getData()), receivePacket.getLength() ) << std::endl;
	//Socket will close with RAII.
	return;
    }
};

int main(int argc, char ** argv)
{
    SimpleEchoClient().sendAndReceive();
}

