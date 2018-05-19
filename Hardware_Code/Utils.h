/*******************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file Utils.h
 *
 * @brief:
 *     通用工具实现
 *     该类采用单例模式实现，需使用Utils::instance()->tools()来统一调用
 *
 * @author Zhaingbo zhaingbo@foxmail.com
 * @date 19.05.2018
 *
 ******************************************************************************/
#ifndef _UTILS_H_
#define _UTILS_H_

#include "Config.h"

class Utils
{
public:
    static Utils *instance();

    bool strToHex(const unsigned char* str, int len, unsigned char *hex);
    void getChipID(unsigned char *id, int len);
    unsigned char checkXor(unsigned char *data, int len);
    unsigned char checkSum(unsigned char *data, int len);
    void dumpBuffer(unsigned char *data, int len);
    int printf(const char *fmt, ...);

protected:
    Utils() {}

private:
    unsigned char charToHex(unsigned char ch);

private:
    static Utils *_utils;
};

#endif // !_UTILS_H_
