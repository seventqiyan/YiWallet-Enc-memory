
#ifndef _BTC_CASH_
#define _BTC_CASH_

#include "AES.h"

typedef unsigned char uint8_t;
typedef unsigned long uint32_t;

#define BTC_CASH_SIZE    (42)
#define BTC_PVTKEY_SIZE  (52)
#define BCC_SIZE         (BTC_CASH_SIZE + BTC_PVTKEY_SIZE)
#define BCC_INFO_SIZE    (BCC_SIZE+2)

typedef union bcc_t {
    struct {
        uint8_t  cash[BTC_CASH_SIZE];
        uint8_t  pvt[BTC_PVTKEY_SIZE];
        uint8_t  xor1;
        uint8_t  xor2;
    };
    uint8_t data[BCC_INFO_SIZE];
} bcc_t;

/**
    bitcoincash:
    qrlaq6kv42vhraqcwhj8hsnflgdwpr8frgy2t9gsf9
    private key:
    KwQKjoScnjvwQW7C9qXiFctwY8o93Souy73i15gLM4gXkdQe4uWo
 */

class BitCoinCash
{
public:
    BitCoinCash(AES &aes);

    void load(int addr);
    void save(int addr);
    void output();

    bool setBccAddr(uint8_t *addr, int len);
    bool setBccPvt(uint8_t *pvt, int len);
    void getBccAddr(uint8_t *addr);
    void getBccPvt(uint8_t *pvt);

    uint32_t calcBccChkFlag(void);
    void encryptBCC(uint8_t *key);
    void decryptBCC(uint8_t *key);

private:
    AES &_aes;
    bcc_t _bcc;
};

#endif // !_BTC_CASH_
