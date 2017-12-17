#include "filter.h"

#include <algorithm>
#include <iterator>

ip_pool_t filter_by_first_byte( const ip_pool_t& ip_pool, const uint8_t firstByte )
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

ip_pool_t filter_by_first_and_second_byte( const ip_pool_t& ip_pool, const uint8_t firstByte, const uint8_t secondByte )
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

ip_pool_t filter_by_any_byte( const ip_pool_t& ip_pool, const uint8_t anyByte )
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

ip_pool_t filter_by_bytes( const ip_pool_t& ip_pool, const std::vector<uint8_t>& bytes )
{
    ip_pool_t ip_pool_new;

    std::copy_if( ip_pool.cbegin(), ip_pool.cend(),
        std::back_inserter( ip_pool_new ),
        [&bytes]( const ip_t& obj )
    {
        for( size_t i = 0; i < bytes.size(); ++i )
        {
            if( obj.at( i ) != bytes.at( i ) )
                return false;
        }
        return true;
    } );

    return ip_pool_new;
}