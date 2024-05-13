#ifndef _ADS1115_H_
#define _ADS1115_H_

#include "pico.h"
#include "hardware/i2c.h"
#include "registers.h"

/** \file ads1115.h
 * \brief Library for using an ADS1115 analog-to-digital converter with
 * the Raspberry Pi Pico
*/

typedef struct ads1115_adc {
    i2c_inst_t *i2c_port;
    uint8_t i2c_addr;
    uint16_t config;
} ads1115_adc_t;

/*! \brief 初始化ads1115对象
 *
 * \param i2c_port 选用的树莓派pico的I2C端口，i2c0或者i2c1
 * \param i2c_addr ads1115的I2C从设备地址
 * \param adc Pointer to the structure that stores the ADS1115 info
 */
void ads1115_init(i2c_inst_t *i2c_port, uint8_t i2c_addr,
                  ads1115_adc_t *adc);

/*! \brief 读取最后一次转换的数值
 *
 * \param adc_value Pointer to a buffer to receive the data
 * \param adc Pointer to the structure that stores the ADS1115 info
 */
void ads1115_read_adc(uint16_t *adc_value, ads1115_adc_t *adc);

/*! \brief Read the 16-bit configuration register
 *
 * After powering up, the default configuration value 
 * is 34179 (1411 after bit 15 has been cleared).
 * 
 * \param adc Pointer to the structure that stores the ADS1115 info
 */
void ads1115_read_config(ads1115_adc_t *adc);

/*! \brief Write current configuration to the configuration register
 *
 * \param adc Pointer to the structure that stores the ADS1115 info
 */
void ads1115_write_config(ads1115_adc_t *adc);

/*! \brief Convert a (raw) ADC value to voltage
 *
 * Converted values are 16-bit two's complement
 * 
 * \param adc_value Raw ADC value to convert
 * \param adc Pointer to the structure that stores the ADS1115 info
 */
float ads1115_raw_to_volts(uint16_t adc_value, ads1115_adc_t *adc);

/*! \brief Configure the programmable gain amplifier (PGA)
 *
 * Configures the PGA to achieve different full-scale voltage ranges.
 * Be aware that, whatever this setting, the absolute voltage of any
 * analog input should never be greater than VDD + 0.3 V.
 * 
 * The available full-scale ranges (FSR) are ±6.144 V, ±4.096 V 
 * (default), ±2.048 V, ±1.024 V, ±0.512 V, and ±0.256 V.
 * 
 * \param pga PGA value to use
 * \param adc Pointer to the structure that stores the ADS1115 info
 */
void ads1115_set_pga(enum ads1115_pga_t pga, ads1115_adc_t *adc);

/*! \brief Set the operating mode
 * 
 * The operating mode of the device can be continuous conversion or
 * single-shot.
 * 
 * \param mode Operating mode
 * \param adc Pointer to the structure that stores the ADS1115 info
 */
void ads1115_set_operating_mode(enum ads1115_mode_t mode,
                                ads1115_adc_t *adc);

/*! \brief Set the data rate
 * 
 * Available data rates are 8, 16, 32, 64, 128 (default), 250, 475,
 * and 860 SPS.
 * 
 * \param rate Data rate
 * \param adc Pointer to the structure that stores the ADS1115 info
 */
void ads1115_set_data_rate(enum ads1115_rate_t rate,
                           ads1115_adc_t *adc);

/*! \brief Configure the input multiplexer
 * 
 * The input can be single-ended or differential. The options for 
 * differential signals are (AIN_P, AIN_N): (0, 1), (0, 3), (1, 3),
 * and (2, 3).
 * 
 * \param mux Multiplexer parameter
 * \param adc Pointer to the structure that stores the ADS1115 info
 */
void ads1115_set_input_mux(enum ads1115_mux_t mux, ads1115_adc_t *adc);

// void set_comparator_mode();
// void set_comparator_polarity();
// void set_comparator_latching();
// void set_comparator_queue();

#endif
