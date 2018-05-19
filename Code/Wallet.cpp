/**
 * Project Untitled
 */


#include "Wallet.h"
#include "Utils.h"
#include <EEPROM.h>
#include <avr/pgmspace.h>

#define buttonPin                 (2)

/**
 * Wallet implementation
 */
Wallet::Wallet(void)
    : _btc(_aes)
{
    _step = 0;
    _prompt = true;
    _trails = 0;
    _rlen = 0;
    initSystemParam();
}

Wallet::~Wallet(void)
{

}

void Wallet::prompt(const char* const msg[])
{
    if (_prompt) {
        char buffer[RECV_BUF_SIZE] = "\0";
        strcpy_P(buffer, (char*)pgm_read_word(&(msg[_step])));
        Serial.println(buffer);
        Serial.flush();
        _prompt = false;
    }
}

void Wallet::setStep(uint8_t step)
{
    _step   = step;
    _prompt = true;
    _rlen   = 0;
}

void Wallet::setState(EWState_t state)
{
    _state = state;
    if (_state != WS_INIT_PASSWD && _state != WS_OVER && _state != WS_RECOVER) {
        EEPROM.write(PRM_ADDR_SYS_STATE, _state);
    }

    setStep(0);
}

void Wallet::readSerial(void)
{
    if (Serial.available()) {
        _rlen += Serial.readBytes(_recv+_rlen, RECV_BUF_SIZE-_rlen);
    }
}

void Wallet::initSystemParam(void)
{
    // EEPROM.write(PRM_ADDR_SYS_STATE, WS_CHK_UID_PIN);
    _state = (EWState_t)(EEPROM.read(PRM_ADDR_SYS_STATE));
    if (_state != WS_INIT_BCC && _state != WS_NORMAL_USE &&
        _state != WS_ERROR) {
        _state = WS_CHK_UID_PIN;
    }
    // 设置buttonPin端口为输入端口
    pinMode(buttonPin, INPUT);

    // 检查错误状态
    if (_state == WS_ERROR) {
        int counter = EEPROM.read(PRM_ADDR_SYS_ERRCNT);
        if (counter < TRIAL_ERROR_TIMES || counter == -1) {
            _state = WS_NORMAL_USE;
        }
    }

    int buttonState = digitalRead(buttonPin);
    if (buttonPin && _state == WS_ERROR) {
        _state = WS_RECOVER;
    }

    if (_state == WS_NORMAL_USE) {
        // 预加载密码密文
        for (uint8_t i = 0; i < PASSWORD_LEN; i++) {
            _pwShadow._data[i] = EEPROM.read(PRM_ADDR_PASSWD + i);
        }
        _pwShadow.setLen(PASSWORD_LEN);

        // // 预加载BCC信息密文
        // for (uint8_t i = 0; i < BCC_INFO_SIZE; i++) {
        //     _bcc.cash[i] = EEPROM.read(PRM_ADDR_BCC0_0 + i);
        // }
    }
}

void Wallet::resetTrailErrorTimes(void)
{
    _trails = 0;
    EEPROM.write(PRM_ADDR_SYS_ERRCNT, _trails);
}

void Wallet::incTrailErrorTimes(void)
{
    int counter = EEPROM.read(PRM_ADDR_SYS_ERRCNT);
    counter++;
    EEPROM.write(PRM_ADDR_SYS_ERRCNT, counter);
}

bool Wallet::getUID()
{
    if (_rlen == 2*DEV_ID_LEN) {
        uint8_t id[DEV_ID_LEN];
        Utils::instance()->strToHex(_recv, _rlen, id);
        Utils::instance()->printf("getUID()");
        Utils::instance()->dumpBuffer(id, DEV_ID_LEN);
        UID uid;
        return uid.equalID(id);
    }

    return false;
}

bool Wallet::getPIN()
{
    if (_rlen == 2*DEV_PIN_LEN) {
        uint8_t pin[DEV_PIN_LEN];
        Utils::instance()->strToHex(_recv, _rlen, pin);
        Utils::instance()->printf("getPIN()");
        Utils::instance()->dumpBuffer(pin, DEV_PIN_LEN);
        UID uid;
        return uid.equalPIN(pin);
    }

    return false;
}

bool Wallet::getPassword(PassWord &pw)
{
    if (_rlen <= PASSWORD_LEN) {
        pw.initWithUID();
        pw.setLen(_rlen);
        pw.setPassWord(_recv, _rlen);
        Utils::instance()->printf("getPassword");
        Utils::instance()->dumpBuffer(pw._data, PASSWORD_LEN);
        return true;
    }

    return false;
}

bool Wallet::checkPassword()
{
    _pwShadow.load(PRM_ADDR_PASSWD);
    _aes.initKey(_pw._data);
    _aes.decrypt(_pwShadow._data);
    Utils::instance()->printf("checkPassword");
    Utils::instance()->dumpBuffer(_pwShadow._data, PASSWORD_LEN);
    _pwShadow.setLen(_pw._len);
    if (_pw == _pwShadow) {
        resetTrailErrorTimes();
        return true;
    }
    return false;
}
