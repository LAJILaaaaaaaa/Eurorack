#include "stdint.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

//用户头文件
#include "oled.h"
#include "raspberry26x32.h"
#include "ssd1306_font.h"

//创建图像数组
uint8_t Buffer[128][8];

//创建命令数组
static uint8_t cmds[] = {

    // 这些命令中有些并非绝对必要，因为重置
    // 进程会默认执行其中一些命令，但这里还是显示了这些命令
    // 演示初始化序列的样子
    // 一些配置值是由电路板制造商推荐的

    // SSD1306_SET_DISP,               // 关闭屏幕
    /* 内存映射 */
    // SSD1306_SET_MEM_MODE,           // 设置内存地址模式 0 = 水平，1 = 垂直，2 = 页面
    // 0x00,                           // 水平寻址模式
    /* 分辨率和布局 */
    // SSD1306_SET_DISP_START_LINE,    // 将显示起始行设置为 0
    // SSD1306_SET_SEG_REMAP | 0x01,   // 设置段重新映射，列地址 127 映射到 SEG0
    // SSD1306_SET_MUX_RATIO,          // 设置复用比
    // SSD1306_HEIGHT - 1,             // 显示屏高度 - 1
    // SSD1306_SET_COM_OUT_DIR | 0x08, // 设置 COM（共用）输出扫描方向。自下而上扫描，COM[N-1] 至 COM0
    // SSD1306_SET_DISP_OFFSET,        // 设置显示偏移
    // 0x00,                           // 无偏移
    // SSD1306_SET_COM_PIN_CFG,        // 设置 COM（公共）引脚硬件配置。特定于电路板的神奇数字。
    // 0x12,                           // 0x02 适用于 128x32，0x12 可能适用于 128x64。其他选项 0x22、0x32
    // 0xC8,
    // 0xA1,
    /* 时间和驱动方法 */
    // SSD1306_SET_DISP_CLK_DIV,       // 设置显示时钟分频比
    // 0x80,                           // 除法比为 1，标准频率
    // SSD1306_SET_PRECHARGE,          // 设定预充电时间
    // 0xF1,                           // 电路板内部产生的 Vcc
    // SSD1306_SET_VCOM_DESEL,         // 设置 VCOMH 取消选择电平
    // 0x30,                           // 0.83xVcc
    /* 显示 */
    // SSD1306_SET_CONTRAST,           // 设置对比度控制
    // 0xFF,
    // SSD1306_SET_ENTIRE_ON,          // 将整个显示屏打开，以跟踪 RAM 内容
    // SSD1306_SET_NORM_DISP,          // 设置正常（非倒置）显示
    // SSD1306_SET_CHARGE_PUMP,        // 设置电荷泵
    // 0x14,                           // 电路板内部产生的 Vcc
    // SSD1306_SET_SCROLL | 0x00,      // 如果设置了，则停用水平滚动。这是必要的，因为如果启用了滚动，内存写入就会损坏
    // SSD1306_SET_DISP | 0x01,        // 开启显示器
    0xAE, /*display off*/ 
    0x00, /*set lower column address*/ 
    0x10, /*set higher column address*/
	0xB0, /*set page address*/ 
	0x40, /*set display start lines*/ 
	0x81, /*contract control*/ 
	0x88, /*4d*/ 
	0x82, /* iref resistor set and adjust ISEG*/ 
	0x00, 
	0xA1, /*set segment remap 0xA0*/ 
	0xA2, /*set seg pads hardware configuration*/ 
    0xA4, /*Disable Entire Display On (0xA4/0xA5)*/ 
	0xA6, /*normal / reverse*/ 
	0xA8, /*multiplex ratio*/ 
	0x3F, /*duty = 1/64*/ 
	0xC8, /*Com scan direction 0XC0*/ 
	0xD3, /*set display offset*/ 
	0x00, /* */ 
	0xD5, /*set osc division*/ 
	0xa0, 
	0xD9, /*set pre-charge period*/ 
	0x22, 
	0xdb, /*set vcomh*/ 
	0x40, 
	0x31, /* Set pump 7.4v */ 
	0xad, /*set charge pump enable*/ 
	0x8b, /*Set DC-DC enable (0x8a=disable; 0x8b=enable) */ 
	0xAF,
};

//发送命令函数
void SSD1306_send_cmd(uint8_t cmd) {
    // I2C 写入过程需要一个控制字节，然后是数据
    // 这个 "数据 "可以是命令，也可以是命令的后续数据
    // Co = 1，D/C = 0 => 驱动程序希望得到一条命令
    uint8_t buf[2] = {0x00, cmd};
    i2c_write_blocking(I2C_PORT, SSD1306_I2C_ADDR, buf, 2, false);
}

//发送命令列表函数
void SSD1306_send_cmd_list(uint8_t *buf, int num) {
    for (int i=0;i<num;i++)
        SSD1306_send_cmd(buf[i]);
}

//初始化函数
void OLED_init() {
    //i2c时钟速度设置
    i2c_init(I2C_PORT, 400*1000);
    //初始化i2c引脚
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    SSD1306_send_cmd_list(cmds, count_of(cmds));
    OLED_DisplayTurn(1);
    OLED_Clear();
    OLED_send_buffer();
}

