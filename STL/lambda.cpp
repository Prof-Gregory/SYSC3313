#include <iostream>
#include <set>
#include <string>

std::set<const std::string> strings = { "fred", "barney" };

int main() {
    const std::string name("barney");
    if ( std::find_if( strings.begin(), strings.end(), [&](const std::string& s){return s == name;}) != strings.end() ) {
	std::cout << "found" << std::endl;
    } else {
	std::cout << "not found" << std::endl;
    }
    return 0;
}

  
