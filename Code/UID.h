

#ifndef _UID_H_
#define _UID_H_

#include "config.h"

#define DEV_ID_LEN       (10)
#define DEV_PIN_LEN      (6)

class UID
{
public:
    UID();
    ~UID();

    // void setID(uint8_t *data);
    // void setPIN(uint8_t *data);
    void getID(uint8_t *data);
    void getPIN(uint8_t *data);

    bool equalID(const UID& uid);
    bool equalID(const uint8_t *id);
    bool equalPIN(const UID& uid);
    bool equalPIN(const uint8_t *pin);

    friend bool operator==(const UID &lhs, const UID &rhs);

private:
    void resetUID();
    void calcPIN();

public:
    uint8_t id[DEV_ID_LEN];
    uint8_t pin[DEV_PIN_LEN];
};

#endif /* end of include guard: _UID_H_ */
