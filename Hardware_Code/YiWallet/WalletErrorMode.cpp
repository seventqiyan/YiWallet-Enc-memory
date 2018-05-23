/**************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file WalletErrorMode.cpp
 *
 * @brief:
 *     系统错误模式实现。
 *
 * @author Zhaingbo zhaingbo@foxmail.com
 * @date 21.05.2018
 *
 *************************************************************************/
#include "Wallet.h"
#include <EEPROM.h>

status_t Wallet::errorMode(void)
{
    if (_prompt) {
        _prompt = false;
        if (EEPROM[PRM_ADDR_SYS_ERRCNT] == PASSWD_TRY_LIMITS) {
            Serial.println(F("This equipment has been locked because the password error times was over limits!"));
            Serial.println(F("Follow the reference guide to unlock the device. !\n"));
        } else {
            EEPROM.write(PRM_ADDR_SYS_STATE, WS_NORMAL_USE);
            Serial.println(F("System is locked, you can replug the device to try again."));
        }
    }
    return OK;
}

status_t Wallet::systemOver(void)
{
    if (_prompt) {
        _prompt = false;
        Serial.println(F("\n\n<<<<<<<<<<<<    Thanks for you using!    >>>>>>>>>>>>"));
    }
    return OK;
}
