
#ifndef _UTILS_H_
#define _UTILS_H_

#include "config.h"

class Utils
{
public:
    static Utils *instance();

    bool strToHex(const uint8_t* str, int len, uint8_t *hex);
    void getChipID(uint8_t *id, int len);
    uint8_t checkXor(uint8_t *data, size_t len);
    uint8_t checkSum(uint8_t *data, size_t len);
    void dumpBuffer(uint8_t *data, size_t len);
    uint16_t printf(const char *fmt, ...);

protected:
    Utils() {}

private:
    uint8_t charToHex(uint8_t ch);

private:
    static Utils *_utils;
};

#endif // !_UTILS_H_
