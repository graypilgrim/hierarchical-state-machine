#include "Event.hpp"

Event::Event(std::string type)
    : type_(std::move(type))
{}

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