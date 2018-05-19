/**************************************************************************
 *
 *   Copyright (c) 2018 www.yiwallet.top. All rights reserved.
 *
 * @file Config.h
 *
 * @brief:
 *     系统配置文件
 *
 * @author Zhaingbo zhaingbo@foxmail.com
 * @date 19.05.2018
 *
 *************************************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>

// 调试控宏
// #define ZDEBUG 1

// 系统版本
// #define VER_STR           ("0.4")
// 设备PIN码生成器掩码
#define UID_PIN_SEED_MASK (0xE83A)

#define SYS_BOOT_DELAY_TM (2000)

#define LED_STATUS_PIN    (7)
#define KEY_FN_PIN        (3)

// 密码试错限次
#define PASSWD_TRY_LIMITS (0x03)

#include "Utils.h"

#endif /* end of include guard: _CONFIG_H_ */
