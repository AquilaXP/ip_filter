#include "lex_sort.h"

#include <algorithm>
#include <stdexcept>

void lexicographically_reverse_sort( ip_pool_t& ip_pool )
{
    std::sort( std::begin( ip_pool ), std::end( ip_pool ),
        []( const auto& left, const auto& right )
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
}