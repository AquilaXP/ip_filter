#include "lex_sort.h"

#include <algorithm>
#include <stdexcept>

ip_pool_t lexicographically_reverse_sort( const ip_pool_t& ip_pool )
{
    auto ip_pool_new = ip_pool;
    std::sort( std::begin( ip_pool_new ), std::end( ip_pool_new ),
        []( const ip_t& left, const ip_t& right )
    {
        if( left.size() != right.size() )
            throw std::runtime_error( "incorect length ip" );

        auto size = left.size();
        for( decltype( size ) i = 0; i < size; ++i )
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