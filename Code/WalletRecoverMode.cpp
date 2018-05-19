
#include "Wallet.h"

// 创建状态定义
#define EW_RECOVER_PRINT_RECOER_MENU  (0x00)
#define EW_RECOVER_RECOVER_PASSWD     (0x01)
#define EW_RECOVER_RESET_PASSWD       (0x02)
#define EW_RECOVER_DESTORY_BCC        (0x03)

status_t Wallet::recoverMode(void)
{
    _step = getUserChoice();
    switch (_step)
    {
    case EW_RECOVER_PRINT_RECOER_MENU:
        printRecoverMenu();
        break;
    case EW_RECOVER_RECOVER_PASSWD:
        break;
    case EW_RECOVER_RESET_PASSWD:
        break;
    case EW_RECOVER_DESTORY_BCC:
        break;
    default:
        break;
    }
    return ERROR;
}

void Wallet::printRecoverMenu()
{
    Serial.println(F("1. RECOVER the password."));
    Serial.println(F("2. RESET the password."));
    Serial.println(F("3. DESTORY the BCC INFO."));
    // Serial.println(F("4. FORMAT the device."));
    Serial.println(F(""));
    _prompt = true;
}

uint8_t Wallet::getUserChoice()
{
    uint8_t choice = 0xFF;
    if (_rlen == 1) {
        if (_recv[0] > '1' && _recv[0] < '4') {
            choice = _recv[0] - '0';
            return choice;
        }
    } else if (_rlen) {
        choice = 0;
    }

    return choice;
}