//刷新屏幕函数
void OLED_send_buffer() {
    // in horizontal addressing mode, the column address pointer auto-increments
    // and then wraps around to the next page, so we can send the entire frame
    // buffer in one gooooooo!

    // copy our frame buffer into a new buffer because we need to add the control byte
    // to the beginning
    uint8_t buf[2];
    buf[0]=0x40;
    for (uint8_t y = 0; y < 8; y++)
    {
        SSD1306_send_cmd(0xb0+y);
        SSD1306_send_cmd(0x00);
        SSD1306_send_cmd(0x10);

        for (uint8_t x = 0; x < 128; x++)
        {
            buf[1]=Buffer[x][y];
            i2c_write_blocking(I2C_PORT, SSD1306_I2C_ADDR, buf, 2, false); 
        }   
    } 
    

}

//填充屏幕函数
void OLED_FillScreen(){
    for (uint8_t y = 0; y < 8; y++)
    {
        for (uint8_t x = 0; x < 128; x++)
        {
            Buffer[x][y]=0xff;
        }   
    } 
}

//清除屏幕函数
void OLED_Clear(){
    for (uint8_t y = 0; y < 8; y++)
    {
        for (uint8_t x = 0; x < 128; x++)
        {
            Buffer[x][y]=0x00;
        }   
    } 
}

//屏幕旋转180度
void OLED_DisplayTurn(uint8_t i)
{
	if(i==0)
		{
			SSD1306_send_cmd(0xC8);//正常显示
			SSD1306_send_cmd(0xA1);
		}
	if(i==1)
		{
			SSD1306_send_cmd(0xC0);//反转显示
			SSD1306_send_cmd(0xA0);
		}
}

//绘制点函数
void OLED_SetPixel(int x,int y, bool on) {
    uint8_t Y = y/8;
    uint8_t byte = Buffer[x][Y];

    if (on)
        byte |=  1 << (y % 8);
    else
        byte &= ~(1 << (y % 8));

    Buffer[x][Y] = byte;
}
//绘制线函数
void OLED_DrawLine2(int x0, int y0, int x1, int y1, bool on) {

    int dx =  abs(x1-x0);
    int sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0);
    int sy = y0<y1 ? 1 : -1;
    int err = dx+dy;
    int e2;

    while (true) {
        OLED_SetPixel( x0, y0, on);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2*err;

        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  uint8_t tmp;
  uint8_t x,y;
  uint8_t dx, dy;
  int err;
  int ystep;

  uint8_t swapxy = 0;
  
  /* no intersection check at the moment, should be added... */

  if ( x1 > x2 ) dx = x1-x2; else dx = x2-x1;
  if ( y1 > y2 ) dy = y1-y2; else dy = y2-y1;

  if ( dy > dx ) 
  {
    swapxy = 1;
    tmp = dx; dx =dy; dy = tmp;
    tmp = x1; x1 =y1; y1 = tmp;
    tmp = x2; x2 =y2; y2 = tmp;
  }
  if ( x1 > x2 ) 
  {
    tmp = x1; x1 =x2; x2 = tmp;
    tmp = y1; y1 =y2; y2 = tmp;
  }
  err = dx >> 1;
  if ( y2 > y1 ) ystep = 1; else ystep = -1;
  y = y1;

#ifndef  U8G2_16BIT
  if ( x2 == 255 )
    x2--;
#else
  if ( x2 == 0xffff )
    x2--;
#endif

  for( x = x1; x <= x2; x++ )
  {
    if ( swapxy == 0 ) 
      OLED_SetPixel( x, y,1); 
    else 
      OLED_SetPixel( y, x,1); 
    err -= (uint8_t)dy;
    if ( err < 0 ) 
    {
      y += (uint8_t)ystep;
      err += (uint8_t)dx;
    }
  }
}
//取字符序号
static inline int GetFontIndex(uint8_t ch) {
    if (ch >= 'A' && ch <='Z') {
        return  ch - 'A' + 1;
    }
    else if (ch >= '0' && ch <='9') {
        return  ch - '0' + 27;
    }
    else return  0; // Not got that char so space.
}

static uint8_t reversed[sizeof(font)] = {0};

static uint8_t reverse(uint8_t b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

static void FillReversedCache() {
    // calculate and cache a reversed version of fhe font, because I defined it upside down...doh!
    for (int i=0;i<sizeof(font);i++)
        reversed[i] = reverse(font[i]);
}

void OLED_WriteChar(int16_t x, int16_t y, uint8_t ch) {
    if (reversed[0] == 0) 
        FillReversedCache();

    if (x > SSD1306_WIDTH - 8 || y > SSD1306_HEIGHT - 8)
        return;

    // For the moment, only write on Y row boundaries (every 8 vertical pixels)
    y = y/8;

    ch = toupper(ch);
    int idx = GetFontIndex(ch);

    for (int i=0;i<8;i++) {
        Buffer[x++][y] = reversed[idx * 8 + i];
    }
}

void OLED_WriteString(int16_t x, int16_t y, char *str) {
    // Cull out any string off the screen
    if (x > SSD1306_WIDTH - 8 || y > SSD1306_HEIGHT - 8)
        return;

    while (*str) {
        OLED_WriteChar( x, y, *str++);
        x+=8;
    }
}