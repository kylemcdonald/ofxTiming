#pragma once

#include "ofMain.h"

class Hysteresis {
protected:
	uint64_t lastTime;
	bool lastValue, curValue;
	uint64_t risingDelay, fallingDelay;
	bool triggered, untriggered;
    
    void resetTriggers() {
        triggered = false;
        untriggered = false;
    }
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
	bool update(bool value) {
        resetTriggers();
		uint64_t curTime = ofGetElapsedTimeMillis();
        if(value != curValue) {
            if(value != lastValue) {
				lastTime = curTime;
			}
            uint64_t& delay = value ? risingDelay : fallingDelay;
			if(curTime > delay + lastTime) {
				curValue = value;
				if(value) {
					triggered = true;
				} else {
					untriggered = true;
				}
			}
		}
		lastValue = value;
        return get();
	}
    bool set(bool value) {
        resetTriggers();
        if(value != curValue) {
            if(value) {
                triggered = true;
            } else {
                untriggered = true;
            }
        }
        curValue = value;
        lastValue = value;
        lastTime = ofGetElapsedTimeMillis();
        return get();
    }
	bool get() const {
		return curValue;
	}
	bool wasTriggered() const {
        return triggered;
	}
	bool wasUntriggered() const {
        return untriggered;
	}
	float length() const {
		return lengthMillis() / 1000.;
	}
	uint64_t lengthMillis() const {
		return ofGetElapsedTimeMillis() - lastTime;
	}
};