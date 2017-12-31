#pragma once

#include <algorithm>
#include <cstdint>

#include "ip.h"

ip_pool_t filter_by_first_byte( const ip_pool_t& ip_pool, const uint8_t firstByte );

ip_pool_t filter_by_first_and_second_byte( const ip_pool_t& ip_pool, const uint8_t firstByte, const uint8_t secondByte );

ip_pool_t filter_by_any_byte( const ip_pool_t& ip_pool, const uint8_t anyByte );

ip_pool_t filter_by_bytes( const ip_pool_t& ip_pool, const std::vector<uint8_t>& bytes );

template<class...Args>
auto filter_by_bytes( const ip_pool_t& ip_pool, Args... args )
{
    ip_pool_t ip_pool_new;

    std::copy_if( ip_pool.cbegin(), ip_pool.cend(),
        std::back_inserter( ip_pool_new ),
        [&args...]( const ip_t& obj )
    {
        size_t i = 0;
        bool ret = true;
        auto temp = { ( ret &= ( obj.at( i++ ) == args ) )... };
        return ret;
    } );

    return ip_pool_new;
}

template<class...Args>
auto filter_by_bytes2( const ip_pool_t& ip_pool, Args... args )
{
    const std::vector<uint8_t> bytes = { uint8_t(args)... };

    return filter_by_bytes( ip_pool, bytes );
}