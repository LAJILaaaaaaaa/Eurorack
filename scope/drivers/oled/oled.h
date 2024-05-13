#define I2C_PORT i2c0

#define I2C_SDA 8
#define I2C_SCL 9

#define ADDR _u(0x3C)

//定义屏幕的长和宽
#define SSD1306_HEIGHT              64
#define SSD1306_WIDTH               128

//定义i2c地址
#define SSD1306_I2C_ADDR            _u(0x3C)

//定义i2c时钟速度
#define SSD1306_I2C_CLK             400

//OLED命令
#define SSD1306_SET_MEM_MODE        _u(0x20)	//定义寻址模式（0x00，水平；0x01，垂直；0x02；页）
#define SSD1306_SET_COL_ADDR        _u(0x21)	//列地址
#define SSD1306_SET_PAGE_ADDR       _u(0x22)	//页面地址
#define SSD1306_SET_HORIZ_SCROLL    _u(0x26)	//
#define SSD1306_SET_SCROLL          _u(0x2E)    //

#define SSD1306_SET_DISP_START_LINE _u(0x40)    //

#define SSD1306_SET_CONTRAST        _u(0x81)	//设置对比度
#define SSD1306_SET_CHARGE_PUMP     _u(0x8D)    //

#define SSD1306_SET_SEG_REMAP       _u(0xA0)    //
#define SSD1306_SET_ENTIRE_ON       _u(0xA4)    //
#define SSD1306_SET_ALL_ON          _u(0xA5)    //
#define SSD1306_SET_NORM_DISP       _u(0xA6)	//正常显示
#define SSD1306_SET_INV_DISP        _u(0xA7)	//反相显示
#define SSD1306_SET_MUX_RATIO       _u(0xA8)    //
#define SSD1306_SET_DISP            _u(0xAE)    //
#define SSD1306_SET_COM_OUT_DIR     _u(0xC0)    //
#define SSD1306_SET_COM_OUT_DIR_FLIP _u(0xC0)   //

#define SSD1306_SET_DISP_OFFSET     _u(0xD3)	//屏幕便宜
#define SSD1306_SET_DISP_CLK_DIV    _u(0xD5)    //
#define SSD1306_SET_PRECHARGE       _u(0xD9)    //
#define SSD1306_SET_COM_PIN_CFG     _u(0xDA)    //
#define SSD1306_SET_VCOM_DESEL      _u(0xDB)    //

#define SSD1306_PAGE_HEIGHT         _u(8)       //
#define SSD1306_NUM_PAGES           (SSD1306_HEIGHT / SSD1306_PAGE_HEIGHT)  //
#define SSD1306_BUF_LEN             (SSD1306_NUM_PAGES * SSD1306_WIDTH)     //

#define SSD1306_WRITE_MODE         _u(0xFE)     //
#define SSD1306_READ_MODE          _u(0xFF)     //

void SSD1306_send_cmd(uint8_t cmd);

void SSD1306_send_cmd_list(uint8_t *buf, int num);

void OLED_init();

void OLED_FillScreen();

void OLED_DisplayTurn(uint8_t i);

void OLED_send_buffer();



void OLED_SetPixel(int x,int y, bool on);

void OLED_DrawLine2(int x0, int y0, int x1, int y1, bool on);

void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

void OLED_WriteChar(int16_t x, int16_t y, uint8_t ch);

void OLED_WriteString(int16_t x, int16_t y, char *str);


// void OLED_Write_Cmd(uint8_t cmd);
// void OLED_Write_Data(uint8_t data);
// void OLED_Write_Cmd2(uint8_t cmda,uint8_t cmdb);
// void OLED_Write_Data1024();

void OLED_Clear();
// void OLED_Clear2(void);

// void OLED_Refresh(void);
