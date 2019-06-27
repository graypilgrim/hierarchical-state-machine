#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE( "Dummy test", "[dummy]" ) {
	REQUIRE( 1 == 1 );
}