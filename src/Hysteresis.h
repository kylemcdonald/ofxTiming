#pragma once

#include "ofMain.h"

class Hysteresis {
protected:
	unsigned long lastTime;
	bool lastValue, curValue;
	unsigned long risingDelay, fallingDelay;
	bool triggered, untriggered;
public:
	Hysteresis()
		:risingDelay(0)
		,fallingDelay(0)
		,lastTime(0)
		,lastValue(false)
		,curValue(false)
		,triggered(false)
		,untriggered(false)
	{
	}
	void setDelay(float risingDelay, float fallingDelay) {
		this->risingDelay = 1000 * risingDelay;
		this->fallingDelay = 1000 * fallingDelay;
	}
	void setDelay(float delay) {
		setDelay(delay, delay);
	}
	void update(bool value) {
		unsigned long curTime = ofGetElapsedTimeMillis();
		if(value != curValue) {
			if(value != lastValue) {
				lastTime = curTime;
			}
			unsigned long& delay = value ? risingDelay : fallingDelay;
			if(curTime - lastTime > delay) {
				curValue = value;
				if(value) {
					triggered = true;
				} else {
					untriggered = true;
				}
			}
		}
		lastValue = value;
	}
	bool get() const {
		return curValue;
	}
	bool wasTriggered() {
		if(triggered) {
			triggered = false;
			return true;
		}
		return false;
	}
	bool wasUntriggered() {
		if(untriggered) {
			untriggered = false;
			return true;
		}
		return false;
	}
	float length() const {
		return lengthMillis() / 1000.;
	}
	unsigned long lengthMillis() const {
		return ofGetElapsedTimeMillis() - lastTime;
	}
};