#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "split_ip.h"
#include "ip.h"
#include "lex_sort.h"


ip_pool_t FilterByFirstByte( const ip_pool_t& ip_pool, const uint8_t firstByte )
{
    ip_pool_t ip_pool_new;

    std::copy_if( ip_pool.cbegin(), ip_pool.cend(),
        std::back_inserter( ip_pool_new ),
        [f = firstByte]( const ip_t& obj )
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

    std::copy_if( ip_pool.cbegin(), ip_pool.cend(),
        std::back_inserter( ip_pool_new ),
        [f = firstByte, s = secondByte]( const ip_t& obj )
    {
        if( obj.at( 0 ) == f && obj.at( 1 ) == s )
        {
            return true;
        }
        return false;
    } );

    return ip_pool_new;
}

ip_pool_t FilterByAnyByte( const ip_pool_t& ip_pool, const uint8_t anyByte )
{
    ip_pool_t ip_pool_new;

    std::copy_if( ip_pool.cbegin(), ip_pool.cend(),
        std::back_inserter( ip_pool_new ),
        [a = anyByte]( const ip_t& obj )
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
#ifdef _MSC_VER
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
#endif

        ip_pool_t ip_pool;
        for( std::string line; std::getline( std::cin, line ); )
        {
            auto v = split( line, '\t' );
            ip_pool.emplace_back( split( v.at( 0 ), '.' ) );
        }
        const auto sort_ip_pool = lexicographically_reverse_sort( ip_pool );
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
