/**************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file Led.h
 *
 * @brief:
 *     LED驱动接口
 *
 * @author Zhaingbo zhaingbo@foxmail.com
 * @date 19.05.2018
 *
 *************************************************************************/
#ifndef _LED_H_
#define _LED_H_

#include "Config.h"

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
