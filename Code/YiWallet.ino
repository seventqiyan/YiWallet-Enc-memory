/*******************************************************************************
 * 
 * Copyright (c) 2018 
 * 
 * 易钱包 ver0.1
 * __   _____        __    _ _      _   
 * \ \ / (_) \      / /_ _| | | ___| |_ 
 *  \ V /| |\ \ /\ / / _` | | |/ _ \ __|
 *   | | | | \ V  V / (_| | | |  __/ |_ 
 *   |_| |_|  \_/\_/ \__,_|_|_|\___|\__|
 * 
 ******************************************************************************/
#include "Wallet.h"
#include "Led.h"

Wallet wallet;
Led    led(13);

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    wallet_logo();
    wallet.initSystemParam();
}

void loop()
{
    wallet.execute();
    wallet.readSerial();
    led.blink(300);
}

void wallet_logo()
{
    Serial.println(F("===================================================="));
    Serial.println(F("=       __   _____        __    _ _      _         ="));
    Serial.println(F("=       \\ \\ / (_) \\      / /_ _| | | ___| |_       ="));
    Serial.println(F("=        \\ V /| |\\ \\ /\\ / / _` | | |/ _ \\ __|      ="));
    Serial.println(F("=         | | | | \\ V  V / (_| | | |  __/ |_       ="));
    Serial.println(F("=         |_| |_|  \\_/\\_/ \\__,_|_|_|\\___|\\__|      ="));
    Serial.println(F("=                                                  ="));
    Serial.println(F("================ YiWallet (ver 0.3) ================"));
    Serial.println(F(""));
}
