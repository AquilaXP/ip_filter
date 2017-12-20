#include <iostream>
#include <vector>
#include <fstream>

#include "ip.h"
#include "lex_sort.h"
#include "filter.h"
#include "read_ip_from_stream.h"

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
        read_ip_from_stream( ip_pool, std::cin );

        lexicographically_reverse_sort( ip_pool );
        std::cout << ip_pool;
        std::cout << filter_by_bytes( ip_pool, 1 );
        std::cout << filter_by_bytes( ip_pool, { 46, 70 } );
        std::cout << filter_by_any_byte( ip_pool, 46 );
    }
    catch( const std::exception &e )
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
