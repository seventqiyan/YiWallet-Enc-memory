
#ifndef _KEY_H_
#define _KEY_H_

#include "Config.h"

class Key
{
public:
    Key(int keyPin);
    ~Key();

    bool isPress();

private:
    int _key;
};

#endif /* end of include guard: _KEY_H_ */
