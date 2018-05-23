/**************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file WalletInitPassWord.cpp
 *
 * @brief:
 *     Wallet密码初始化逻辑实现
 *
 * @author Zhaingbo zhaingbo@foxmail.com
 * @date 21.05.2018
 *
 *************************************************************************/
#include "Wallet.h"
#include <EEPROM.h>

// 创建状态定义
#define EW_CRT_INPUT_PASSWD1      (0x00)
#define EW_CRT_INPUT_PASSWD2      (0x01)
#define EW_CRT_PASSWD_ERROR       (0x02)
#define EW_CRT_PASSWD_DIFF        (0x03)

const char initPW_prompt_0[] PROGMEM = "Please init your password (Max.16): ";
const char initPW_prompt_1[] PROGMEM = "Please init your AGAIN password: ";
const char initPW_prompt_2[] PROGMEM = "PassWord is too loooooooooooooong!!";
const char initPW_prompt_3[] PROGMEM = "Entered passwords differ from the another!";
const char* const initPW_prompt[] PROGMEM  = {
    initPW_prompt_0, initPW_prompt_1, initPW_prompt_2, initPW_prompt_3
};

status_t Wallet::initPassword()
{
    prompt(initPW_prompt);

    switch (_step) {
    case EW_CRT_INPUT_PASSWD1:
        if (_rlen) {
            if (getPassword(_pw)) {
                setStep(EW_CRT_INPUT_PASSWD2);
            } else {
                setStep(EW_CRT_PASSWD_ERROR);
            }
        }
        break;

    case EW_CRT_INPUT_PASSWD2:
        if (_rlen) {
            if (getPassword(_pwShadow) && _pw == _pwShadow) {
                _aes.initKey(_pw._data);
                _aes.encrypt(_pwShadow._data);
                _pwShadow.save(PRM_ADDR_PASSWD);
                // _pwShadow.load(PRM_ADDR_PASSWD);

                _pwShadow = _pw;
                _pw.initWithUID();
                _aes.initKey(_pw._data);
                _aes.encrypt(_pwShadow._data);
                _pwShadow.save(PRM_ADDR_PASSWD_SHADOW);
                // _pwShadow.load(PRM_ADDR_PASSWD_SHADOW);
                return OK;
            } else {
                setStep(EW_CRT_PASSWD_DIFF);
            }
        }
        break;

    case EW_CRT_PASSWD_ERROR:
        // setStep(EW_CRT_INPUT_PASSWD1);
        // break;
    case EW_CRT_PASSWD_DIFF:
        setStep(EW_CRT_INPUT_PASSWD1);
        break;
        
    default:
        break;
    }

    return ERROR;
}