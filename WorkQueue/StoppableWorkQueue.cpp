#include <string>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

using namespace std::literals::chrono_literals;

template <typename Type> class WorkQueue
{
private:
    std::list<Type> queue;
    std::mutex mtx;
    std::condition_variable_any cv;
    
public:
    WorkQueue() : queue(), mtx(), cv() {}

    void run( std::stop_token stop_token, const std::string& name ) {
	std::cerr << name << ": run()" << std::endl;
	std::jthread thread( &WorkQueue<Type>::dispatch, this, stop_token, "worker" );
	thread.join();
	std::cerr << name << ": run() finished." << std::endl;
    }

    void enqueue(const std::string& workItem) {
	std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
	queue.push_back(workItem);
	cv.notify_all();
    }

    void processItem(const Type& workItem) {
	std::cout << "processing "  << workItem << std::endl;
	std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
    }

private:
    void dispatch( std::stop_token stop_token, const std::string& name ) {
	while (true) {
	    Type workItem;
	    {
		std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
		if ( !cv.wait(lock,stop_token,[&](){return !queue.empty();}) ) {
		    std::cerr << "Stopping " <<  name << std::endl;
		    return;
		}
		workItem = queue.front();
		queue.pop_front();
	    }
	    processItem(workItem);
	}
    }
};


int main( int argc, char ** argv )
{
    std::stop_source stop_source;
    WorkQueue<std::string> dispatcher;
    std::jthread thread( &WorkQueue<std::string>::run, &dispatcher, stop_source.get_token(), "dispatcher" );
    std::cerr << "main() enqueues...." << std::endl;
    dispatcher.enqueue( "One" );
    dispatcher.enqueue( "Two" );
    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    dispatcher.enqueue( "Three" );
    std::this_thread::sleep_for( 6s );
    std::cerr << "main() finished." << std::endl;
    stop_source.request_stop();
//    thread.join();
}
