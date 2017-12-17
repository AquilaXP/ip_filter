#include <string>
#include <istream>

#include "read_ip_from_stream.h"
#include "split_ip.h"

void read_ip_from_stream( ip_pool_t& ip_pool, std::istream& istr )
{
    for( std::string line; std::getline( istr, line ); )
    {
        auto v = split( line, '\t' );
        ip_pool.emplace_back( split( v.at( 0 ), '.' ) );
    }
}
