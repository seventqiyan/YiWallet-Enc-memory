
#ifndef _LED_H_
#define _LED_H_

#include <Arduino.h>

class Led
{
public:
    Led(int ledPin);
    ~Led();

    enum LedState {ON = HIGH, OFF = LOW };

    void on();
    void off();
    void toggle();
    void blink(int ms);

    LedState getState();

private:
    uint32_t _blink;
    int _led;
};

#endif /* end of include guard: _LED_H_ */
