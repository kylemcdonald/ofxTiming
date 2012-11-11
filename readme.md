# ofxTiming is an addon for [openFrameworks](http://openframeworks.cc)

ofxTiming provides classes that implement common patterns associated with timing.

## DelayTimer

An asynchronous buffered intervalometer that will accept a framerate, and return a true `tick()` when it's time to execute an event associated with that interval.

## FadeTimer

A class that returns a state between 0 and 1 that will fade from one end to the other given `start()` or `stop()`, correctly handling intermediate cases.

## Hysteresis

A class for filtering and tracking noisy input. This also plugs into `FadeTimer`.

## RateTimer

A class for timing framerates or intervals of time.