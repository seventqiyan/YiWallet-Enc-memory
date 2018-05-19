
#define _LED_C_
#include "Led.h"

Led::Led(int ledPin)
    : _led(ledPin)
{
    pinMode(_led, OUTPUT);
}

Led::~Led()
{

}

void Led::on()
{
    digitalWrite(_led, HIGH);
}

void Led::off()
{
    digitalWrite(_led, LOW);
}

void Led::toggle()
{
    if (getState() == ON) {
        off();
    } else {
        on();
    }
}

void Led::blink(int ms)
{
    uint32_t blink = millis() / ms;
    if (blink != _blink) {
        toggle();
        _blink = blink;
    }
}

Led::LedState Led::getState()
{
    return digitalRead(_led);
}
