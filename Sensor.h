#pragma once 
#include "Arduino.h"
#include "IR.h"
#include "QueueList.h"

namespace IR
{
	class Sensor
	{
	private:
		QueueList<unsigned long> * _rcvQueue;
		int _pin;
		bool _headerStart;
		int _state;
		bool _pinState;
		int _bufferPos, _bufferOffset;
		unsigned long _buffer[5];
	public:
		Sensor(int aPin);
		void tick();
		void check();
		bool DataAvailable();
		Data * rcv();
	};
}
