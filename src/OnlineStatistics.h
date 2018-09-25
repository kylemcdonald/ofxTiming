#pragma once

#include "ofMain.h"

/*
 This class helps measure running statistics like mean
 and variance for DurationTimer.
 */

class OnlineStatistics {
protected:
    long count;
    double mean, m2;
    double min, max;
public:
    OnlineStatistics() :
    count(0),
    mean(0),
    m2(0),
    min(0),
    max(0) {
    }
    void update(float x) {
        if (x < min) min = x;
        if (x > max) max = x;
        
        if (count == 0) {
            mean = x;
            min = x;
            max = x;
        }
        
        // wellford's algorithm
        count++;
        double delta = x - mean;
        mean += delta / count;
        double delta2 = x - mean;
        m2 += delta * delta2;
    }
    long getCount() const {
        return count;
    }
    double getMean() const {
        return mean;
    }
    double getVariance() const {
        return m2 / count;
    }
    double getStd() const {
        return sqrt(getVariance());
    }
    double getMin() const {
        return min;
    }
    double getMax() const {
        return max;
    }
};
