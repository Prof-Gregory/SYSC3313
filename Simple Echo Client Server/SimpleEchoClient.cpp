// SimpleEchoClient.java
// This class is the client side for a simple echo server based on
// UDP/IP. The client sends a character string to the echo server, then waits 
// for the server to send it back to the client.
// Last edited January 9th, 2016

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
   
#define PORT     8080 
#define MAXLINE 1024 
   
class InetAddress
{
public:
    static in_addr_t getLocalHost() { return inet_addr( "127.0.0.1" ); }
};


class DatagramPacket {
public:
    DatagramPacket() : _data() {
	memset(&_address, 0, sizeof(_address)); 
       
	_address.sin_family = AF_INET; 
	_address.sin_port = htons(0); 
	_address.sin_addr.s_addr = INADDR_ANY;		/* Bind to all local interfaces */
    }
    DatagramPacket( const std::vector<uint8_t>& data, size_t length, in_addr_t address=INADDR_ANY, in_port_t port=0 ) : _data(data) {
	_address.sin_family = AF_INET; 
	_address.sin_port = htons(port); 
	_address.sin_addr.s_addr = address;
	_length = std::min( data.size(), length );	// Take smaller value.
    }

    void * getData() const { return const_cast<void *>(static_cast<const void *>(_data.data())); }
    size_t getLength() const { return _length; }
    void setLength( size_t length ) { _length = std::min( length, _data.size() ); }
    in_addr_t getAddress() { return _address.sin_addr.s_addr; }
    in_port_t getPort() { return _address.sin_port; }

    struct sockaddr* address() { return reinterpret_cast<sockaddr*>(&_address); }
    std::vector<uint8_t>::const_iterator begin() const { return _data.begin(); }
    std::vector<uint8_t>::const_iterator end() const { return _data.end(); }

private:
    std::vector<uint8_t> _data;
    size_t _length;
    struct sockaddr_in _address;
};

// Creating socket file descriptor
class DatagramSocket {
public:
    DatagramSocket() : socket_fd(socket(AF_INET, SOCK_DGRAM, 0)) {
	if ( socket_fd < 0 ) {
	    throw std::runtime_error( "socket creation failed" );
	}
    }

    ~DatagramSocket() {
	close( socket_fd );
    }

    ssize_t send( DatagramPacket& packet ) {
	ssize_t sent = sendto( socket_fd, packet.getData(), packet.getLength(), 0, packet.address(), sizeof(*packet.address()) );
	if ( sent == -1 ) {
	    throw std::runtime_error( "send failure" );
	}
	return sent;
    }
    
    void receive( DatagramPacket& packet ) {
	socklen_t len = packet.getLength();
	int received = recvfrom(socket_fd, packet.getData(), MAXLINE, MSG_WAITALL, packet.address(), &len);
	if ( received < 0 ) {
	    throw std::runtime_error( "receive failure" );
	}
	packet.setLength(len);
    }
    
private:
    int socket_fd;
};


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

#if 0
	// Java stores characters as 16-bit Unicode values, but 
	// DatagramPackets store their messages as byte arrays.
	// Convert the String into bytes according to the platform's 
	// default character encoding, storing the result into a new 
	// byte array.

	byte msg[] = s.getBytes();
#endif

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
	DatagramPacket sendPacket( out, out.size(), InetAddress::getLocalHost(), 5000 );

	std::cout << "Client: Sending packet:" << std::endl;
	std::cout << "To host: " << sendPacket.getAddress() << std::endl;
	std::cout << "Destination host port: " << sendPacket.getPort() << std::endl;
	int len = sendPacket.getLength();
	std::cout << "Length: " << len << std::endl;
	std::cout << "Containing: ";
	std::cout << std::string(sendPacket.begin(), sendPacket.end()); // or could print "s"

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
	std::string received = std::string( receivePacket.begin(), receivePacket.end() );
	std::cout << received << std::endl;
	//Socket will close with RAII.
	return;
    }
};

int main(int argc, char ** argv)
{
    SimpleEchoClient().sendAndReceive();
}

