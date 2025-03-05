#include <cassert>
#include <vector>
#include <iostream>

#define SIZE 10000

int
main( int argc, char **argv )
{
    std::vector<int> v(SIZE);
    int i;

    for ( i = 0; i < SIZE; ++i ) {
	v[i] = i;
    }

    for ( i = 0; i < SIZE; ++i ) {
	assert( i == v[i] );
    }
}
