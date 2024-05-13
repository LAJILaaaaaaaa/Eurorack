#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/dma.h"
#include "hardware/pio.h"
#include "hardware/interp.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"

//包含用户库
#include "drivers/led/led.h"
#include "drivers/oled/oled.h"
#include "drivers/ads1115/ads1115.h"


// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
// #define I2C_PORT i2c0
// #define I2C_SDA 8
// #define I2C_SCL 9


int64_t alarm_callback(alarm_id_t id, void *user_data) {
    // Put your timeout handler code in here
    return 0;
}

struct ads1115_adc adc;
//主函数入口
int main()
{
    sleep_ms(10);
    stdio_init_all();

    // Interpolator example code
    // interp_config cfg = interp_default_config();
    // Now use the various interpolator library functions for your use case
    // e.g. interp_config_clamp(&cfg, true);
    //      interp_config_shift(&cfg, 2);
    // Then set the config 
    // interp_set_config(interp0, 0, &cfg);

    // Timer example code - This example fires off the callback after 2000ms
    // add_alarm_in_ms(2000, alarm_callback, NULL, false);

    //用户函数初始化
    OLED_init();
    LED_init();
    
    OLED_SetPixel(63,0,1);
    OLED_SetPixel(66,4,1);
    OLED_DrawLine(0,0,127,63);
    OLED_DrawLine(127,32,0,10);
    char *text[] = {
        "A long time ago",
        "  on an OLED ",
        "   display",
        " far far away",
        "Lived a small",
        "red raspberry",
        "by the name of",
        "    PICO"
    };
    //OLED变量
    char string[16] = {0};
    int number1 = 0;

    while (1)
    {
        number1++;
        itoa(number1,string,10);
        OLED_WriteString(10,20,string);
        OLED_send_buffer();

    }
    
    return 0;
}
