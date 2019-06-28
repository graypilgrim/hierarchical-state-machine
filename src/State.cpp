#include "State.hpp"

#include <cassert>

State::State(std::string name, std::weak_ptr<State> parent)
    : name_(std::move(name)), parent_(std::move(parent))
{}

State::State(std::string name, std::weak_ptr<State> parent, std::vector<std::shared_ptr<State>> children, size_t defaultChild)
    : name_(std::move(name)), parent_(std::move(parent)), children_(std::move(children)), defaultChild_(defaultChild)
{}

std::string State::getName() const
{
    return name_;
}

void State::addChild(const std::shared_ptr<State> &state)
{
    children_.push_back(state);
}

void State::setDefaultChild(size_t childId)
{
    defaultChild_ = childId;
}

std::shared_ptr<State> State::getDefaultChild()
{
    if (children_.empty())
        return shared_from_this();

    assert(!children_.empty() && defaultChild_.has_value());

    return children_[defaultChild_.value()]->getDefaultChild();
}

std::weak_ptr<State> State::getParent()
{
    return parent_;
}

void State::activate()
{
    if (onActivate_) onActivate_();
}

void State::deactivate()
{
    if (onDeactivate_) onDeactivate_();
}