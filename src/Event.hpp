#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include <string>

class Event
{
    public:
    Event() = default;
    Event(std::string type);
    std::string getType() const;
    std::vector<unsigned char> serialize();

    protected:
    virtual std::vector<unsigned char> serializeImpl();

    std::string type_;
    static const char SEPARATOR_ = ';';

};

#endif