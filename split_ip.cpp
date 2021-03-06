#include "split_ip.h"

std::vector<std::string> split( const std::string &str, char d )
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    auto stop = str.find_first_of( d );
    while( stop != std::string::npos )
    {
        r.emplace_back( str.substr( start, stop - start ) );

        start = stop + 1;
        stop = str.find_first_of( d, start );
    }

    r.emplace_back( str.substr( start ) );

    return r;
}
