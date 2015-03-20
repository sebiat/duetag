#include "Sender.h"

namespace IR
{
	void Sender::init(int aPin)
	{
		_Pin = aPin;
		pinMode(_Pin, OUTPUT);
		digitalWrite(_Pin, LOW);
	}
	void Sender::tick()
	{
		if (!_available)   
		{
			switch (_state)
				digitalWrite(_Pin, HIGH);
				_state = IrData;
				_sendPos = 0;
				break;
				digitalWrite(_Pin, bitRead(_sendBuffer, _sendPos));
				_sendPos++;
				if (_sendPos >= IrPacketLen)
					_state = IrParity;
				break;
				digitalWrite(_Pin, _parity);
				_state = IrStop;
				break;
				digitalWrite(_Pin, HIGH);
				_state = IrIdle;
				break;
				digitalWrite(_Pin, LOW);
				_state = IrHeader;
				_available = true;
				break;
		}
	}
	void Sender::Send(unsigned long aData)
	{
		if (_available)
		{
			_available = false;
			_sendBuffer = aData;
			_parity = !getParity(aData);
		}
	}
}