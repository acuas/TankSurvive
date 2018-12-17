#include "stdlib.h"
#include "Arduino.h"

#ifndef TIMER_H
#define TIMER_H
typedef void (*CallBackType)();


class Timer{
private:
	void Create(unsigned long int ms, CallBackType callback, bool isSingle);
	unsigned long int msInterval;
	bool blEnabled;
	bool blSingleShot;
	CallBackType onRun;
	unsigned long LastTime;
	unsigned long DiffTime;//used when I pause the Timer and need to resume

public:
	Timer(unsigned long int ms);
	Timer(unsigned long int ms, CallBackType callback);
	Timer(unsigned long int ms, CallBackType callback, bool isSingle);
	~Timer();

	void setInterval(unsigned long int ms);
	void setEnabled(bool Enabled);
	void setSingleShot(bool isSingle);
	void setOnTimer(CallBackType callback);
	void Start();
	void Resume();
	void Pause();
	void Stop();
	void Update();

	bool Tick();
	unsigned long int getInterval();
	unsigned long int getCurrentTime();
	CallBackType getOnTimerCallback();

	bool isEnabled();
	bool isSingleShot();

};


#endif // TIMER_H