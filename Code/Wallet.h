/**
 * Project Untitled
 */


#ifndef _WALLET_H_
#define _WALLET_H_

#include "AES.h"
#include "BtcCash.h"
#include "PassWord.h"
#include "UID.h"

#define TRIAL_ERROR_TIMES         (3)
#define RECV_BUF_SIZE             (128)

// 系统参数EEPROM地址定义
#define PRM_ADDR_SYS_STATE        (0x00)
#define PRM_ADDR_SYS_ERRCNT       (0x03)
#define PRM_ADDR_PASSWD           (0x10)
#define PRM_ADDR_PASSWD_SHADOW    (0x20)
#define PRM_ADDR_BCC0_0           (0x60)
#define PRM_ADDR_BCC0_1           (0xC0)
#define PRM_ADDR_BCC0_2           (0x120)

enum status_t {
    ERR_OK = 0,
    OK = ERR_OK,
    ERR_DEFAULT = 1,
    NO_ERROR = ERR_DEFAULT,
    ERROR,

    ERR_UID_ERROR_BASE = 0x10,
    ERR_UID_ERROR = ERR_UID_ERROR_BASE,
    ERR_PIN_ERROR,

    ERR_INIT_PASSWD_ERRO_BASE = 0x20,
    ERR_PASSWD_DIFF = ERR_INIT_PASSWD_ERRO_BASE,

    ERR_INIT_BCC_INFO_BASE = 0x30,

    ERR_NORMAL_USE_BASE = 0x40,
    ERR_NORMAL_PASSWD_ERR,
    ERR_NORMAL_ERR_OVER_LIMIT,

    ERR_UNKOWN_STATUS = 0xFF
};

class Wallet {
public:
    enum EWState_t{
        WS_CHK_UID_PIN = 0,
        WS_INIT_PASSWD,
        WS_INIT_BCC,
        WS_NORMAL_USE,
        WS_OVER,
        WS_ERROR,
        WS_RECOVER,
        WS_MAX,
    };

public: 
    Wallet(void);
    ~Wallet(void);

    void execute(void);
    void readSerial(void);
    void waitFnKeyPress(int waitDly);
    void printRecoverMenu();

    status_t checkUID(void);
    status_t initPassword(void);
    status_t initBccInfo(void);
    status_t normalMode(void);
    status_t errorMode(void);
    status_t recoverMode(void);
    status_t systemOver(void);

private:
    void prompt(const char* const msg[]);
    void setState(EWState_t state);
    void setStep(uint8_t step);
    void resetTrailErrorTimes(void);
    void incTrailErrorTimes(void);

    uint8_t getUserChoice();

    bool checkUID(uint16_t stateTrue, uint16_t stateFalse);
    bool checkPIN(uint16_t stateTrue, uint16_t stateFalse);

    bool getUID();
    bool getPIN();
    bool getPassword(PassWord &pw);
    bool checkPassword();

private:
    AES          _aes;

    EWState_t   _state;
    BitCoinCash _btc;
    PassWord    _pw;
    PassWord    _pwShadow;

    uint16_t    _step;
    bool        _prompt;
    uint8_t     _trails;
    bool        _destory_bcc;

    uint8_t     _recv[RECV_BUF_SIZE];
    uint8_t     _rlen;
};

#endif  /* end of include guard: _WALLET_H_ */