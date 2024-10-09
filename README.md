# Eurorack

[TOC]

## 模块尺寸规范
[01] [物理规格参考链接_doepfer](https://www.doepfer.de/a100_man/a100m_e.htm)  
[02] [物理规格参考链接_intellijel](https://intellijel.com/support/1u-technical-specifications/)

## 信号和电压
[电气规格参考链接](https://www.doepfer.de/a100_man/a100t_e.htm)  
### 音频信号  
>通常在10Vpp范围内（从-5V到+5V）。  

### 控制电压  
>由LFO和ADSR等调制源产生，LFO通常从-2.5 V到+2.5 V（5 Vpp），ADSR从0 V到+8 V。

### 触发电压  
>触发器、门或时钟信号，启动过程或功能，是矩形信号，典型电压电平为0/+5 V。在触发应用程序的情况下，通常是用于触发事件的信号的上升边缘。  

## 模块制造商
- [makenoise](https://www.makenoisemusic.com)
- [instruo](https://www.instruomodular.com)
- [4ms](https://4mscompany.com)
- [mutable-instruments](https://pichenettes.github.io/mutable-instruments-documentation/)
- [busycircuits](https://busycircuits.com)
- [intellijel](https://intellijel.com)
- [expert-sleepers](https://www.expert-sleepers.co.uk)
- [befaco](https://www.befaco.org)
- [Der Mann mit der Maschine](https://shop.dermannmitdermaschine.de) 
- [antumbra](https://www.antumbra.eu)
- [QU-Bit](https://www.qubitelectronix.com/shop)
- [2HP](https://www.twohp.com/modules)
- [musicthing](https://www.musicthing.co.uk)
- [abyssdevices](https://abyssdevices.com)
- [monome](https://monome.org)

## 开发者套件
开发者套件的目的是将Eurorack中常用的电路模块化，方便Eurorack开发者们在面包板上进行电路实验。
### [PJ301M-12]()
> 单声道音频输入模块

### [PJ301BM]()
> 单声道音频输入模块

### [KEY_LED]()
> 带led灯的轻触开关模块  

### [KEY]()
> 轻触开关模块

### [LED]()
> LED灯模块

### [ENCODER]()
> 编码器模块



## 常用电路
- ne555时钟发生电路  
- 白噪声发生电路  
- 粉色噪声发生电路
- 采样保持电路  
- 电压比较器电路  
- 门转触发电路  
- 触发转门电路  
- 随机门发生器  
- 门随机跳过电路  
- AR包络发生器电路
- 随机电压发生电路

### LED灯光电路
1. 三极管
2. lm321运算放大器
3. 单led
4. 双led
5. rgb

### 运算放大器电路
1. 同相比例放大
2. 反相比例放大
3. 加法器
4. 电压跟随器

## 常用网站
- [thonk](https://www.thonk.co.uk)
- [modulargrid](https://modulargrid.net)
- [mouser](https://www.mouser.cn)

## 硬件驱动库
- OLED
- Key
- Encoder
- LED
- ADC
- DAC
- CAP1214电容触摸
- MAX7219数码管驱动

## 模拟电路
- multisim电路仿真

## PCB绘制
Kicad
- PCB艺术外观

## 合成器电路
### 参考网站

## DSP算法

## 常用开发板
- Stm32
  - f103c8t6
  - f411c8t6
- 树莓派
  - pico
  - 5
  - 4B+
- Arduino
  - nano
  - Uno R4

## 常用硬件
- 基础
  - 电阻
  - 电容  
  - 二极管
    - 1N4148高速开关二极管
    - 肖特基二极管
      - 1N5819HW
      - BAT54SLT1G双肖特基二极管
  - NPN三极管
    - MMBT3904
  - LDO
    - LM1117
    - MCP1703 LDO Vref
  - 磁珠
- 控制
  - 按键
  - 电位器
  - 编码器
- 显示
  - LED灯
  - OLED显示器
    - 0.96英寸（驱动SSD1306）
    - 1.29英寸（驱动CH1115）
    - 1.3英寸
    - 1.54英寸（驱动SSD1306）
    - 2.7英寸
- 输入输出
  - 3.5mm单声道插座
  - type-c插座
- 连接
  - 2.54排针排母
  - 1.27排针排母
  - 跳线帽
  - 11mm，m2铜柱
- 运算放大器
  - TL072
  - TL074
  - MCP6002 R2R
  - MCP6004 R2R
  - OPA4171 四运放
  - OPA2171 双运放
  - LM324 四运放
- ADC
  - ADS1115
- DAC
  - WM8731
  - DAC8564
  - DAC128S085
- 其他
  - LM4040
  - CD4051
  - 74hc595 移位寄存器
  - 74AHCT1G125
  - MAX7219 数码管驱动