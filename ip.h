#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <limits>
#include <iosfwd>

using ip_str_t = std::vector<std::string>;

struct ip_t : public std::vector<uint8_t>
{
    explicit ip_t( const ip_str_t& ip_str )
    {
        for( auto& ip_part : ip_str )
        {
            const auto number = std::stoul( ip_part );
            if( number > ( std::numeric_limits<value_type>::max )( ) )
                throw std::runtime_error( "incorect ip, max part ip 255" );
            push_back( number );
        }
    }
};

using ip_pool_t = std::vector<ip_t>;

inline std::ostream& operator << ( std::ostream& ostr, const ip_t& ip )
{
    for( auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part )
    {
        if( ip_part != ip.cbegin() )
        {
            ostr << '.';
        }
        ostr << uint32_t( *ip_part );
    }
    return ostr;
}

inline std::ostream& operator << ( std::ostream& ostr, const ip_pool_t& ip_pool )
{
    for( auto& ip : ip_pool )
    {
        ostr << ip;
        ostr << '\n';
    }
    return ostr;
}