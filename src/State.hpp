#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <functional>

class State : public std::enable_shared_from_this<State>
{
    public:
    State() = default;
    State(std::string name, std::weak_ptr<State> parent = {});
    State(std::string name, std::weak_ptr<State> parent, std::vector<std::shared_ptr<State>> children, size_t defaultChild);
    std::string getName() const;
    void addChild(const std::shared_ptr<State> &state);
    void setDefaultChild(size_t childId);
    std::shared_ptr<State> getDefaultChild();
    std::weak_ptr<State> getParent();

    protected:
    std::string name_;
    std::weak_ptr<State> parent_;
    std::vector<std::shared_ptr<State>> children_;
    std::optional<size_t> defaultChild_;
    std::function<void()> onActivate_;
    std::function<void()> onDeactivate_;
};

#endif