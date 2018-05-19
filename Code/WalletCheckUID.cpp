
#include "Wallet.h"

// 校验UID
#define EW_CID_INPUT_UID          (0x00)
#define EW_CID_INPUT_PIN          (0x01)
#define EW_CID_UID_ERROR          (0x02)
#define EW_CID_PIN_ERROR          (0x03)

const char chkUID_prompt_0[] PROGMEM = "Please Input the UID(20): ";
const char chkUID_prompt_1[] PROGMEM = "Please Input the PIN(6): ";
const char chkUID_prompt_2[] PROGMEM = "The UID is NOT match!";
const char chkUID_prompt_3[] PROGMEM = "The PIN is NOT match!";
const char* const chkUID_prompt[] PROGMEM  = {
    chkUID_prompt_0, chkUID_prompt_1, chkUID_prompt_2, chkUID_prompt_3
};

status_t Wallet::checkUID(void)
{
    prompt(chkUID_prompt);

    switch (_step) {
    case EW_CID_INPUT_UID:
        if (_rlen) {
            if (getUID()) {
                setStep(EW_CID_INPUT_PIN);
                Serial.println(F("\n**********"));
            } else {
                setStep(EW_CID_UID_ERROR);
            }
        }
        break;
    case EW_CID_INPUT_PIN:
        if (_rlen) {
            if (getPIN()) {
                Serial.println(F("\n******"));
                return OK;
            } else {
                setStep(EW_CID_PIN_ERROR);
            }
        }
        break;
    case EW_CID_UID_ERROR:
        setStep(EW_CID_INPUT_UID);
        break;
    case EW_CID_PIN_ERROR:
        setStep(EW_CID_INPUT_PIN);
        break;
    default:
        setStep(EW_CID_INPUT_UID);
        break;
    }

    return ERROR;
}

