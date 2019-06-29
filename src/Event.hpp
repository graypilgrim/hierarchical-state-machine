#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

class Event
{
    public:
    Event() = default;
    Event(std::string type);
    std::string getType() const;
    std::vector<unsigned char> serialize();
    void registerDeserializer(std::function<std::unique_ptr<Event>(std::string, std::vector<unsigned char>)> fun);
    static std::unique_ptr<Event> deserialize(const std::vector<unsigned char> &data);
    static void clearDeserializers();

    protected:
    virtual std::vector<unsigned char> serializeImpl();

    const std::string type_;
    static const char SEPARATOR_ = ';';
    static std::unordered_map<std::string, std::function<std::unique_ptr<Event>(std::string, std::vector<unsigned char>)>> deserializers_;
};

#endif