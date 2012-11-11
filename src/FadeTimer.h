#pragma once

#include "ofMain.h"
#include "Hysteresis.h"

class FadeTimer {
protected:
	enum {RISING = true, FALLING = false};
	double referenceTime, risingLength, fallingLength;
	bool direction;
public:
	FadeTimer()
	:risingLength(0)
	,fallingLength(0)
	,direction(RISING)
	,referenceTime(0) {
	}
	void setLength(double length) {
		this->risingLength = length;
		this->fallingLength = length;
	}
	void setLength(double risingLength, double fallingLength) {
		this->risingLength = risingLength;
		this->fallingLength = fallingLength;
	}
	void start() {
		double curTime = ofGetElapsedTimef();
		double state = get();
		referenceTime = curTime - state * risingLength;
		direction = RISING;
	}
	void stop() {
		double curTime = ofGetElapsedTimef();
		double state = get();
		referenceTime = curTime - (1 - state) * fallingLength;
		direction = FALLING;
	}
	void update(Hysteresis& hysteresis) {
		if(hysteresis.wasTriggered()) {
			start();
		} else if(hysteresis.wasUntriggered()) {
			stop();
		}
	}
	double get() {
		if(referenceTime > 0) {
			double base = ofGetElapsedTimef() - referenceTime;
			if(direction == FALLING) {
				base /= fallingLength;
				base = 1 - base;
			} else {
				base /= risingLength;
			}
			if(base < 0) return 0;
			if(base > 1) return 1;
			return base;
		} else {
			return 0;
		}
	}
	bool getActive() {
		return get() > 0;
	}
};