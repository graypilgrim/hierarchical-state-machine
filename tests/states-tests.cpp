#include "catch.hpp"

#include "../src/State.hpp"

TEST_CASE( "States hierarchy", "[states]" ) {
	SECTION( "States creation" ) {
        auto s1 = std::make_shared<State>("s1");
        auto s2 = std::make_shared<State>("s2", s1);

        auto p = s2->getParent().lock();
        assert(p);
        REQUIRE(p.get() == s1.get());
	}

    SECTION( "State creation" ) {
        auto s1 = std::make_shared<State>("s1");
        auto s2 = std::make_shared<State>("s2");
        s1->addChild(s2);
        s1->addChild(std::make_shared<State>("s3"));
        s1->addChild(std::make_shared<State>("s4"));
        s1->addChild(std::make_shared<State>("s5"));
        auto s6 = std::make_shared<State>("s6");
        s1->addChild(s6);
        s1->addChild(std::make_shared<State>("s7"));
        
        s1->setDefaultChild(0);
        auto s = s1->getDefaultChild();
        REQUIRE(s.get() == s2.get());

        s1->setDefaultChild(4);
        s = s1->getDefaultChild();
        REQUIRE(s.get() == s6.get());
	}
}
