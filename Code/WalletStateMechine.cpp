
#include "Wallet.h"

void Wallet::execute(void)
{
    EWState_t state = _state;
    status_t  status;
    switch (_state) {
    case WS_CHK_UID_PIN:
        if (checkUID() == OK) {
            state = WS_INIT_PASSWD;
        }
        break;

    case WS_INIT_PASSWD:
        if (initPassword() == OK) {
            state = WS_INIT_BCC;
        }
        break;

    case WS_INIT_BCC:
        if (initBccInfo() == OK) {
            state = WS_NORMAL_USE;
        }
        break;

    case WS_NORMAL_USE:
        status = normalMode();
        if (status == OK) {
            state = WS_OVER;
        } else if (status == ERR_NORMAL_ERR_OVER_LIMIT) {
            state = WS_ERROR;
        }
        break;

    case WS_OVER:
        systemOver();
        break;

    case WS_ERROR:
        errorMode();
        state = WS_OVER;
        break;

    case WS_RECOVER:
        if (recoverMode() == OK) {
            state = WS_NORMAL_USE;
        }
        break;

    default:
        break;
    }

    if (state != _state) {
        setState(state);
    }
}
