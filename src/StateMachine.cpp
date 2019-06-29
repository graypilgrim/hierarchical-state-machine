#include "StateMachine.hpp"

#include <sstream>
#include <iostream>

void StateMachine::addTranstition(const std::shared_ptr<State> &from, std::string eventType, const std::shared_ptr<State> &to)
{
    auto insertion = transitionTable_.emplace(TransitionTableKey{from, eventType}, to);
    if (!insertion.second) {
        std::stringstream ss;
        ss << "Transition from state \"" << from->getName() << "\" in case of event \"" << eventType << "\" already exists";
        throw std::logic_error(ss.str().c_str());
    }
}