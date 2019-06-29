#include "StateMachine.hpp"

#include "QueueLibrary.h"
#include "configuration.hpp"
#include "Event.hpp"

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

void StateMachine::setStartState(std::shared_ptr<State> state)
{
    chooseCurrentState(std::move(state));
}

void StateMachine::run()
{
    auto queueHandle = QueueCreate(configuration::QUEUE_LENGTH, configuration::MESSAGE_SIZE);
    void *msg = nullptr;
    std::vector<unsigned char> data;
    
    while (true) {
        QueueReceive(queueHandle, msg);
        if (!msg)
            break;
        
        auto ptr = static_cast<unsigned char*>(msg);
        auto data = std::vector<unsigned char>{ptr, ptr + configuration::MESSAGE_SIZE};

        auto ev = Event::deserialize(data);
        makeTransition(ev->getType());
    }
}

void StateMachine::makeTransition(const std::string &eventType)
{
    auto state = currentState_;
    while (state) {
        auto key = TransitionTableKey{state, eventType};
        auto search = transitionTable_.find(key);
        if (search != transitionTable_.end()) {
            chooseCurrentState(search->second);
            return;
        } else {
            state = state->getParent().lock();
        }
    }

    std::cerr << "Event \"" << eventType << "\" does not cause a change of active state." << std::endl;
}

void StateMachine::chooseCurrentState(std::shared_ptr<State> state)
{
    if (currentState_)
        currentState_->deactivate();

    auto currentCandidate = state->getDefaultChild();
    if (currentCandidate) {
        currentState_ = std::move(currentCandidate);
        currentState_->activate();
    } else {
        std::cerr << "State \"" << currentCandidate->getName() << "\" does not provide default state. Transition aborted." << std::endl;
    }
}