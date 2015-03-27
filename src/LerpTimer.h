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
        startTime = ofGetElapsedTimef();
        startValue = getValue();
        targetValue = value;
    }
    float getProgress() const {
        float progress = (ofGetElapsedTimef() - startTime) / duration;
        return ofClamp(progress, 0, 1);
    }
    float getValue() const {
        return ofLerp(startValue, targetValue, getProgress());
    }
    bool getDone() const {
        return (ofGetElapsedTimef() - startTime) > duration;
    }
};
