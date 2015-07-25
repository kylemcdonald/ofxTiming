#include "ofMain.h"
#include "ofxTiming.h"

class ofApp : public ofBaseApp {
public:
    DelayTimer delayTimer;
    RateTimer rateTimer, appTimer;
    Hysteresis hysteresis;
    FadeTimer fadeTimer;
    LerpTimer lerpTimer;
    
    void setup() {
        ofBackground(0);

        // ping every second
        delayTimer.setPeriod(1);
        // wait to turn on, wait longer to turn off
        hysteresis.setDelay(1, 2);
        // fade in fast, fade out slow
        fadeTimer.setLength(1, 2);
        // lerp over one second
        lerpTimer.setDuration(1);
    }
    void update() {
        appTimer.tick();
        hysteresis.update(ofGetMousePressed());
        if(hysteresis.wasTriggered()) {
            ofLog() << "triggered";
        }
        if(hysteresis.wasUntriggered()) {
            ofLog() << "untriggered";
        }
        fadeTimer.update(hysteresis);
    }
    void draw() {
        stringstream msg;
        msg << "delayTimer: " << (delayTimer.tick() ? "ping" : "") << endl;
        msg << "appTimer: " << int(appTimer.getFrameRate()) << " fps" << endl;
        msg << "rateTimer: " << rateTimer.getFrameRate() << " fps (or Hz)" << endl;
        msg << "rateTimer: " << (60 * rateTimer.getFrameRate()) << " bpm" << endl;
        msg << "rateTimer: " << rateTimer.getPeriod() << " seconds" << endl;
        msg << "mouse: " << (ofGetMousePressed() ? "on" : "off") << endl;
        msg << "hysteresis: " << (hysteresis.get() ? "on" : "off") << endl;
        msg << "fadeTimer: " << fadeTimer.get() << endl;
        msg << "lerpTimer:"
            << " from " << lerpTimer.getStartValue()
            << " to " << lerpTimer.getTargetValue()
            << " : " << int(lerpTimer.getValue())
            << " (" << int(100*lerpTimer.getProgress()) << "%)" << endl;
        ofDrawBitmapString(msg.str(), 10, 20);
    }
    void keyPressed(int key) {
        if(key == ' ') {
            rateTimer.tick();
        }
        lerpTimer.lerpToValue(key);
    }
};
int main() {
    ofSetupOpenGL(640, 320, OF_WINDOW);
    ofRunApp(new ofApp());
}