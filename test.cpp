#define BOOST_TEST_MODULE test_ip_filter

#include <string>

#include <boost/test/unit_test.hpp>

#include "lib.h"
#include "split_ip.h"

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

BOOST_AUTO_TEST_SUITE_END()
