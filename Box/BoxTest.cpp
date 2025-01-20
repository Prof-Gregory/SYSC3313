/**
 * The basic Box class to show mutual exclusion and 
 * condition synchronization using Resource Acquisition
 * Is Initialization (RAII) idiom.
 * 
 * @author Lynn Marshall 
 * @version 1.00
 */

#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <mutex>
#include <condition_variable>
#include <cassert>

template <typename Type> class Box
{
private:
    Type contents;	// The "Type" stored in the box
    bool empty = true;	// The state of the box.
    std::mutex mtx;
    std::condition_variable cv;
public:
    Box() : contents(Type()), empty(true), mtx(), cv() {}	// Constructor

    void put( Type item ) {
	std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
	while ( !empty ) cv.wait(lock);
	contents = item;
	empty = false;
	cv.notify_all();
    }

    Type get() {
	std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
	while ( empty ) cv.wait(lock);
	Type item = contents;
	empty = true;
	cv.notify_all();
	return item;
    }

    bool is_empty() {
	std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
	return empty;
    }
};

int main( int argc, char ** argv )
{
    Box<std::string> box;

    assert( box.is_empty() );
    box.put( "Hello World\n" );
    assert( !box.is_empty() );
    std::string result = box.get();
    assert( box.is_empty() );
    std::cout << result;
    return 0;
}

