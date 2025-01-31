#include <iostream>
#include <set>
#include <string>

struct pred {
    pred( const std::string& s ) : _s(s) {}
    bool operator()( const std::string& s ) const { return s == _s; }
private:
    const std::string _s;
};

std::set<const std::string> strings = { "fred", "barney" };

int main() {
    if ( std::find_if( strings.begin(), strings.end(), pred( "fred" ) ) != strings.end() ) {
	std::cout << "found" << std::endl;
    } else {
	std::cout << "not found" << std::endl;
    }
    return 0;
}

  
