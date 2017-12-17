#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "split_ip.h"

using ip_str_t = std::vector<std::string>;

struct ip_t : public std::vector<uint8_t>
{
    ip_t( const ip_str_t& ip_str )
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

std::ostream& operator << ( std::ostream& ostr, const ip_t& ip )
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

std::ostream& operator << ( std::ostream& ostr, const ip_pool_t& ip_pool )
{
    for( auto& ip : ip_pool )
    {
        ostr << ip;
        ostr << '\n';
    }
    return ostr;
}

ip_pool_t LexicographicallyReverseSort( const ip_pool_t& ip_pool )
{
    auto ip_pool_new = ip_pool;
    std::sort( std::begin( ip_pool_new ), std::end( ip_pool_new ),
        []( const auto& left, const auto& right )
    {
        if( left.size() != right.size() )
            throw std::runtime_error( "incorect length ip" );

        auto size = left.size();
        for( auto i = 0; i < size; ++i )
        {
            if( left[i] > right[i] )
            {
                return true;
            }
            else if( left[i] < right[i] )
            {
                return false;
            }
        }
        return false;
    } );

    return ip_pool_new;
}

ip_pool_t FilterByFirstByte( const ip_pool_t& ip_pool, const uint8_t firstByte )
{
    ip_pool_t ip_pool_new;

    std::copy_if( std::cbegin( ip_pool ), std::cend( ip_pool ),
        std::back_inserter( ip_pool_new ),
        [f = firstByte]( const auto& obj )
    {
        if( obj.at( 0 ) == f )
        {
            return true;
        }
        return false;
    } );

    return ip_pool_new;
}

ip_pool_t FilterByFirstAndSecondByte( const ip_pool_t& ip_pool, const uint8_t firstByte, const uint8_t secondByte )
{
    ip_pool_t ip_pool_new;

    std::copy_if( std::cbegin( ip_pool ), std::cend( ip_pool ),
        std::back_inserter( ip_pool_new ),
        [f = firstByte, s = secondByte]( const auto& obj )
    {
        if( obj.at( 0 ) == f && obj.at( 1 ) == s )
        {
            return true;
        }
        return false;
    } );

    return ip_pool_new;
}

ip_pool_t FilterByAnyByte( const ip_pool_t& ip_pool, const uint8_t anyByte ) noexcept
{
    ip_pool_t ip_pool_new;

    std::copy_if( std::cbegin( ip_pool ), std::cend( ip_pool ),
        std::back_inserter( ip_pool_new ),
        [a = anyByte]( const auto& obj )
    {
        for( const auto& o : obj )
        {
            if( o == a )
                return true;
        }

        return false;
    } );

    return ip_pool_new;
}

int main( int argc, char const *argv[] )
{   
    try
    {        
        std::ofstream ofstr;
        std::ifstream ifstr;
        if( argc >= 2 )
        {
            ifstr.open( argv[1] );
            std::cin.set_rdbuf( ifstr.rdbuf() );
            if( argc >= 3 )
            {
                ofstr.open( argv[2] );
                std::cout.set_rdbuf( ofstr.rdbuf() );
            }
        }

        ip_pool_t ip_pool;
        for( std::string line; std::getline( std::cin, line ); )
        {
            auto v = split( line, '\t' );
            ip_pool.emplace_back( split( v.at( 0 ), '.' ) );
        }
        const auto sort_ip_pool = LexicographicallyReverseSort( ip_pool );
        std::cout << sort_ip_pool;
        std::cout << FilterByFirstByte( sort_ip_pool, 1 );
        std::cout << FilterByFirstAndSecondByte( sort_ip_pool, 46, 70 );
        std::cout << FilterByAnyByte( sort_ip_pool, 46 );
    }
    catch( const std::exception &e )
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
