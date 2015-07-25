#pragma once

#include "ofMain.h"

class LerpTimer {
protected:
    float startTime = 0;
    float duration = 1;
    float startValue = 0;
    float targetValue = 0;
public:
    void setDuration(float duration) {
        this->duration = duration;
    }
    void setToValue(float value) {
        startTime = ofGetElapsedTimef();
        startValue = value;
        targetValue = value;
    }
    void lerpToValue(float value) {
        startValue = getValue();
        targetValue = value;
        startTime = ofGetElapsedTimef();
    }
    float getProgress() const {
        float progress = (ofGetElapsedTimef() - startTime) / duration;
        return ofClamp(progress, 0, 1);
    }
    float getStartValue() const {
        return startValue;
    }
    float getTargetValue() const {
        return targetValue;
    }
    float getValue() const {
        return ofLerp(startValue, targetValue, getProgress());
    }
    bool getDone() const {
        return getValue() == targetValue;
    }
};
