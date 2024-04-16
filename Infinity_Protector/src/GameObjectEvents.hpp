#pragma once

#include "GameObject.hpp"
#include "IEvent.hpp"

namespace mmt_gd
{
class GameObjectCreateEvent final : public BasicDataEvent<GameObject::Ptr>
{
public:
    using BasicDataEvent::BasicDataEvent;  // Inherit constructor from BasicDataEvent

    /**
     * \brief m_eventType defined using GUID functionality of VS 2015.
     * Tools->Create GUID -> DEFINE_GUID -> take longest value in the beginning.
     * output:
     *
     * {DEC71435-8D92-4CA7-A3D5-FD17F9D5CC34}
     * DEFINE_GUID(<< name >> ,
     * 0xdec71435, 0x8d92, 0x4ca7, 0xa3, 0xd5, 0xfd, 0x17, 0xf9, 0xd5, 0xcc, 0x34);
     *
     * m_EventType identifies event, when we want to add it to the event bus
     */
    // Type identifier for the event
    static const EventType Type;

    // Override the getEventType function to return the event type
    EventType getEventType() override
    {
        return Type;
    }
};

// Definition of the GameObjectDestroyEvent class
class GameObjectDestroyEvent final : public BasicDataEvent<GameObject::Ptr>
{
public:
    using BasicDataEvent::BasicDataEvent;  // Inherit constructor from BasicDataEvent

    // Type identifier for the event
    static const EventType Type;

    // Override the getEventType function to return the event type
    EventType getEventType() override
    {
        return Type;
    }
};
} // namespace mmt_gd
