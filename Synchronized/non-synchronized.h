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

public:
    synchronized() : c() {}
    synchronized(size_type n, const value_type& val = value_type()) : c(n,val) {}

    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    reference at(size_type n) { return c.at(n); }
    const_reference at(size_type n) const { return c.at(n); }
    void resize(size_type sz) { c.resize(sz); }
    void resize(size_type sz, const value_type& v) { c.resize(sz,v); }
};

