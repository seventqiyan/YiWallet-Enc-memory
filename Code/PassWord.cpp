
#include "PassWord.h"
#include "UID.h"
#include "Utils.h"
#include <EEPROM.h>

PassWord::PassWord()
{
    initWithUID();
    _len = 0;
}

void PassWord::load(int addr)
{
    for (size_t i = 0; i < PASSWORD_LEN; i++) {
        _data[i] = EEPROM[addr + i];
    }
}
void PassWord::save(int addr)
{
    for (size_t i = 0; i < PASSWORD_LEN; i++) {
        EEPROM[addr + i] = _data[i];
    }
}

bool PassWord::setPassWord(uint8_t *data, int len)
{
    _len = len;
    if (_len < PASSWORD_LEN) {
        initWithUID();
    }

    for (uint8_t i = 0; i < _len; i++) {
        _data[i] = data[i];
    }

}

void PassWord::setLen(int len)
{
    _len = len;
}

void PassWord::initWithUID(void)
{
    UID uid;

    uid.getID(_data);
    uid.getPIN(_data + DEV_ID_LEN);

    Utils::instance()->printf("initWithUID");
    Utils::instance()->dumpBuffer(_data, PASSWORD_LEN);    
}

uint8_t& PassWord::operator [](int i)
{
    if (i >= PASSWORD_LEN) {
        return _data[0];
    }

    return _data[i];
}

const uint8_t& PassWord::operator [](int i) const
{
    if (i >= PASSWORD_LEN) {
        return _data[0];
    }

    return _data[i];
}

PassWord& PassWord::operator=(const PassWord &pw)
{
    _len = pw._len;
    for (uint8_t i = 0; i < PASSWORD_LEN; i++) {
        _data[i] = pw._data[i];
    }
    return *this;
}

bool operator==(const PassWord &lhs, const PassWord &rhs)
{
    // if (lhs._len == rhs._len) {
        for (uint8_t i = 0; i < PASSWORD_LEN; i++) {
            if (lhs._data[i] != rhs._data[i]) {
                return false;
            }
        }
        return true;
    // } else {
    //     return false;
    // }
}
