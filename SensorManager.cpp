#include "SensorManager.h"


namespace IR
{
	namespace SensorManager
	{
		void init()							  
		{
			_irSender.init(Config::Pin::Fire);
			_sensorCnt = sizeof(Config::Pin::IrSensors) / sizeof(Config::Pin::IrSensors[0]);
			for (int i = 0; i < _sensorCnt; i++)
			{
				_sensors[i] = new Sensor(Config::Pin::IrSensors[i]);
			}
		}
		void tick()
		{
			for (int i = 0; i < _sensorCnt; i++)
				_sensors[i]->tick();
			for (int i = 0; i < _sensorCnt; i++)
				_sensors[i]->check();
		}
		void sensorRcv(QueueList<Game::Event> * aCallback)
		{
			for (int i = 0; i < _sensorCnt; i++)
			{
				while (_sensors[i]->DataAvailable())
				{
					Game::Event mEvent;
					mEvent.Data = _sensors[i]->rcv();
					mEvent.Type = Game::Hit;
					aCallback->push(mEvent);
				}
			}
		}
		//void sendShot(unsigned char aDmg, )
	}
}

