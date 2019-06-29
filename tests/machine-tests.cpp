#include "catch.hpp"

#include <iostream>
#include "../src/StateMachine.hpp"

TEST_CASE( "State machine", "[State machine]" ) {
    SECTION( "Adding transition" ) {
        auto sm = StateMachine{};
        auto s1 = std::make_shared<State>("s1");
        auto s2 = std::make_shared<State>("s2");
        auto eventType = "event";

        REQUIRE_NOTHROW(sm.addTranstition(s1, eventType, s2));
    }

    SECTION( "Transition conflict" ) {
        auto sm = StateMachine{};
        auto s1 = std::make_shared<State>("s1");
        auto s2 = std::make_shared<State>("s2");

        auto eventType = "event";

        REQUIRE_NOTHROW(sm.addTranstition(s1, eventType, s2));

        auto s1_prim = s1;
        auto s2_prim = s2;
        
        REQUIRE_THROWS(sm.addTranstition(s1_prim, eventType, s2_prim));
    }
}