#include "Sensor.h"
#include "SensorManager.h"

namespace IR
{
	Sensor::Sensor(int aPin)
	{
		_rcvQueue = new QueueList<unsigned long>();
		_headerStart = false;
		_bufferOffset = 0;
		_bufferPos = 0;
		_pin = aPin;
		_state = IrHeader;
		pinMode(_pin, INPUT_PULLUP);
	}
	void Sensor::tick()
	{
		_pinState = !digitalRead(_pin);
	}
	void Sensor::check()
	{
		switch (_state)
		{
		case IrHeader:
			if (_pinState)
			{
				_state = IrData;
				_bufferPos = 0;
				_buffer[_bufferOffset] = 0;
			}
			break;
		case IrData:
			bitWrite(_buffer[_bufferOffset], _bufferPos, _pinState);
			_bufferPos++;
			if (_bufferPos >= IrPacketLen) _state = IrStop;
			break;
		case IrStop:
			if (_pinState)
			{
				_rcvQueue->push(_buffer[_bufferOffset]);
			}
			_state = IrHeader;
			_bufferOffset++;
			if (_bufferOffset >= 4) _bufferOffset = 0;
			break;
		}
		/*
		_state = !digitalRead(_pin);
		if (_state && !_headerStart)
		{
			_headerStart = true;
			_bufferPos = 0;
			_buffer[_bufferOffset] = 0;
			return;
		}
		if (_headerStart)
		{
			if (_bufferPos < PacketLen)
			{
				bitWrite(_buffer[_bufferOffset], _bufferPos, _state);
				_bufferPos++;
			}
			else
			{
				_headerStart = false;
				Serial.println(_buffer[_bufferOffset]);
				_bufferOffset++;
				if (_bufferOffset >= 4) _bufferOffset = 0;
			}
		}
		*/
	}
	bool Sensor::DataAvailable()
	{
		return !_rcvQueue->isEmpty();
	}
	IR::Data * Sensor::rcv()
	{
		unsigned long data = _rcvQueue->pop();
		Data *tmp = new Data();
		tmp->ID = (data >> 20) & 0x0F;
		tmp->TeamID = (data >> 14) & 0x3F;
		tmp->PlayerID = (data >> 8) & 0x3F;
		tmp->Damage = data & 0xFF;
		return tmp;
	}
}


