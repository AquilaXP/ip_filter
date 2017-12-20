#include "lex_sort.h"

#include <algorithm>
#include <stdexcept>

void lexicographically_reverse_sort( ip_pool_t& ip_pool )
{
    std::sort( std::begin( ip_pool ), std::end( ip_pool ),
        []( const auto& left, const auto& right )
    {
        if( left > right )
            return true;
        return false;
    } );
}