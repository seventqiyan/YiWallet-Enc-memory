/*******************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file AES.h
 *
 * @brief:
 *     AES加密算法接口类定义
 *
 * @author Zhaingbo zhaingbo@foxmail.com
 * @date 19.05.2018
 *
 ******************************************************************************/
#ifndef _AES_H_
#define _AES_H_

#include "Config.h"

class AES
{
public:
    AES();
    virtual ~AES();
    void initKey(const uint8_t* key);
    uint8_t* encrypt(uint8_t* input);             // 加密，传入的数组大小必须是16字节
    uint8_t* decrypt(uint8_t* input);             // 解密，传入的数组也必须是16字节
    void* encrypt(void* input, int length = 0);   // 可以传入数组，大小必须是16的整数倍，如果不是将会越界操作；如果不传length而默认为0，那么将按照字符串处理，遇'\0'结束
    void* decrypt(void* input, int length);       // 必须传入数组和大小，必须是16的整数倍

    uint8_t w[11][4][4];
private:
    static const uint8_t Sbox[256];
    static const uint8_t InvSbox[256];
    static const uint8_t mult_2[256];             // Rijndael multiplication by 2
    static const uint8_t mult_3[256];             // Rijndael multiplication by 3
    static const uint8_t mult_9[256];             // Rijndael multiplication by 9
    static const uint8_t mult_11[256];            // Rijndael multiplication by 11
    static const uint8_t mult_13[256];            // Rijndael multiplication by 13
    static const uint8_t mult_14[256];            // Rijndael multiplication by 14

    void KeyExpansion(const uint8_t* key, uint8_t w[][4][4]);
    uint8_t FFmul(uint8_t a, uint8_t b);

    void SubBytes(uint8_t state[][4]);
    void ShiftRows(uint8_t state[][4]);
    void MixColumns(uint8_t state[][4]);
    void AddRoundKey(uint8_t state[][4], uint8_t k[][4]);

    void InvSubBytes(uint8_t state[][4]);
    void InvShiftRows(uint8_t state[][4]);
    void InvMixColumns(uint8_t state[][4]);
};

#endif    // _AES_H_
