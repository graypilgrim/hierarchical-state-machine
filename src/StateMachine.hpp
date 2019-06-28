#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "State.hpp"
#include "Event.hpp"

#include <unordered_map>
#include <memory>

using TransitionTableKey = std::pair<std::shared_ptr<State>, Event>;

template <>
struct std::hash<TransitionTableKey>
{
    std::size_t operator()(const TransitionTableKey& key) const
    {
        using std::hash;
        using std::string;
        using std::shared_ptr;

        return ((hash<shared_ptr<State>>()(key.first) ^ (hash<string>()(key.second.getType()) << 1)) >> 1);
    }
};

class StateMachine
{
    public:
    StateMachine() = default;

    protected:
    std::unordered_map<TransitionTableKey, std::shared_ptr<State>> transitionTable_;
};

#endif