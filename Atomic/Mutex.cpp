/*
 * Copied from https://en.cppreference.com/w/cpp/atomic/atomic
 * jthread isn't present in clang, so added explicit joins.
 */
 
#include <iostream>
#include <thread>
#include <vector>
#include <mutex> 

int acnt;
int cnt;
std::mutex mtx;
 
void f() {
    for (int n = 0; n < 10000; ++n) {
	{
	    std::lock_guard<std::mutex> lock(mtx);
	    ++acnt;
//	    lock.unlock();
	}
        ++cnt;
        // Note: for this example, relaxed memory order
        // is sufficient, e.g. acnt.fetch_add(1, std::memory_order_relaxed);
    }
}
 
int main() {
    {
        std::vector<std::thread> pool;
        for (int n = 0; n < 10; ++n)
            pool.emplace_back(f);
        for (auto& thread : pool )
            thread.join();
    }
 
    std::cout << "The atomic counter is " << acnt << std::endl
              << "The non-atomic counter is " << cnt << std::endl;
}
