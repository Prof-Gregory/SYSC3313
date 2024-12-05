/*
 * Copied from https://en.cppreference.com/w/cpp/atomic/atomic
 * jthread isn't present in clang, so added explicit joins.
 */
 
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
 
std::atomic_int acnt;
int cnt;
 
void f() {
    for (int n = 0; n < 10000; ++n) {
        ++acnt;
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
