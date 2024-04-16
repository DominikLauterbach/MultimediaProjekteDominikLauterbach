#pragma once

#include <memory>

namespace mmt_gd
{
class IEvent
{
public:
    IEvent()                                 = default; // Default constructor
    virtual ~IEvent()                        = default; // Default destructor
    IEvent(const IEvent& other)              = delete;  // Copy constructor (deleted)
    IEvent(const IEvent&& other)             = delete;  // Move constructor (deleted)
    IEvent&  operator=(const IEvent& other)  = delete;  // Copy assignment operator (deleted)
    IEvent&& operator=(const IEvent&& other) = delete;  // Move assignment operator (deleted)


    using EventType = unsigned long;           // Alias for event type
    using Ptr       = std::shared_ptr<IEvent>; // Shared pointer alias for events

    virtual EventType getEventType() = 0; // Pure virtual function to get event type
};
// Template class for events carrying basic data
template <typename T>
class BasicDataEvent : public IEvent
{
public:
    // Constructor taking data as a parameter
    explicit BasicDataEvent(T data) : m_data(std::move(data))
    {
    }

    ~BasicDataEvent() override                               = default; // Default destructor
    BasicDataEvent(const BasicDataEvent& other)              = delete;  // Copy constructor (deleted)
    BasicDataEvent(const BasicDataEvent&& other)             = delete;  // Move constructor (deleted)
    BasicDataEvent&  operator=(const BasicDataEvent& other)  = delete;  // Copy assignment operator (deleted)
    BasicDataEvent&& operator=(const BasicDataEvent&& other) = delete;  // Move assignment operator (deleted)

    // Getter method to retrieve the stored data
    T getData()
    {
        return m_data; // Member variable to store data
    }

private:
    T m_data;
};
} // namespace mmt_gd
