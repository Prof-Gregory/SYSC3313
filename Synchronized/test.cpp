#include "synchronized.h"
#include <iostream>


int
main( int argc, char **argv )
{
    synchronized<int> v(10);
    int i;

    for ( i = 0; i < 10; ++i ) {
	v.at(i) = i;
    }

    for ( i = 0; i < 10; ++i ) {
	std::cerr << "i = " << i << ", v[i] = " << v.at(i) << std::endl;
    }
}
