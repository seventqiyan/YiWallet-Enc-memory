/*******************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file YiWallet.ino
 * __   _____        __    _ _      _   
 * \ \ / (_) \      / /_ _| | | ___| |_ 
 *  \ V /| |\ \ /\ / / _` | | |/ _ \ __|
 *   | | | | \ V  V / (_| | | |  __/ |_ 
 *   |_| |_|  \_/\_/ \__,_|_|_|\___|\__|
 *
 * @brief:
 *     易钱包主框架实现。
 *
 * @author Zhaingbo zhaingbo@foxmail.com
 * @date 19.05.2018
 *
 ******************************************************************************/
#include "Wallet.h"
#include "Led.h"
#include "Key.h"

Wallet wallet;
Led    led(LED_STATUS_PIN);

void setup() {
    led.on();
    Serial.begin(115200);
    while (!Serial);
    wallet.waitFnKeyPress(SYS_BOOT_DELAY_TM);
    wallet_logo();
    wallet.printRecoverMenu();
}

void loop()
{
    wallet.execute();
    wallet.readSerial();
    led.blink(300);
}

// 打印系统Logo
void wallet_logo()
{
    Serial.println(F("===================================================="));
    Serial.println(F("=       __   _____        __    _ _      _         ="));
    Serial.println(F("=       \\ \\ / (_) \\      / /_ _| | | ___| |_       ="));
    Serial.println(F("=        \\ V /| |\\ \\ /\\ / / _` | | |/ _ \\ __|      ="));
    Serial.println(F("=         | | | | \\ V  V / (_| | | |  __/ |_       ="));
    Serial.println(F("=         |_| |_|  \\_/\\_/ \\__,_|_|_|\\___|\\__|      ="));
    Serial.println(F("=                                                  ="));
    Serial.println(F("================ YiWallet (ver 0.6) ================"));
    Serial.println(F(""));
}
