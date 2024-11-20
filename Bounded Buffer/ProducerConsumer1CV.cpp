/** ProducerConsumer.cpp
 *
 * This is a C++ implementation of the classic producer/consumer/bounded buffer 
 * program.
 * 
 * @author D.L. Bailey, 
 * Systems and Computer Engineering,
 * Carleton University
 * @version 1.3, January 23, 2002
 */

#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <deque>
#include <mutex>
#include <condition_variable>

template <typename Type> class BoundedBuffer
{
private:
    const size_t size = 5;
    std::deque<Type> contents;
    bool empty = true;
    std::mutex mtx;
    std::condition_variable add_wait;
    std::condition_variable remove_wait;
public:
    BoundedBuffer() : contents(), empty(true), mtx(), add_wait(), remove_wait() {}	// Constructor

    void addLast( Type item ) {
	std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
	while ( !writeable() ) add_wait.wait(lock);
	contents.emplace_back(item);
	empty = false;
	remove_wait.notify_one();
    }

    Type removeFirst() {
	std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
	while ( !readable() ) remove_wait.wait(lock);
	Type item = contents.front();
	contents.pop_front();
	add_wait.notify_one();
	return item;
    }

private:
    bool writeable() const {
	return contents.size() < size;
    }

    bool readable() const {
	return !contents.empty();
    }
};

const int count = 10;

template <typename Type> class Producer
{
private:
    std::string name;
    BoundedBuffer<Type>& buffer;

public:
    Producer( BoundedBuffer<Type>& a_buffer ) : name(), buffer(a_buffer) {}
    
    void operator()( const std::string& name ) {
        for(int i = 0; i < 10; i++) {
	    std::cout << name << "(" << std::this_thread::get_id() << ") produced " << i << std::endl;
	    buffer.addLast( i );
	    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
	}
    }
};

template <typename Type> class Consumer
{
private:
    std::string name;
    BoundedBuffer<Type>& buffer;

public:
    Consumer( BoundedBuffer<Type>& a_buffer ) : name(), buffer(a_buffer) {}
    void operator()( const std::string& name ) {
        for(int i = 0; i < 10; i++) {
	    Type item = buffer.removeFirst();
	    std::cout << name << "(" << std::this_thread::get_id() << ") consumed " << item << std::endl;
	    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
	}
    }
};

int main( int argc, char ** argv )
{
    BoundedBuffer<int> buffer;
    Producer<int> producer( buffer );
    Consumer<int> consumer( buffer );
    
    std::thread producer_thread( producer, "Producer" );
    std::thread consumer_thread( consumer, "Consumer" );
    producer_thread.join();
    consumer_thread.join();
    return 0;
}

