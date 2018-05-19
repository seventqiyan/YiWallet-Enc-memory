/*******************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file Utils.cpp
 *
 * @brief:
 *     通用工具实现
 *
 * @author Zhaingbo zhaingbo@foxmail.com
 * @date 19.05.2018
 *
 ******************************************************************************/
#include "Utils.h"
#include <Arduino.h>
#include <avr/boot.h>
#include <stdarg.h>

#define UTILS_SYS_CHIP_ID_ADDR (14)
#define UTILS_SYS_CHIP_ID_LEN  (10)


Utils *Utils::_utils = new Utils;

Utils* Utils::instance()
{
    return _utils;
}

bool Utils::strToHex(const uint8_t* str, int len, uint8_t *hex)
{
    if (len % 2) {
        return false;
    }

    uint8_t t1, t2;
    for (uint8_t i = 0; i < len; i += 2) {
        t1 = charToHex(str[i]);
        t2 = charToHex(str[i+1]);
        if (t1 == 0xFF || t2 == 0xFF) {
            return false;
        }

        hex[i/2] = (t1 << 4) | t2;
    }

    return true;
}

void Utils::getChipID(uint8_t *id, int len)
{
    for (int i = 0; i < UTILS_SYS_CHIP_ID_LEN && i < len; i++) {
        id[i] = boot_signature_byte_get(i + UTILS_SYS_CHIP_ID_ADDR);
    }
}

uint8_t Utils::checkXor(uint8_t *data, int len)
{
    uint8_t _xor = 0xFF;
    for (int i = 0; i < len; i++) {
        _xor = _xor ^ data[i];
    }

    return _xor;
}

uint8_t Utils::checkSum(uint8_t *data, int len)
{
    uint8_t sum = 0;
    for (int i = 0; i < len; i++) {
        sum += data[i];
    }

    return sum;
}

uint8_t Utils::charToHex(uint8_t ch)
{
    if (ch >= '0' && ch <= '9') {
        ch = ch - '0';
    } else if (ch >= 'a' && ch <= 'f') {
        ch = ch - 'a' + 10;
    } else if (ch >= 'A' && ch <= 'F') {
        ch = ch - 'A' + 10;
    } else {
        ch = 0xFF;
    }

    return ch;
}

void Utils::dumpBuffer(uint8_t *data, int len)
{
#ifdef ZDEBUG
    for (uint8_t i = 0; i < len; i++) {
        Serial.print(data[i]/16, HEX);
        Serial.print(data[i]%16, HEX);
        // Serial.print(data[i], HEX);
        Serial.print(" ");
    }
    Serial.print("\n");
#endif
}

int Utils::printf(const char *fmt, ...)
{
    int size = 0;
#ifdef ZDEBUG
    char buf[128];
    va_list ap;

    va_start(ap, fmt);
    size = vsnprintf(buf, 128, fmt, ap);
    va_end(ap);
    Serial.print(buf);
#endif
    return size;
}
