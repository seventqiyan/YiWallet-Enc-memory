/**************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file Key.cpp
 *
 * @brief:
 *     Key按键类接口实现
 *
 * @author Zhaingbo zhaingbo@foxmail.com
 * @date 21.05.2018
 *
 *************************************************************************/
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
