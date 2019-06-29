#include "Event.hpp"

#include <exception>

std::unordered_map<std::string, std::function<std::unique_ptr<Event>(std::string, std::vector<unsigned char>)>> Event::deserializers_ = {};

Event::Event(std::string type)
    : type_(std::move(type))
{
    deserializers_.insert({type_, [](std::string type, std::vector<unsigned char> data){
        return std::make_unique<Event>(type);
    }});
}

std::string Event::getType() const
{
    return type_;
}

std::vector<unsigned char> Event::serialize()
{
    auto ret = std::vector<unsigned char>{type_.begin(), type_.end()};
    auto data = serializeImpl();
    ret.push_back(SEPARATOR_);
    ret.insert(ret.end(), data.begin(), data.end());

    return ret;
}

std::vector<unsigned char> Event::serializeImpl()
{
    return {};
}

void Event::registerDeserializer(std::function<std::unique_ptr<Event>(std::string, std::vector<unsigned char>)> fun)
{
    auto insertion = Event::deserializers_.insert_or_assign(type_, std::move(fun));
}

std::unique_ptr<Event> Event::deserialize(const std::vector<unsigned char> &data)
{
    std::string type;
    auto it = data.begin();
    for (it = data.begin(); it != data.end(); ++it) {
        if (*it == SEPARATOR_) {
            type = std::string{data.begin(), it};
            break;
        }
    }

    if (type.empty())
        throw std::runtime_error("No type in received data");

    auto search = deserializers_.find(type);
    if (search == deserializers_.end())
        throw std::runtime_error("No function to create object found.");

    return search->second(type, {it + 1, data.end()});
}

void Event::clearDeserializers()
{
    deserializers_.clear();
}