/* -*- c++ -*- */
#include <vector>
#include <mutex>

template <class T, class _Container = std::vector<T> > class synchronized {

public:
    typedef T value_type;
    typedef size_t size_type;
    typedef _Container container_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;

private:
    container_type c;
    std::mutex m;

public:
    synchronized() : c() {}
    synchronized(size_type n, const value_type& val = value_type()) : c(n,val) {}

    bool empty() const { std::lock_guard<std::mutex> l(m); return c.empty(); }
    size_type size() const { std::lock_guard<std::mutex> l(m); return c.size(); }
    reference operator[](size_type n) { std::lock_guard<std::mutex> l(m); return c[n]; }
    const_reference operator[](size_type n) const { std::lock_guard<std::mutex> l(m); return c[n]; }
    reference at(size_type n) { std::lock_guard<std::mutex> l(m); return c.at(n); }
    const_reference at(size_type n) const { std::lock_guard<std::mutex> l(m); return c.at(n); }
    void resize(size_type sz) { std::lock_guard<std::mutex> l(m); c.resize(sz); }
    void resize(size_type sz, const value_type& v) { std::lock_guard<std::mutex> l(m); c.resize(sz,v); }
};

