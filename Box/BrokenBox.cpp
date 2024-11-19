/**
 * The basic Box class to show mutual exclusion and 
 * condition synchronization.
 * 
 * @author Lynn Marshall, Greg Franks
 * @version 1.00
 */

#include <chrono>
#include <thread>
#include <iostream>

template <typename Type> class Box
{
private:
    Type contents;
    bool empty;
    
public:
    Box() : contents(Type()), empty(true) {}	// Constructor

/**
 * Stores its argument in the Box if
 * the Box is empty; otherwise, the
 * Box contents are not changed.
 *
 * @param obj the object that is to be
 *        stored in this Box.
 * @return true if obj was stored in this
 *         Box; false if another object
 *         was already stored in the Box
 *         (in which case, this Box was
 *         not changed by invoking this
 *         method).
 */
    bool put( Type item ) {
        if ( !empty ) return false;

        contents = item;
        empty = false;
        return true;
    }

/**
 * Removes the object stored in this
 * Box, leaving the Box empty.
 *
 * @return the object stored in this Box,
 *         if there is one.  
 *         If the Box is empty,
 *         returns null.
 */
    Type get() {
        Type item = contents;
        empty = true;
        contents = Type();
        return item;
    }
};

const int count = 10;

template <typename Type> class Producer
{
private:
    std::string name;
    Box<Type>& box;

public:
    Producer( Box<Type>& a_box ) : name(), box(a_box) {}
    
    void operator()( const std::string& name ) {
        for(int i = 0; i < 10; i++) {
	    std::cout << name << "(" << std::this_thread::get_id() << ") produced " << i << std::endl;
	    box.put( i );
	    std::cout << name << "(" << std::this_thread::get_id() << ") put in box " << i << std::endl;
	    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
	}
    }
};

template <typename Type> class Consumer
{
private:
    std::string name;
    Box<Type>& box;

public:
    Consumer( Box<Type>& a_box ) : name(), box(a_box) {}
    void operator()( const std::string& name ) {
        for(int i = 0; i < 10; i++) {
	    std::cout << name << "(" << std::this_thread::get_id() << ") ready to consume " << i << std::endl;
	    Type item = box.get();
	    std::cout << name << "(" << std::this_thread::get_id() << ") consumed " << item << std::endl;
	    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
	}
    }
};

int main( int argc, char ** argv )
{
    Box<int> box;
    Producer<int> producer( box );
    Consumer<int> consumer( box );
    
    std::thread producer_thread( producer, "producer" );	// Pass by value.
    std::thread consumer_thread( consumer, "consumer" );	// Pass by value.
    producer_thread.join();
    consumer_thread.join();
    return 0;
}

