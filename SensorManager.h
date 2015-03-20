#pragma once 
#include "Sensor.h"
#include "Sender.h"
#include "Config.h"
#include "QueueList.h"
#include "Game.h"

namespace IR
{
	namespace SensorManager
	{
		static int _sensorCnt;
		static Sensor *_sensors[16];
		static Sender _irSender;
		void init();
		void tick();
		void sensorRcv(QueueList<Game::Event> * aCallback);
	};
}

