#include "catch.hpp"

#include <iostream>

#include "../src/Event.hpp"

class TestEvent : public Event
{
    public:
    using Event::Event;
};

class ExtendedTestEvent : public Event
{
    public:
    ExtendedTestEvent(std::string type)
        : Event(std::move(type))
    {
        deserializers_.insert_or_assign(type_, [](std::string type, std::vector<unsigned char> data){
            auto e = std::make_unique<ExtendedTestEvent>(type);
            if (data[0] == '0')
                e->value = false;
            else if (data[0] == '1')
                e->value = true;
            else
                throw std::runtime_error("Value cannot be determined.");
            return e;
        });
    }
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
        Event::clearDeserializers();
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
        Event::clearDeserializers();
	}

    SECTION( "Base event deserialization" ) {
        auto e = Event("test");
        auto s = e.serialize();
        auto e_prim = Event::deserialize(s);

        REQUIRE(e.getType() == e_prim->getType());
        Event::clearDeserializers();
    }

    SECTION( "Derived event deserialization" ) {
        auto e1 = ExtendedTestEvent{"test1"};
        e1.value = true;
        auto s1 = e1.serialize();
        auto e1_prim_base = Event::deserialize(s1);
        auto e1_prim = dynamic_cast<ExtendedTestEvent*>(e1_prim_base.get());

        REQUIRE(e1.getType() == e1_prim->getType());
        REQUIRE(e1.value == e1_prim->value);

        auto e2 = ExtendedTestEvent{"test2"};
        e2.value = false;
        auto s2 = e2.serialize();
        auto e2_prim_base = Event::deserialize(s2);
        auto e2_prim = dynamic_cast<ExtendedTestEvent*>(e2_prim_base.get());

        REQUIRE(e2.getType() == e2_prim->getType());
        REQUIRE(e2.value == e2_prim->value);
        Event::clearDeserializers();
    }
}