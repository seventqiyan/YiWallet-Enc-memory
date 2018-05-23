/**************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file Key.h
 *
 * @brief:
 *     按键类接口定义
 *
 * @author Zhaingbo zhaingbo@foxmail.com
 * @date 21.05.2018
 *
 *************************************************************************/
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
