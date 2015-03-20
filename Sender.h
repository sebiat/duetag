#pragma once 
#include "Arduino.h"
#include "IR.h"

namespace IR
{
	extern bool getParity(unsigned long x);
	class Sender
	{
	protected:
		int _Pin;
		bool _available;
		int _id;
		int _sendPos;
		int _state;
		bool _parity;
		unsigned long _sendBuffer;
	public:
		void init(int aPin);
		void Send(unsigned long aData);
		void tick();
	};
}

