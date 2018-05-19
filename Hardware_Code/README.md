# 易钱包<sup>TM</sup>  （Yi<sup>☯</sup>Wallet）

​	易钱包（YiWallet）是一种采用Arduino平台实现的冷钱包技术设备。最大程度上保障客户的数字财产的安全性，钱包目前支持BitCoin Cash货币钱包地址信息的存储。

<!-- more -->

## 使用说明

### 设备初始化

​	首次使用易钱包需要根据提示输入“设备编码（UID）”和”预置码（PIN）“，系统校验UID与PIN后，完成对硬件设备的初始化操作。

- UID -- 全球设备唯一编码，该序列共包含20个字符，随设备提供。
- PIN -- 设备使用预置码，该序列共包含12个字符，由系统随机预置。设备初始化完成后亦请请妥善保管之。

#### 设置使用密码

​	设备初始化完成后，用户需要根据提示设置使用密码；密码长度最长不超过16个字符。

> ★警告：使用密码是访问设备的合法凭证，用户应该妥善保管“使用密码”。

#### 初始化BCC信息

​	在完成密码初始化后，用户需要根据提示输入BCC设备信息。完成BCC信息的初始化工作。

目前设备仅支持Bitcoin Cash格式的钱包地址，该种格式钱包地址由42位的bitcoin_addr及52字节的private key组成。

``` shell
====================================================
=       __   _____        __    _ _      _         =
=       \ \ / (_) \      / /_ _| | | ___| |_       =
=        \ V /| |\ \ /\ / / _` | | |/ _ \ __|      =
=         | | | | \ V  V / (_| | | |  __/ |_       =
=         |_| |_|  \_/\_/ \__,_|_|_|\___|\__|      =
=                                                  =
================ YiWallet (ver 0.3) ================

Please Input the UID(20): **********
Please Input the PIN(6): ******
Please init your password (Max.16): 
Please init your AGAIN password: 
Please Input your password(Init): 
Please input your bitcoin_cash(42): 
Please input your private key(52): 
System Init OK!!!
```

### 设备使用

#### 正常使用

​	设备提示用户输入使用密码，取出BCC信息。一个正常使用的实例应该如下所示：

``` shell
====================================================
=       __   _____        __    _ _      _         =
=       \ \ / (_) \      / /_ _| | | ___| |_       =
=        \ V /| |\ \ /\ / / _` | | |/ _ \ __|      =
=         | | | | \ V  V / (_| | | |  __/ |_       =
=         |_| |_|  \_/\_/ \__,_|_|_|\___|\__|      =
=                                                  =
================ YiWallet (ver 0.x) ================

Please Input your password: 
BTC Cash Info: 
bitcoincash: 
qrlaq6kv42vhraqcwhj8hsnflgdwpr8frgy2t9gsf9
private Key: 
KwQKjoScnjvwQW7C9qXiFctwY8o93Souy73i15gLM4gXkdQe4uWo

<<<<<<<<<<<<    Thanks for you using!    >>>>>>>>>>>>
```

#### 忘记密码

针对忘记使用密码恢复的情况，可以参考下节[异常恢复模式](#recover_mode)。

### <span id = "recover_mode">异常恢复模式</span>


​	如果用户忘记使用密码，需要按住 **`Fn键`** 重启系统，以使系统进入维护模式。之后根据提示维护菜单提示重设设备使用密码。

> ★★★★★警告：维护模式提供的“销毁BCC信息”和（或）“重新初始化BCC信息”的功能会擦除设备中存储的BCC信息。本设备中的存储信息一旦擦除，断无恢复可能，故请务必确保该信息已通过其他途径保存。

## 特性

​	易钱包主要有以下特性：

-   设备采用加密性能良好的单片处理器，实现成本低廉；
-   支持用户自定义密码，密码长度（1~16个字符，建议不低于6个字符的数字/字符/特殊符号组成的混合密码组）；
-   设备本身不存任何明文信息，密码与BCC地址信息采用AES128加密技术进行加密存储；
-   预留有密码可恢复指令。
