#pragma once
#include "QueueList.h"

namespace Game
{
	enum EventType
	{
		Hit,
		Shoot
	};
	struct Event
	{
		int Type;
		void *Data;
	};
	class Game
	{
	public:
		Game();
		QueueList<Event>* Events;
	};
}
