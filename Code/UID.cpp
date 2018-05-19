
#define _UID_C_
#include "UID.h"
#include "Utils.h"
#include <Arduino.h>
#include <string.h>

UID::UID()
{
    resetUID();
}

UID::~UID()
{

}

// void UID::setID(uint8_t *data)
// {
//     memcpy(id, data, DEV_ID_LEN);
// }

// void UID::setPIN(uint8_t *data)
// {
//     memcpy(pin, data, DEV_PIN_LEN);
// }

void UID::getID(uint8_t *data)
{
    memcpy(data, id, DEV_ID_LEN);
}

void UID::getPIN(uint8_t *data)
{
    memcpy(data, pin, DEV_PIN_LEN);
}

bool UID::equalID(const uint8_t *id)
{
    for (int i = 0; i < DEV_ID_LEN; i++) {
        if (this->id[i] != id[i]) {
            return false;
        }
    }
    return true;
}

bool UID::equalID(const UID& uid)
{
    return equalID(uid.id);
}

bool UID::equalPIN(const uint8_t *pin)
{
    for (int i = 0; i < DEV_PIN_LEN; i++) {
        if (this->pin[i] != pin[i]) {
            return false;
        }
    }
    return true;
}

bool UID::equalPIN(const UID& uid)
{
    return equalPIN(uid.pin);
}

void UID::resetUID()
{
    Utils::instance()->getChipID(id, DEV_ID_LEN);
    calcPIN();

    Utils::instance()->printf("UID:");
    Utils::instance()->dumpBuffer(id, DEV_ID_LEN);
    Utils::instance()->printf("PIN");
    Utils::instance()->dumpBuffer(pin, DEV_PIN_LEN);
}

void UID::calcPIN()
{
    uint16_t seed = 0xFFFF;
    for (int i = 0; i < DEV_ID_LEN / 2; i += 2) {
        seed = seed ^ ((id[i] << 8) | id[i+1]);
    }
    seed ^= UID_PIN_SEED_MASK;
    randomSeed(seed);

    for (int i = 0; i < DEV_PIN_LEN; i++) {
        pin[i] = random(0xFF+1);
    }
}

bool operator==(const UID &lhs, const UID &rhs)
{
    return (lhs.equalID(rhs) && lhs.equalPIN(rhs));
}
