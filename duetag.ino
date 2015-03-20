#include "Sender.h"
#include "Config.h"
#include "DueTimer.h"
#include "Arduino.h"
#include "QueueList.h"
#include "SensorManager.h"
#include "Game.h"


Game::Game _currentgame;

void setup()
{
	Serial.begin(115200);
    IR::SensorManager::init();
	pinMode(Config::Pin::Trigger, INPUT_PULLUP);
	Timer1.attachInterrupt(tick).setFrequency(IR::IrFreq).start();
}

time_t _triggerDiff, _tickDiff = 0;

/*
void printData(IR::Sensor::Data *aData)
{
	Serial.print("ID: "); Serial.print(aData->ID);
	Serial.print("	TeamID: "); Serial.print(aData->TeamID);
	Serial.print("	PlayerID: "); Serial.print(aData->PlayerID);
	Serial.print("	Damage: "); Serial.println(aData->Damage);
}  */

void loop()
{
	if (digitalRead(Config::Pin::Trigger) == LOW && millis() - _triggerDiff > 100)
	{
		//_IrSender.Send(16715760);
		_triggerDiff = millis();
	}
	if (!_currentgame.Events->isEmpty())
	{
		Game::Event t = _currentgame.Events->pop();
		//printData(((IR::Sensor::Data*)t.Data));
		//Serial.println(((IR::Sensor::Data*)t.Data)->Damage);
		delete(t.Data);
	}
	IR::SensorManager::sensorRcv(_currentgame.Events);
}
void tick()
{
	IR::SensorManager::tick();
	//_IrSender.tick();
}

