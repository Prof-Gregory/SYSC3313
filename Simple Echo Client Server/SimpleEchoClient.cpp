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
   
class DatagramPacket {
public:
    DatagramPacket() {
	memset(&_address, 0, sizeof(_address)); 
       
	// Filling server information 
	_address.sin_family = AF_INET; 
	_address.sin_port = htons(PORT); 
	_address.sin_addr.s_addr = INADDR_ANY; 
    }

    void * data() const { return const_cast<void *>(static_cast<const void *>(_data.data())); }
    size_t length() const { return _data.size(); }
    struct sockaddr* address() { return reinterpret_cast<struct sockaddr *>(&_address); }

private:
    std::string _data;
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
	ssize_t sent = sendto( socket_fd, packet.data(), packet.length(), 0, packet.address(), sizeof(*packet.address()) );
	if ( sent == -1 ) {
	    throw std::runtime_error( "send failure" );
	}
	return sent;
    }
    
    void receive( DatagramPacket& packet ) {
	socklen_t len = sizeof(*packet.address());  //len is value/result 
	int received = recvfrom(socket_fd, packet.data(), MAXLINE,  
				MSG_WAITALL, packet.address(), &len);
	if ( received < 0 ) {
	    throw std::runtime_error( "receive failure" );
	}
    }
    
private:
    int socket_fd;
};


class SimpleEchoClient {
public:
    SimpleEchoClient() : sendReceiveSocket() {}
    
    void sendAndReceive() {}
private:
    DatagramSocket sendReceiveSocket;
#if 0
   DatagramPacket sendPacket, receivePacket;
   DatagramSocket sendReceiveSocket;

   public SimpleEchoClient()
   {
      try {
         // Construct a datagram socket and bind it to any available 
         // port on the local host machine. This socket will be used to
         // send and receive UDP Datagram packets.
         sendReceiveSocket = new DatagramSocket();
      } catch (SocketException se) {   // Can't create the socket.
         se.printStackTrace();
         System.exit(1);
      }
   }

   public void sendAndReceive()
   {
      // Prepare a DatagramPacket and send it via sendReceiveSocket
      // to port 5000 on the destination host.
 
      String s = "Anyone there?";
      System.out.println("Client: sending a packet containing:\n" + s);

      // Java stores characters as 16-bit Unicode values, but 
      // DatagramPackets store their messages as byte arrays.
      // Convert the String into bytes according to the platform's 
      // default character encoding, storing the result into a new 
      // byte array.

      byte msg[] = s.getBytes();

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
      try {
         sendPacket = new DatagramPacket(msg, msg.length,
                                         InetAddress.getLocalHost(), 5000);
      } catch (UnknownHostException e) {
         e.printStackTrace();
         System.exit(1);
      }

      System.out.println("Client: Sending packet:");
      System.out.println("To host: " + sendPacket.getAddress());
      System.out.println("Destination host port: " + sendPacket.getPort());
      int len = sendPacket.getLength();
      System.out.println("Length: " + len);
      System.out.print("Containing: ");
      System.out.println(new String(sendPacket.getData(),0,len)); // or could print "s"

      // Send the datagram packet to the server via the send/receive socket. 

      try {
         sendReceiveSocket.send(sendPacket);
      } catch (IOException e) {
         e.printStackTrace();
         System.exit(1);
      }

      System.out.println("Client: Packet sent.\n");

      // Construct a DatagramPacket for receiving packets up 
      // to 100 bytes long (the length of the byte array).

      byte data[] = new byte[100];
      receivePacket = new DatagramPacket(data, data.length);

      try {
         // Block until a datagram is received via sendReceiveSocket.  
         sendReceiveSocket.receive(receivePacket);
      } catch(IOException e) {
         e.printStackTrace();
         System.exit(1);
      }

      // Process the received datagram.
      System.out.println("Client: Packet received:");
      System.out.println("From host: " + receivePacket.getAddress());
      System.out.println("Host port: " + receivePacket.getPort());
      len = receivePacket.getLength();
      System.out.println("Length: " + len);
      System.out.print("Containing: ");

      // Form a String from the byte array.
      String received = new String(data,0,len);   
      System.out.println(received);

      // We're finished, so close the socket.
      sendReceiveSocket.close();
#endif
};

int main(int argc, char ** argv)
{
    SimpleEchoClient().sendAndReceive();
}
