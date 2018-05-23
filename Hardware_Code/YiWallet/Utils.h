/*******************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file Utils.h
 *
 * @brief
 *     通用工具实现
 *     该类采用单例模式实现，需使用Utils::instance()->tools()来统一调用。
 * 
 * @note
 *     1. strToHex()  -- 将用户字符串转换成HEX模式
 *     2. getChipID() -- 获取设备ID
 *     3. checkXor()  -- 计算缓冲区xor值
 *     4. checnSum()  -- 计算缓冲区sum值
 *     5. dump()   -- 以HEX模式输出缓冲区内容（启用ZDEBUG有效）
 *     6. printf() -- 打印调试信息（启用ZDEBUG时有效）
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
