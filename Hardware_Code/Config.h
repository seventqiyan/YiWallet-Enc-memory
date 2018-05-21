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
// 系统启动延时定义（ms）
#define SYS_BOOT_DELAY_TM (2000)

// 状态指示灯功能引脚定义
#define LED_STATUS_PIN    (7)
// Fn功能按键定义
#define KEY_FN_PIN        (3)

// 密码试错限次
#define PASSWD_TRY_LIMITS (0x03)

// 引入工具类
#include "Utils.h"

#endif /* end of include guard: _CONFIG_H_ */
