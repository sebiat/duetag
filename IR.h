#pragma once
namespace IR
{
	static const int IrFreq = 1024;
	static const int IrPacketLen = 24; //Bit
	struct Data
	{
		unsigned char ID : 4;
		unsigned char TeamID : 6;
		unsigned char PlayerID : 6;
		unsigned char Damage : 8;
	};
	enum TransmitState
	{
		IrHeader,
		IrData,
		IrStop,
		IrIdle,
		IrParity
	};
	static bool getParity(unsigned long x)
	{
		x = ((x >> 1) & 0x55555555) + (x & 0x55555555);
		x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
		x = ((x >> 4) & 0x0F0F0F0F) + (x & 0x0F0F0F0F);
		x = (x >> 8) + x;
		x = (x >> 16) + x;
		return (x & 0x01);
	}
}