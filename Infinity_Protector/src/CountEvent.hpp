#pragma once

#include "IEvent.hpp"

namespace mmt_gd
{
class CountEvent : public BasicDataEvent<int>
{
public:
	CountEvent(int count) : BasicDataEvent(count)
	{
	}
	using BasicDataEvent::BasicDataEvent;

	static const EventType type;

	EventType getEventType() override
	{
		return type;
	}
};

}
