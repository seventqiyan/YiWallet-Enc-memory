
#include "Wallet.h"
#include <EEPROM.h>

// 校验状态定义
#define EW_NRM_INPUT_PASSWD       (0x00)
#define EW_NRM_OUTPUT_BIT_INFO    (0x01)
#define EW_NRM_PASSWD_ERROR       (0x02)
#define EW_NRM_OVER               (0x03)

const char normal_prompt_0[] PROGMEM = "Please Input your password: ";
const char normal_prompt_1[] PROGMEM = "\nBTC Cash Info: ";
const char normal_prompt_2[] PROGMEM = "WARRING! Warring!! Warring!!!\nWRONG password!";
const char* const normal_prompt[] PROGMEM = {
    normal_prompt_0, normal_prompt_1, normal_prompt_2
};

status_t Wallet::normalMode()
{
    prompt(normal_prompt);

    int addr, size;
    switch (_step) {
    case EW_NRM_INPUT_PASSWD:
        if (_rlen > 0) {
            if (getPassword(_pw)) {
                if (checkPassword()) {
                    resetTrailErrorTimes();
                    setStep(EW_NRM_OUTPUT_BIT_INFO);
                } else {
                    setStep(EW_NRM_PASSWD_ERROR);
                }
            }  else {
                setStep(EW_NRM_PASSWD_ERROR);
            }
        }
        break;
    case EW_NRM_OUTPUT_BIT_INFO:
        // _aes.initKey(_pw._data);
        // _aes.decrypt(_bcc.cash, BCC_INFO_SIZE);
        _btc.load(PRM_ADDR_BCC0_0);
        _btc.decryptBCC(_pw._data);
        _btc.output();
        return OK;
        break;
    case EW_NRM_PASSWD_ERROR:
        if (++_trails == PASSWD_TRY_LIMITS) {
            incTrailErrorTimes();
            Serial.println(F("The number of password errors exceeds the limit."));
            return ERR_NORMAL_ERR_OVER_LIMIT;
        }
        setStep(EW_NRM_INPUT_PASSWD);
        break;
    default:
        // _pw.initWithUID();
        // _pwShadow.load(PRM_ADDR_PASSWD);
        // _step = EW_NRM_INPUT_PASSWD;
        break;
    }

    return NO_ERROR;
}
