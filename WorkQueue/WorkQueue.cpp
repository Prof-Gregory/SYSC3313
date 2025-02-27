#include <string>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

template <typename Type> class WorkQueue
{
private:
    std::list<Type> queue;
    std::mutex mtx;
    std::condition_variable cv;
    
public:
    WorkQueue() : queue(), mtx(), cv() {}

    void run( const std::string& name ) {
	std::cerr << name << ": run()" << std::endl;
	std::thread thread( &WorkQueue<Type>::dispatch, this, "dispatcher" );
	thread.join();
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
    void dispatch( const std::string& name ) {
	while (true) {
	    Type workItem;
	    {
	    std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
	    while ( queue.empty() ) {
		cv.wait(lock);
	    }
	    workItem = queue.front();
	    queue.pop_front();
	    }
//	    mtx.unlock(); // end of critical section
	    processItem(workItem);
	}
    }
};


int main( int argc, char ** argv )
{
    WorkQueue<std::string> dispatcher;
    std::thread thread( &WorkQueue<std::string>::run, &dispatcher, "dispatcher" );
    std::cerr << "main() enqueues...." << std::endl;
    dispatcher.enqueue( "One" );
    dispatcher.enqueue( "Two" );
    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    dispatcher.enqueue( "Three" );
    std::cerr << "main() finished." << std::endl;
    thread.join();
}
