/**
 * ThreadExample.c++ - this application demonstrates how to define a
 * separate thread of execution using std::thread to run a member function.
 *
 * Must use -std=c++11 (or better!)
 */

#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <string>

std::random_device random_device;
std::mt19937 generator(random_device());
std::uniform_real_distribution<double> f(0.,1.);

const static int count = 20;

/**
 * This thread calculates 0! through 20!, where
 *  0! = 1
 *  n! = n * (n-1)!, n > 0
 */

class Factorial {
public:
    void run( const std::string& name ) {

	// 0! = 1
	long factorial = 1;
	std::cout << "0! = " << factorial << std::endl;
	for (int n = 1; n <= count; n++) {
	    // Sleep for between 0 and 2 seconds before calculating n!
	    std::this_thread::sleep_for( std::chrono::milliseconds( static_cast<long>(f(generator) * 2000 )) );
	    // n! = n * (n-1)!
	    factorial = n * factorial;
	    std::cout << n << "! = " << factorial << std::endl;
	}
	std::cout << name << "(" << std::this_thread::get_id() << ") finished" << std::endl;
    }
};


int main( int argc, char ** argv )
{
    std::cerr << "Creating factorial thread." << std::endl;
    Factorial compute;
    std::thread thread( &Factorial::run, &compute, "Factorial::run" );	// pass object by reference.
    std::cerr << "Created: " << thread.get_id() << std::endl;
    thread.join();
    std::cerr << "Factorial thread ended." << std::endl;
    return 0;
}
