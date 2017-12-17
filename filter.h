#pragma once

#include <cstdint>


#include "ip.h"

ip_pool_t filter_by_first_byte( const ip_pool_t& ip_pool, const uint8_t firstByte );

ip_pool_t filter_by_first_and_second_byte( const ip_pool_t& ip_pool, const uint8_t firstByte, const uint8_t secondByte );

ip_pool_t filter_by_any_byte( const ip_pool_t& ip_pool, const uint8_t anyByte );
