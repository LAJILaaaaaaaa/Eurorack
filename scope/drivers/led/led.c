#include <stdio.h>
#include "pico/stdlib.h"
#include "led.h"

//LED初始化函数
void LED_init()
{
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
}

//LED闪烁函数
void LED_Brink()
{
    gpio_put(25, 1);
    sleep_ms(5);
    gpio_put(25, 0);
    sleep_ms(500);
}

//LED亮起函数
void LED_ON()
{
    gpio_put(25, 1);
}

//LED熄灭函数
void LED_OFF()
{
    gpio_put(25, 0);
}