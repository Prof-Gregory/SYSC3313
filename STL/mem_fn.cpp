#include <iostream>
#include <functional>
#include <vector>
#include <string>

std::vector<const std::string> strings = { "fred", "barney", "" };

int main() {
    if ( std::find_if( strings.begin(), strings.end(), std::mem_fn( &std::string::empty ) ) != strings.end() ) {
	std::cout << "found" << std::endl;
    } else {
	std::cout << "not found" << std::endl;
    }
    return 0;
}

  
