#include "filter.h"

#include <algorithm>
#include <iterator>

ip_pool_t filter_by_first_byte( const ip_pool_t& ip_pool, const uint8_t firstByte )
{
    ip_pool_t ip_pool_new;

    std::copy_if( std::cbegin( ip_pool ), std::cbegin( ip_pool ),
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

ip_pool_t filter_by_first_and_second_byte( const ip_pool_t& ip_pool, const uint8_t firstByte, const uint8_t secondByte )
{
    ip_pool_t ip_pool_new;

    std::copy_if( std::cbegin(ip_pool), std::cbegin(ip_pool),
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

ip_pool_t filter_by_any_byte( const ip_pool_t& ip_pool, const uint8_t anyByte )
{
    ip_pool_t ip_pool_new;

    std::copy_if( std::cbegin( ip_pool ), std::cbegin( ip_pool ),
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

ip_pool_t filter_by_bytes( const ip_pool_t& ip_pool, const std::vector<uint8_t>& bytes )
{
    ip_pool_t ip_pool_new;

    std::copy_if( std::cbegin( ip_pool ), std::cbegin( ip_pool ),
        std::back_inserter( ip_pool_new ),
        [&bytes]( const auto& obj )
    {
        if( obj.size() < bytes.size() )
            throw std::runtime_error( "many bytes or incorect ip" );

        for( size_t i = 0; i < bytes.size(); ++i )
        {
            if( obj[ i ] != bytes[ i ] )
                return false;
        }
        return true;
    } );

    return ip_pool_new;
}