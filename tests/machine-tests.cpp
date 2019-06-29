#include "catch.hpp"

#include <iostream>
#include "../src/StateMachine.hpp"

class MockedMachine : public StateMachine
{
    public:
    using StateMachine::StateMachine;
    std::shared_ptr<State> getCurrentState() {
        return currentState_;
    }
    void makeTransitionMocked(const std::string &eventType) {
        makeTransition(eventType);
    }
};

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

    SECTION( "Machine lifecycle" ) {
        auto stateOff = std::make_shared<State>("Off");
        auto stateOn = std::make_shared<State>("On");
        auto stateStopped = std::make_shared<State>("Stopped");
        auto statePlaying = std::make_shared<State>("Playing");
        stateOn->addChild(stateStopped);
        stateOn->addChild(statePlaying);
        stateOn->setDefaultChild(0);

        MockedMachine mm;
        mm.addTranstition(stateOff, "PowerOn", stateOn);
        mm.addTranstition(stateOn, "PowerOff", stateOff);
        mm.addTranstition(stateStopped, "Start", statePlaying);
        mm.addTranstition(statePlaying, "Stop", stateStopped);
        mm.setStartState(stateOff);
        REQUIRE(mm.getCurrentState().get() == stateOff.get());

        mm.makeTransitionMocked("PowerOn");
        REQUIRE(mm.getCurrentState().get() == stateStopped.get());

        mm.makeTransitionMocked("Start");
        REQUIRE(mm.getCurrentState().get() == statePlaying.get());
        
        mm.makeTransitionMocked("PowerOff");
        REQUIRE(mm.getCurrentState().get() == stateOff.get());
    }
}