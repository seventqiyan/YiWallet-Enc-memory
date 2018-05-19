/**************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file WalletRecoverMode.cpp
 *
 * @brief:
 *     系统维护模式实现
 *
 * @author Zhaingbo zhaingbo@foxmail.com
 * @date 19.05.2018
 *
 *************************************************************************/
#include "Wallet.h"

// 定义系统恢复模式子状态
enum rec_state_t {
    EW_MTC_PRINT_RECOER_MENU = 0,
    EW_MTC_RECOVER_PASSWD,
    EW_MTC_RESET_PASSWD,
    EW_MTC_DESTORY_BCC,
    EW_MTC_CHK_UID,
    EW_MTC_CHK_PIN,
    EW_MTC_ERR_UID,
    EW_MTC_ERR_PIN,
    EW_MTC_OVER
};

const char mtcPrompt_0[] PROGMEM = "";
const char mtcPrompt_1[] PROGMEM = "1. RETRIEVE PASSWD";
const char mtcPrompt_2[] PROGMEM = "2. CHANGE password is not support.";
const char mtcPrompt_3[] PROGMEM = "3. DESTORY BCC";
const char mtcPrompt_4[] PROGMEM = "Please Input the UID(20): ";
const char mtcPrompt_5[] PROGMEM = "Please Input the PIN(6): ";
const char mtcPrompt_6[] PROGMEM = "The UID is NOT match!";
const char mtcPrompt_7[] PROGMEM = "The PIN is NOT match!";
const char mtcPrompt_8[] PROGMEM = "Device Maintaince over.";
const char* const mtcPrompt[] PROGMEM  = {
    mtcPrompt_0, mtcPrompt_1, mtcPrompt_2, mtcPrompt_3, mtcPrompt_4, mtcPrompt_5, mtcPrompt_6, mtcPrompt_7, mtcPrompt_8
};


status_t Wallet::recoverMode(void)
{
    prompt(mtcPrompt);
    
    switch (_step) {
    case EW_MTC_PRINT_RECOER_MENU: {
        printRecoverMenu();
        uint8_t choice = getUserChoice();
        if (_step != choice && choice < EW_MTC_DESTORY_BCC+1) {
            setStep(choice);
        }
    }
        break;

    case EW_MTC_RECOVER_PASSWD:
        setStep(EW_MTC_CHK_UID);
        break;

    case EW_MTC_RESET_PASSWD:
        setStep(EW_MTC_OVER);
        break;

    case EW_MTC_DESTORY_BCC:
        _destory_bcc = true;
        setStep(EW_MTC_CHK_UID);
        break;

    case EW_MTC_CHK_UID:
        checkUID(EW_MTC_CHK_PIN, EW_MTC_ERR_UID);
        break;

    case EW_MTC_CHK_PIN:
        if (checkPIN(EW_MTC_OVER, EW_MTC_ERR_PIN)) {
            if (_destory_bcc) {
                setState(WS_INIT_BCC);
            } else {
                _pw.initWithUID();
                _pwShadow.load(PRM_ADDR_PASSWD_SHADOW);
                _aes.initKey(_pw._data);
                _aes.decrypt(_pwShadow._data);

                char c;
                Serial.println(F("Your password is: "));
                for (int i = 0; i < PASSWORD_LEN; i++) {
                    if (_pw[i] == _pwShadow[i]) {
                        break;
                    }
                    c = _pwShadow[i];
                    Serial.print(c);
                }
                Serial.println("\n");
                setState(WS_NORMAL_USE);
                resetTrailErrorTimes();
            }
            return OK;
        }
        break;

    case EW_MTC_ERR_UID:
        setStep(EW_MTC_CHK_UID);
        break;

    case EW_MTC_ERR_PIN:
        setStep(EW_MTC_CHK_PIN);
        break;

    case EW_MTC_OVER:
        return OK;
        break;
    default:
        break;
    }


    return NO_ERROR;
}

void Wallet::printRecoverMenu()
{
    if (_prompt && _state == WS_RECOVER) {
        Serial.println(F("===================================================="));
        Serial.println(F("1. retrieve password."));
        Serial.println(F("2. change password."));
        Serial.println(F("3. destory BCC INFO."));
        // Serial.println(F("4. FORMAT device."));
        Serial.println(F("===================================================="));
        Serial.println(F(""));
        // _prompt = false;
    }
}

uint8_t Wallet::getUserChoice()
{
    uint8_t choice = 0xFF;
    if (_rlen == 1) {
        if (_recv[0] > '0' && _recv[0] < '4') {
            choice = _recv[0] - '0';
            return choice;
        }
    } else if (_rlen) {
        choice = EW_MTC_PRINT_RECOER_MENU;
    }

    return choice;
}
