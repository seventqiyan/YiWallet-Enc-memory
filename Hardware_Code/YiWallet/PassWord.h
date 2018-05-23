/**************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file PassWord.h
 *
 * @brief:
 *     密码类接口定义
 *
 * @author Zhaingbo zhaingbo@foxmail.com
 * @date 21.05.2018
 *
 *************************************************************************/
#ifndef _PASSWORD_H_
#define _PASSWORD_H_

#include "Config.h"

#define PASSWORD_LEN   (16)

class PassWord {
public:
    PassWord();
    void load(int addr);
    void save(int addr);

    bool setPassWord(uint8_t *data, int len);
    void setLen(int len);
    void initWithUID(void);

    uint8_t& operator [](int i);
    const uint8_t & operator[](int i) const;
    PassWord &operator = (const PassWord &);
    friend bool operator==(const PassWord &lhs, const PassWord &rhs);

    // 将Wallet设置为PassWord的友元，以便直接访问其私有数据。
    friend class Wallet;

private:
    uint8_t _len;
    uint8_t _data[PASSWORD_LEN];
};

#endif /* end of include guard: _PASSWORD_H_ */
