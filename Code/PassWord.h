
#ifndef _PASSWORD_H_
#define _PASSWORD_H_

#include "config.h"

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

    // 将Wallet设置为PassWo的友元，以便直接访问其私有数据。
    friend class Wallet;

private:
    uint8_t _len;
    uint8_t _data[PASSWORD_LEN];
};

#endif /* end of include guard: _PASSWORD_H_ */
