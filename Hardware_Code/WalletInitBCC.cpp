
#include "Wallet.h"
#include <EEPROM.h>

#define EW_INIT_INPUT_PASSWD1     (0x00)
#define EW_INIT_BCC_ADDR          (0x01)
#define EW_INIT_PRIVATE_KEY       (0x02)
#define EW_INIT_OK                (0x03)
#define EW_INIT_PASSWD_DIFF       (0x04)

const char initBCC_prompt_0[] PROGMEM = "Please Input your password(Init): ";
const char initBCC_prompt_1[] PROGMEM = "Please input your bitcoin_cash(42): ";
const char initBCC_prompt_2[] PROGMEM = "Please input your private key(52): ";
const char initBCC_prompt_3[] PROGMEM = "System Init OK!!!";
const char initBCC_prompt_4[] PROGMEM = "WARRING! Warring!! Warring!!!\nWRONG password!";

const char* const initBCC_prompt[] PROGMEM = {
    initBCC_prompt_0, initBCC_prompt_1, initBCC_prompt_2, initBCC_prompt_3, initBCC_prompt_4
};

status_t Wallet::initBccInfo()
{
    prompt(initBCC_prompt);

    switch (_step) {
    case EW_INIT_INPUT_PASSWD1:
        if (_rlen && getPassword(_pw)) {
            if (checkPassword()) {
                setStep(EW_INIT_BCC_ADDR);
            } else {
                setStep(EW_INIT_PASSWD_DIFF);
            }
        }
        break;
    case EW_INIT_BCC_ADDR:
        if (_rlen == BTC_CASH_SIZE) {
            _btc.setBccAddr(_recv, _rlen);
            setStep(EW_INIT_PRIVATE_KEY);
        } else if (_rlen) {
            Serial.println(F("bitcoin_cash is INVALID!"));
            setStep(EW_INIT_BCC_ADDR);
        }
        break;

    case EW_INIT_PRIVATE_KEY:
        if (_rlen == BTC_PVTKEY_SIZE) {
            _btc.setBccPvt(_recv, _rlen);
            _btc.encryptBCC(_pw._data);

            _btc.save(PRM_ADDR_BCC0_0);
            _btc.save(PRM_ADDR_BCC0_1);
            _btc.save(PRM_ADDR_BCC0_2);
            setStep(EW_INIT_OK);;
        } else if (_rlen) {
            Serial.println(F("Private Key is INVALID!"));
            setStep(EW_INIT_PRIVATE_KEY);
        }
        break;
    case EW_INIT_OK:
        return OK;
        break;
    case EW_INIT_PASSWD_DIFF:
        setStep(EW_INIT_INPUT_PASSWD1);
        break;
    }
    return ERROR;
}