#include "catch.hpp"

#include "../src/StateMachine.hpp"

TEST_CASE( "State machine", "[State machine]" ) {
	SECTION( "Simple transition table" ) {
        auto sm = StateMachine{};

        REQUIRE(true);
	}
}