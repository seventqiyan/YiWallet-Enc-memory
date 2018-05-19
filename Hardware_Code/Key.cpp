
#include "Key.h"


Key::Key(int keyPin)
    : _key(keyPin)
{

}

Key::~Key()
{

}

bool Key::isPress()
{
    return (digitalRead(_key) == LOW);
}
