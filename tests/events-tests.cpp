#include "catch.hpp"

#include "../src/Event.hpp"

class TestEvent : public Event
{
    public:
    using Event::Event;
};

class ExtendedTestEvent : public Event
{
    public:
    using Event::Event;
    bool value = true;

    std::vector<unsigned char> serializeImpl() override {
        std::vector<unsigned char> ret;
        ret.push_back(value ? '1' : '0');
        return ret;
    }
};

TEST_CASE( "Events", "[events]" ) {
	SECTION( "Simple event serialization" ) {
        auto e = TestEvent{"test"};
        auto serialized = e.serialize();
        std::string s{serialized.begin(), serialized.end()};

        REQUIRE(s == "test;");
	}

    SECTION( "Event serialization" ) {
        auto e1 = ExtendedTestEvent{"test"};
        e1.value = true;
        auto serialized = e1.serialize();
        std::string s1{serialized.begin(), serialized.end()};

        REQUIRE(s1 == "test;1");

        auto e2 = ExtendedTestEvent{"test"};
        e2.value = false;
        serialized = e2.serialize();
        std::string s2{serialized.begin(), serialized.end()};

        REQUIRE(s2 == "test;0");
	}
}