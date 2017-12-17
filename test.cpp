#define BOOST_TEST_MODULE test_ip_filter

#include <string>
#include <fstream>

#include <boost/test/unit_test.hpp>

#include "lib.h"
#include "split_ip.h"
#include "lex_sort.h"
#include "filter.h"
#include "read_ip_from_stream.h"

BOOST_AUTO_TEST_SUITE( test_ip_filter )

    BOOST_AUTO_TEST_CASE( test_valid_version )
    {
        BOOST_CHECK( version() > 0 );
    }

    BOOST_AUTO_TEST_CASE( test_split_ip1 )
    {
        // ("",  '.') -> [""]
        auto res = split( "", '.' );
        BOOST_REQUIRE_EQUAL( res.size(), size_t(1) );
        BOOST_REQUIRE( res.at( 0 ).empty() );
    }

    BOOST_AUTO_TEST_CASE( test_split_ip2 )
    {
        // ("11", '.') -> ["11"]
        auto res = split( "11", '.' );
        BOOST_REQUIRE_EQUAL( res.size(), size_t(1) );
        BOOST_REQUIRE_EQUAL( res.at( 0 ), "11" );
    }

    BOOST_AUTO_TEST_CASE( test_split_ip3 )
    {
        // ("..", '.') -> ["", "", ""]
        auto etalon = { "", "", "" };
        auto res = split( "..", '.' );
        BOOST_REQUIRE( res.size() == 3 );
        BOOST_REQUIRE_EQUAL_COLLECTIONS( res.begin(), res.end(), etalon.begin(), etalon.end() );
    }

    BOOST_AUTO_TEST_CASE( test_split_ip4 )
    {
        // ("11.", '.') -> ["11", ""]
        auto etalon = { "11", "" };
        auto res = split( "11.", '.' );
        BOOST_REQUIRE( res.size() == 2 );
        BOOST_REQUIRE_EQUAL_COLLECTIONS( res.begin(), res.end(), etalon.begin(), etalon.end() );
    }

    BOOST_AUTO_TEST_CASE( test_split_ip5 )
    {
        // (".11", '.') -> ["", "11"]
        auto etalon = { "", "11" };
        auto res = split( ".11", '.' );
        BOOST_REQUIRE( res.size() == 2 );
        BOOST_REQUIRE_EQUAL_COLLECTIONS( res.begin(), res.end(), etalon.begin(), etalon.end() );
    }

    BOOST_AUTO_TEST_CASE( test_split_ip6 )
    {
        // ("11.22", '.') -> ["11", "22"]
        auto etalon = { "11", "22" };
        auto res = split( "11.22", '.' );
        BOOST_REQUIRE( res.size() == 2 );
        BOOST_REQUIRE_EQUAL_COLLECTIONS( res.begin(), res.end(), etalon.begin(), etalon.end() );
    }

    BOOST_AUTO_TEST_CASE( test_lex_res_sort_ip )
    {
        std::ifstream input( "ip.tsv" );
        BOOST_REQUIRE( input.is_open() );
        ip_pool_t ip_pool;
        read_ip_from_stream( ip_pool, input );
        input.close();

        lexicographically_reverse_sort( ip_pool );

        for( auto it = ip_pool.begin(), it_next = ip_pool.begin() + 1;
            it_next != ip_pool.end();
            ++it_next, ++it )
        {
            BOOST_REQUIRE( ( *it ) >= ( *it_next ) );
        }
    }


    BOOST_AUTO_TEST_CASE( test_filter_by_first_byte )
    {
        std::ifstream input( "ip.tsv" );
        BOOST_REQUIRE( input.is_open() );
        ip_pool_t ip_pool;
        read_ip_from_stream( ip_pool, input );
        input.close();

        lexicographically_reverse_sort( ip_pool );

        const std::string test = {
            R"(1.231.69.33
            1.87.203.225
            1.70.44.170
            1.29.168.152
            1.1.234.8)"
        };
        ip_pool_t etalon_pool;
        std::istringstream ss( std::move(test) );
        read_ip_from_stream( etalon_pool, ss );

        auto ip_pool_filter = filter_by_bytes( ip_pool, { 1 } );
        BOOST_REQUIRE_EQUAL( ip_pool_filter, etalon_pool );
    }


    BOOST_AUTO_TEST_CASE( test_filter_by_first_and_second_byte )
    {
        std::ifstream input( "ip.tsv" );
        BOOST_REQUIRE( input.is_open() );
        ip_pool_t ip_pool;
        read_ip_from_stream( ip_pool, input );
        input.close();

        lexicographically_reverse_sort( ip_pool );

        const std::string test = {
            R"(46.70.225.39
            46.70.147.26
            46.70.113.73
            46.70.29.76)"
        };
        ip_pool_t etalon_pool;
        std::istringstream ss( std::move( test ) );
        read_ip_from_stream( etalon_pool, ss );

        auto ip_pool_filter = filter_by_bytes( ip_pool, { 46, 70 } );
        BOOST_REQUIRE_EQUAL( ip_pool_filter, etalon_pool );
    }

    BOOST_AUTO_TEST_CASE( test_filter_by_any_byte )
    {
        std::ifstream input( "ip.tsv" );
        BOOST_REQUIRE( input.is_open() );
        ip_pool_t ip_pool;
        read_ip_from_stream( ip_pool, input );
        input.close();

        lexicographically_reverse_sort( ip_pool );

        const std::string test = {
            R"(186.204.34.46
            186.46.222.194
            185.46.87.231
            185.46.86.132
            185.46.86.131
            185.46.86.131
            185.46.86.22
            185.46.85.204
            185.46.85.78
            68.46.218.208
            46.251.197.23
            46.223.254.56
            46.223.254.56
            46.182.19.219
            46.161.63.66
            46.161.61.51
            46.161.60.92
            46.161.60.35
            46.161.58.202
            46.161.56.241
            46.161.56.203
            46.161.56.174
            46.161.56.106
            46.161.56.106
            46.101.163.119
            46.101.127.145
            46.70.225.39
            46.70.147.26
            46.70.113.73
            46.70.29.76
            46.55.46.98
            46.49.43.85
            39.46.86.85
            5.189.203.46)"
        };
        ip_pool_t etalon_pool;
        std::istringstream ss( std::move( test ) );
        read_ip_from_stream( etalon_pool, ss );

        auto ip_pool_filter = filter_by_any_byte( ip_pool, 46 );
        BOOST_REQUIRE_EQUAL( ip_pool_filter, etalon_pool );
    }

BOOST_AUTO_TEST_SUITE_END()