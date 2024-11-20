/**
 * ThreadExample.c++ - this application demonstrates how to define a
 * separate thread of execution using std::thread to run a functor.
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
    void operator()( const std::string& name ) {

	// 0! = 1
	long factorial = 1;
	std::cout << name << ": 0! = " << factorial << std::endl;
	for (int n = 1; n <= count; n++) {
	    // Sleep for between 0 and 2 seconds before calculating n!
	    std::this_thread::sleep_for( std::chrono::milliseconds( static_cast<long>(f(generator) * 2000 )) );
	    // n! = n * (n-1)!
	    factorial = n * factorial;
	    std::cout << name << ": " << n << "! = " << factorial << std::endl;
	}
	std::cout << name << "(" << std::this_thread::get_id() << ") finished" << std::endl;
    }
};


/**
 * This thread calculates fib(1) through fib(20), where
 * fib(1) = 1
 * fib(2) = 1
 * fib(n) = fib(n-1) + fib(n-2), n >2
 */

class Fibonacci {
public:
    void operator()( const std::string& name ) {
        // fib(1) = 1
        int firstFib = 0;
        int secondFib = 1;
	std::cout << name << ": fib(1) = " << secondFib <<  std::endl;

        for (int n = 2; n <= count; n++) {
	    std::this_thread::sleep_for( std::chrono::milliseconds( static_cast<long>(f(generator) * 2000 )) );

            // fib(n) = fib(n-1) + fib(n-2)
            int fibN = firstFib + secondFib;
	    std::cout << name << ": fib(" << n << ") = " << fibN << std::endl;
            firstFib = secondFib;
            secondFib = fibN;
        }
	std::cout << name << "(" << std::this_thread::get_id() << ") finished" << std::endl;
    }
};



int main( int argc, char ** argv )
{
    std::cerr << "Creating factorial thread." << std::endl;
    Factorial compute;
    std::thread thread1( Factorial(), "Factorial 1" );
    std::cerr << "Created: " << thread1.get_id() << std::endl;
    std::thread thread2( Factorial(), "Factorial 2" );
    std::cerr << "Created: " << thread2.get_id() << std::endl;
    std::thread thread3( Fibonacci(), "Fibonacci" );
    std::cerr << "Created: " << thread3.get_id() << std::endl;
    thread1.join();
    thread2.join();
    thread3.join();
    std::cerr << "main ended." << std::endl;
    return 0;
}
