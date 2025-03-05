#include <cassert>
#include "synchronized.h"
#include <thread>

#define SIZE 10000

int
main( int argc, char **argv )
{
    synchronized<int> v(SIZE);

    std::thread even( [&](){ for ( int i = 0; i < SIZE; i += 2 ) v[i] = i; } );
    std::thread odd( [&](){ for ( int i = 1; i < SIZE; i += 2 )  v[i] = i; } );
    even.join();
    odd.join();
    for ( int i = 0; i < SIZE; ++i ) assert( i == v[i] );
}
