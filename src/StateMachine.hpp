#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "State.hpp"
#include "Event.hpp"

#include <unordered_map>
#include <memory>

using TransitionTableKey = std::pair<std::shared_ptr<State>, std::string>;

template <>
struct std::hash<TransitionTableKey>
{
    std::size_t operator()(const TransitionTableKey& key) const
    {
        using std::hash;
        using std::string;
        using std::shared_ptr;

        return ((hash<shared_ptr<State>>()(key.first) ^ (hash<string>()(key.second) << 1)) >> 1);
    }
};

class StateMachine
{
    public:
    StateMachine() = default;
    void addTranstition(const std::shared_ptr<State> &from, std::string eventType, const std::shared_ptr<State> &to);
    void setStartState(std::shared_ptr<State> state);
    void run();

    protected:
    void makeTransition(const std::string &eventType);
    void chooseCurrentState(std::shared_ptr<State> state);

    std::unordered_map<TransitionTableKey, std::shared_ptr<State>> transitionTable_;
    std::shared_ptr<State> currentState_;
};

#endif