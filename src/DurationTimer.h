#pragma once

#include "ofMain.h"
#include "OnlineStatistics.h"

/*
 DurationTimer will keep track of how long something takes.
 This is useful for timing functions to check performance.
 Call start() and stop() to before and after the function
 that you want to time.
 */

string humanDuration(float seconds, int precision) {
    if(seconds > 60) {
        int minutes = seconds / 60;
        seconds = seconds - minutes * 60;
        return ofToString(minutes) + "m" + ofToString(seconds, precision) + "s";
    } else if(seconds > 1) {
        return ofToString(seconds, precision) + "s";
    } else if(seconds > 0.001) {
        return ofToString(seconds / 0.001, precision) + "ms";
    } else if(seconds > 1e-6) {
        return ofToString(seconds / 1e-6, precision) + "us";
    } else if(seconds > 1e-9) {
        return ofToString(seconds / 1e-9, precision) + "ns";
    }
}

class DurationTimer : public OnlineStatistics {
protected:
    float lastTime;
public:
	DurationTimer() :
    lastTime(0) {
	};
    void start() {
        lastTime = ofGetElapsedTimef();
    }
    float stop() {
        float curTime = ofGetElapsedTimef();
        float duration = curTime - lastTime;
        update(duration);
        return duration;
    }
    string getSummary(int precision=2) const {
        stringstream msg;
        msg << humanDuration(getMean(), precision);
        if(getCount() > 1) {
            msg << " +/-" << humanDuration(getStd(), precision) << " "
            << "(" << humanDuration(getMin(), precision) << " to " << humanDuration(getMax(), precision) << ") "
            << "x" << getCount();
        }
        return msg.str();
    }
};
