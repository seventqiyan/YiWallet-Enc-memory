
#include "BtcCash.h"
#include "Utils.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <string.h>

BitCoinCash::BitCoinCash(AES &aes)
    : _aes(aes)
{

}

void BitCoinCash::load(int addr)
{
    for (size_t i = 0; i < BCC_INFO_SIZE; i++) {
        _bcc.data[i] = EEPROM[addr + i];
    }
    Utils::instance()->printf("BCC load");
    Utils::instance()->dumpBuffer(_bcc.data, BCC_INFO_SIZE);
}

void BitCoinCash::save(int addr)
{
    for (size_t i = 0; i < BCC_INFO_SIZE; i++) {
        EEPROM[addr + i] = _bcc.data[i];
    }
    Utils::instance()->printf("BCC save");
    Utils::instance()->dumpBuffer(_bcc.data, BCC_INFO_SIZE);
}

void BitCoinCash::output()
{
    Serial.println(F("bitcoincash: "));
    char c;
    for (int i = 0; i < BTC_CASH_SIZE; i++) {
        c = _bcc.cash[i];
        Serial.print(c);
    }
    Serial.println(F("\nprivate Key: "));
    for (int i = 0; i < BTC_PVTKEY_SIZE; i++) {
        c = _bcc.pvt[i];
        Serial.print(c);
    }
}

bool BitCoinCash::setBccAddr(uint8_t *addr, int len)
{
    if (len == BTC_CASH_SIZE) {
        memcpy(_bcc.cash, addr, len);
        return true;
    } else {
        return false;
    }
}

bool BitCoinCash::setBccPvt(uint8_t *pvt, int len)
{
    if (len == BTC_PVTKEY_SIZE) {
        memcpy(_bcc.pvt, pvt, len);
        return true;
    } else {
        return false;
    }
    return true;
}

void BitCoinCash::getBccAddr(uint8_t *addr)
{
    memcpy(addr, _bcc.cash, BTC_CASH_SIZE);
    return true;
}

void BitCoinCash::getBccPvt(uint8_t *pvt)
{
    memcpy(pvt, _bcc.pvt, BTC_PVTKEY_SIZE);
    return true;
}

uint32_t BitCoinCash::calcBccChkFlag(void)
{
    _bcc.xor1 = Utils::instance()->checkXor(_bcc.cash, BCC_SIZE);
    _bcc.xor2 = ~_bcc.xor1;

    return 0;
}

void BitCoinCash::encryptBCC(uint8_t *key)
{
    calcBccChkFlag();
    _aes.initKey(key);
    _aes.encrypt(_bcc.cash, BCC_INFO_SIZE);
}

void BitCoinCash::decryptBCC(uint8_t *key)
{
    _aes.initKey(key);
    _aes.decrypt(_bcc.cash, BCC_INFO_SIZE);
}

