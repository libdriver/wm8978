/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_wm8978.h
 * @brief     driver wm8978 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2023-07-31
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2023/07/31  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_WM8978_H
#define DRIVER_WM8978_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup wm8978_driver wm8978 driver function
 * @brief    wm8978 driver modules
 * @{
 */

/**
 * @addtogroup wm8978_base_driver
 * @{
 */

/**
 * @brief wm8978 bool enumeration definition
 */
typedef enum
{
    WM8978_BOOL_FALSE = 0x00,        /**< disable */
    WM8978_BOOL_TRUE  = 0x01,        /**< enable */
} wm8978_bool_t;

/**
 * @brief wm8978 impedance enumeration definition
 */
typedef enum
{
    WM8978_IMPEDANCE_OFF  = 0x00,        /**< open circuit */
    WM8978_IMPEDANCE_75K  = 0x01,        /**< 75k ohm */
    WM8978_IMPEDANCE_300K = 0x02,        /**< 300k ohm */
    WM8978_IMPEDANCE_5K   = 0x03,        /**< 5k ohm */
} wm8978_impedance_t;

/**
 * @brief wm8978 polarity enumeration definition
 */
typedef enum
{
    WM8978_POLARITY_NORMAL   = 0x00,        /**< normal mode */
    WM8978_POLARITY_INVERTED = 0x01,        /**< inverted mode */
} wm8978_polarity_t;

/**
 * @brief wm8978 word length enumeration definition
 */
typedef enum
{
    WM8978_WORD_LENGTH_16_BITS = 0x00,        /**< 16 bits */
    WM8978_WORD_LENGTH_20_BITS = 0x01,        /**< 20 bits */
    WM8978_WORD_LENGTH_24_BITS = 0x02,        /**< 24 bits */
    WM8978_WORD_LENGTH_32_BITS = 0x03,        /**< 32 bits */
} wm8978_word_length_t;

/**
 * @brief wm8978 data format enumeration definition
 */
typedef enum
{
    WM8978_DATA_FORMAT_RIGHT_JUSTIFIED = 0x00,        /**< right justified */
    WM8978_DATA_FORMAT_LEFT_JUSTIFIED  = 0x01,        /**< left justified */
    WM8978_DATA_FORMAT_IIS             = 0x02,        /**< iis format */
    WM8978_DATA_FORMAT_PCM             = 0x03,        /**< dsp/pcm mode */
} wm8978_data_format_t;

/**
 * @brief wm8978 appear enumeration definition
 */
typedef enum
{
    WM8978_APPEAR_LEFT  = 0x00,        /**< appear in left */
    WM8978_APPEAR_RIGHT = 0x01,        /**< appear in right */
} wm8978_appear_t;

/**
 * @brief wm8978 channel enumeration definition
 */
typedef enum
{
    WM8978_CHANNEL_STEREO = 0x00,        /**< stereo device operation */
    WM8978_CHANNEL_MONO   = 0x01,        /**< mono device operation */
} wm8978_channel_t;

/**
 * @brief wm8978 companding enumeration definition
 */
typedef enum
{
    WM8978_COMPANDING_LINEAR = 0x00,        /**< linear mode */
    WM8978_COMPANDING_U_LAW  = 0x02,        /**< u-law */
    WM8978_COMPANDING_A_LAW  = 0x03,        /**< a-law */
} wm8978_companding_t;

/**
 * @brief wm8978 clksel enumeration definition
 */
typedef enum
{
    WM8978_CLKSEL_MCLK       = 0x00,        /**< mclk */
    WM8978_CLKSEL_PLL_OUTPUT = 0x01,        /**< pll output */
} wm8978_clksel_t;

/**
 * @brief wm8978 mclk div enumeration definition
 */
typedef enum
{
    WM8978_MCLK_DIV_BY_1   = 0x00,        /**< divide by 1 */
    WM8978_MCLK_DIV_BY_1P5 = 0x01,        /**< divide by 1.5 */
    WM8978_MCLK_DIV_BY_2   = 0x02,        /**< divide by 2 */
    WM8978_MCLK_DIV_BY_3   = 0x03,        /**< divide by 3 */
    WM8978_MCLK_DIV_BY_4   = 0x04,        /**< divide by 4 */
    WM8978_MCLK_DIV_BY_6   = 0x05,        /**< divide by 6 */
    WM8978_MCLK_DIV_BY_8   = 0x06,        /**< divide by 8 */
    WM8978_MCLK_DIV_BY_12  = 0x07,        /**< divide by 12 */
} wm8978_mclk_div_t;

/**
 * @brief wm8978 bclk div enumeration definition
 */
typedef enum
{
    WM8978_BCLK_DIV_BY_1  = 0x00,        /**< divide by 1 */
    WM8978_BCLK_DIV_BY_2  = 0x01,        /**< divide by 2 */
    WM8978_BCLK_DIV_BY_4  = 0x02,        /**< divide by 4 */
    WM8978_BCLK_DIV_BY_8  = 0x03,        /**< divide by 8 */
    WM8978_BCLK_DIV_BY_16 = 0x04,        /**< divide by 16 */
    WM8978_BCLK_DIV_BY_32 = 0x05,        /**< divide by 32 */
} wm8978_bclk_div_t;

/**
 * @brief wm8978 clock mode enumeration definition
 */
typedef enum
{
    WM8978_CLOCK_MODE_INPUT  = 0x00,        /**< bclk and lrc clock are inputs */
    WM8978_CLOCK_MODE_OUTPUT = 0x01,        /**< bclk and lrc clock are output generated by the wm8978 */
} wm8978_clock_mode_t;

/**
 * @brief wm8978 approximate sample enumeration definition
 */
typedef enum
{
    WM8978_APPROXIMATE_SAMPLE_48_KHZ = 0x00,        /**< 48khz */
    WM8978_APPROXIMATE_SAMPLE_32_KHZ = 0x01,        /**< 32khz */
    WM8978_APPROXIMATE_SAMPLE_24_KHZ = 0x02,        /**< 24khz */
    WM8978_APPROXIMATE_SAMPLE_16_KHZ = 0x03,        /**< 16khz */
    WM8978_APPROXIMATE_SAMPLE_12_KHZ = 0x04,        /**< 12khz */
    WM8978_APPROXIMATE_SAMPLE_8_KHZ  = 0x05,        /**< 8khz */
} wm8978_approximate_sample_t;

/**
 * @brief wm8978 pll div enumeration definition
 */
typedef enum
{
    WM8978_PLL_DIV_BY_1 = 0x00,        /**< divide by 1 */
    WM8978_PLL_DIV_BY_2 = 0x01,        /**< divide by 2 */
    WM8978_PLL_DIV_BY_3 = 0x02,        /**< divide by 3 */
    WM8978_PLL_DIV_BY_4 = 0x03,        /**< divide by 4 */
} wm8978_pll_div_t;

/**
 * @brief wm8978 gpio1 sel enumeration definition
 */
typedef enum
{
    WM8978_GPIO1_SEL_INPUT        = 0x00,        /**< input */
    WM8978_GPIO1_SEL_TEMP_OK      = 0x02,        /**< temp ok */
    WM8978_GPIO1_SEL_AMUTE_ACTIVE = 0x03,        /**< amute active */
    WM8978_GPIO1_SEL_PLL_CLK      = 0x04,        /**< pll clk */
    WM8978_GPIO1_SEL_PLL_LOCK     = 0x05,        /**< pll lock */
    WM8978_GPIO1_SEL_LOGIC_1      = 0x06,        /**< logic 1 */
    WM8978_GPIO1_SEL_LOGIC_0      = 0x07,        /**< logic 0 */
} wm8978_gpio1_sel_t;

/**
 * @brief wm8978 jack sel enumeration definition
 */
typedef enum
{
    WM8978_JACK_SEL_GPIO1 = 0x00,        /**< gpio1 */
    WM8978_JACK_SEL_GPIO2 = 0x01,        /**< gpio2 */
    WM8978_JACK_SEL_GPIO3 = 0x02,        /**< gpio3 */
} wm8978_jack_sel_t;

/**
 * @brief wm8978 dac oversample rate enumeration definition
 */
typedef enum
{
    WM8978_DAC_OVERSAMPLE_RATE_64X  = 0x00,        /**< 64x, lowest power */
    WM8978_DAC_OVERSAMPLE_RATE_128X = 0x01,        /**< 128x, lowest power */
} wm8978_dac_oversample_rate_t;

/**
 * @brief wm8978 jack enumeration definition
 */
typedef enum
{
    WM8978_JACK_OUT1 = 0x01,        /**< out1 */
    WM8978_JACK_OUT2 = 0x02,        /**< out2 */
    WM8978_JACK_OUT3 = 0x04,        /**< out3 */
    WM8978_JACK_OUT4 = 0x08,        /**< out4 */
} wm8978_jack_t;

/**
 * @brief wm8978 mode enumeration definition
 */
typedef enum
{
    WM8978_MODE_AUDIO       = 0x00,        /**< audio mode */
    WM8978_MODE_APPLICATION = 0x01,        /**< application mode */
} wm8978_mode_t;

/**
 * @brief wm8978 high pass filter cut off enumeration definition
 *
 *                                fs(kH)                             
 *      8kHz  11.025Hz  12Hz  16Hz  22.05Hz  24Hz  32Hz  44.1Hz  48Hz
 * 0x0   82     113     122    82     113    122    82    113    122
 * 0x1  102     141     153   102     141    153   102    141    153
 * 0x2  131     180     196   131     180    196   131    180    196
 * 0x3  163     225     245   163     225    245   163    225    245
 * 0x4  204     281     306   204     281    306   204    281    306
 * 0x5  261     360     392   261     360    392   261    360    392
 * 0x6  327     450     490   327     450    490   327    450    490
 * 0x7  408     563     612   408     563    612   408    563    612
 */
typedef enum
{
    WM8978_HIGH_PASS_FILTER_CUT_OFF_0 = 0x00,        /**< frequency 0 */
    WM8978_HIGH_PASS_FILTER_CUT_OFF_1 = 0x01,        /**< frequency 1 */
    WM8978_HIGH_PASS_FILTER_CUT_OFF_2 = 0x02,        /**< frequency 2 */
    WM8978_HIGH_PASS_FILTER_CUT_OFF_3 = 0x03,        /**< frequency 3 */
    WM8978_HIGH_PASS_FILTER_CUT_OFF_4 = 0x04,        /**< frequency 4 */
    WM8978_HIGH_PASS_FILTER_CUT_OFF_5 = 0x05,        /**< frequency 5 */
    WM8978_HIGH_PASS_FILTER_CUT_OFF_6 = 0x06,        /**< frequency 6 */
    WM8978_HIGH_PASS_FILTER_CUT_OFF_7 = 0x07,        /**< frequency 7 */
} wm8978_high_pass_filter_cut_off_t;

/**
 * @brief wm8978 adc oversample rate enumeration definition
 */
typedef enum
{
    WM8978_ADC_OVERSAMPLE_RATE_64X  = 0x00,        /**< 64x, lowest power */
    WM8978_ADC_OVERSAMPLE_RATE_128X = 0x01,        /**< 128x, lowest power */
} wm8978_adc_oversample_rate_t;

/**
 * @brief wm8978 equaliser enumeration definition
 */
typedef enum
{
    WM8978_EQUALISER_APPLIED_TO_ADC = 0x00,        /**< equaliser and 3d enhancement applied to adc path */
    WM8978_EQUALISER_APPLIED_TO_DAC = 0x01,        /**< equaliser and 3d enhancement applied to dac path */
} wm8978_equaliser_t;

/**
 * @brief wm8978 eq1 band cut off enumeration definition
 */
typedef enum
{
    WM8978_EQ1_BAND_CUT_OFF_80HZ  = 0x00,        /**< 80hz */
    WM8978_EQ1_BAND_CUT_OFF_105HZ = 0x01,        /**< 105hz */
    WM8978_EQ1_BAND_CUT_OFF_135HZ = 0x02,        /**< 135hz */
    WM8978_EQ1_BAND_CUT_OFF_175HZ = 0x03,        /**< 175hz */
} wm8978_eq1_band_cut_off_t;

/**
 * @brief wm8978 eq bandwidth enumeration definition
 */
typedef enum
{
    WM8978_EQ_BANDWIDTH_NARROW = 0x00,        /**< narrow bandwidth */
    WM8978_EQ_BANDWIDTH_WIDE   = 0x01,        /**< wide bandwidth */
} wm8978_eq_bandwidth_t;

/**
 * @brief wm8978 eq2 band centre freq enumeration definition
 */
typedef enum
{
    WM8978_EQ2_BAND_CENTRE_FREQ_230HZ = 0x00,        /**< 230hz */
    WM8978_EQ2_BAND_CENTRE_FREQ_300HZ = 0x01,        /**< 300hz */
    WM8978_EQ2_BAND_CENTRE_FREQ_385HZ = 0x02,        /**< 385hz */
    WM8978_EQ2_BAND_CENTRE_FREQ_500HZ = 0x03,        /**< 500hz */
} wm8978_eq2_band_centre_freq_t;

/**
 * @brief wm8978 eq3 band centre freq enumeration definition
 */
typedef enum
{
    WM8978_EQ3_BAND_CENTRE_FREQ_650HZ  = 0x00,        /**< 650hz */
    WM8978_EQ3_BAND_CENTRE_FREQ_850HZ  = 0x01,        /**< 850hz */
    WM8978_EQ3_BAND_CENTRE_FREQ_1100HZ = 0x02,        /**< 1100hz */
    WM8978_EQ3_BAND_CENTRE_FREQ_1400HZ = 0x03,        /**< 1400hz */
} wm8978_eq3_band_centre_freq_t;

/**
 * @brief wm8978 eq4 band centre freq enumeration definition
 */
typedef enum
{
    WM8978_EQ4_BAND_CENTRE_FREQ_1800HZ = 0x00,        /**< 1800hz */
    WM8978_EQ4_BAND_CENTRE_FREQ_2400HZ = 0x01,        /**< 2400hz */
    WM8978_EQ4_BAND_CENTRE_FREQ_3200HZ = 0x02,        /**< 3200hz */
    WM8978_EQ4_BAND_CENTRE_FREQ_4100HZ = 0x03,        /**< 4100hz */
} wm8978_eq4_band_centre_freq_t;

/**
 * @brief wm8978 eq5 band cut off enumeration definition
 */
typedef enum
{
    WM8978_EQ5_BAND_CUT_OFF_5300HZ  = 0x00,       /**< 5300hz */
    WM8978_EQ5_BAND_CUT_OFF_6900HZ  = 0x01,       /**< 6900hz */
    WM8978_EQ5_BAND_CUT_OFF_9000HZ  = 0x02,       /**< 9000hz */
    WM8978_EQ5_BAND_CUT_OFF_11700HZ = 0x03,       /**< 11700hz */
} wm8978_eq5_band_cut_off_t;

/**
 * @brief wm8978 dac limiter decay enumeration definition
 */
typedef enum
{
    WM8978_DAC_LIMITER_DECAY_750US = 0x00,       /**< 750us */
    WM8978_DAC_LIMITER_DECAY_1P5MS = 0x01,       /**< 1.5ms */
    WM8978_DAC_LIMITER_DECAY_3MS   = 0x02,       /**< 3ms */
    WM8978_DAC_LIMITER_DECAY_6MS   = 0x03,       /**< 6ms */
    WM8978_DAC_LIMITER_DECAY_12MS  = 0x04,       /**< 12ms */
    WM8978_DAC_LIMITER_DECAY_24MS  = 0x05,       /**< 24ms */
    WM8978_DAC_LIMITER_DECAY_48MS  = 0x06,       /**< 48ms */
    WM8978_DAC_LIMITER_DECAY_96MS  = 0x07,       /**< 96ms */
    WM8978_DAC_LIMITER_DECAY_192MS = 0x08,       /**< 192ms */
    WM8978_DAC_LIMITER_DECAY_384MS = 0x09,       /**< 384ms */
    WM8978_DAC_LIMITER_DECAY_768MS = 0x0A,       /**< 768ms */
} wm8978_dac_limiter_decay_t;

/**
 * @brief wm8978 dac limiter attack enumeration definition
 */
typedef enum
{
    WM8978_DAC_LIMITER_ATTACK_94US  = 0x00,       /**< 94us */
    WM8978_DAC_LIMITER_ATTACK_188US = 0x01,       /**< 188us */
    WM8978_DAC_LIMITER_ATTACK_375US = 0x02,       /**< 375us */
    WM8978_DAC_LIMITER_ATTACK_750US = 0x03,       /**< 750us */
    WM8978_DAC_LIMITER_ATTACK_1P5MS = 0x04,       /**< 1.5ms */
    WM8978_DAC_LIMITER_ATTACK_3MS   = 0x05,       /**< 3ms */
    WM8978_DAC_LIMITER_ATTACK_6MS   = 0x06,       /**< 6ms */
    WM8978_DAC_LIMITER_ATTACK_12MS  = 0x07,       /**< 12ms */
    WM8978_DAC_LIMITER_ATTACK_24MS  = 0x08,       /**< 24ms */
    WM8978_DAC_LIMITER_ATTACK_48MS  = 0x09,       /**< 48ms */
    WM8978_DAC_LIMITER_ATTACK_96MS  = 0x0A,       /**< 96ms */
} wm8978_dac_limiter_attack_t;

/**
 * @brief wm8978 dac limiter level enumeration definition
 */
typedef enum
{
    WM8978_DAC_LIMITER_LEVEL_NEGATIVE_1DB = 0x00,       /**< -1db */
    WM8978_DAC_LIMITER_LEVEL_NEGATIVE_2DB = 0x01,       /**< -2db */
    WM8978_DAC_LIMITER_LEVEL_NEGATIVE_3DB = 0x02,       /**< -3db */
    WM8978_DAC_LIMITER_LEVEL_NEGATIVE_4DB = 0x03,       /**< -4db */
    WM8978_DAC_LIMITER_LEVEL_NEGATIVE_5DB = 0x04,       /**< -5db */
    WM8978_DAC_LIMITER_LEVEL_NEGATIVE_6DB = 0x05,       /**< -6db */
} wm8978_dac_limiter_level_t;

/**
 * @brief wm8978 alc enumeration definition
 */
typedef enum
{
    WM8978_ALC_OFF   = 0x00,       /**< alc off */
    WM8978_ALC_RIGHT = 0x01,       /**< alc right only */
    WM8978_ALC_LEFT  = 0x02,       /**< alc left only */
    WM8978_ALC_BOTH  = 0x03,       /**< alc both on */
} wm8978_alc_t;

/**
 * @brief wm8978 max gain enumeration definition
 */
typedef enum
{
    WM8978_MAX_GAIN_35P25_DB         = 0x07,       /**< 35.25db */
    WM8978_MAX_GAIN_29P25_DB         = 0x06,       /**< 29.25db */
    WM8978_MAX_GAIN_23P25_DB         = 0x05,       /**< 23.25db */
    WM8978_MAX_GAIN_17P25_DB         = 0x04,       /**< 17.25db */
    WM8978_MAX_GAIN_11P25_DB         = 0x03,       /**< 11.25db */
    WM8978_MAX_GAIN_5P25_DB          = 0x02,       /**< 5.25db */
    WM8978_MAX_GAIN_NEGATIVE_0P75_DB = 0x01,       /**< -0.75db */
    WM8978_MAX_GAIN_NEGATIVE_6P75_DB = 0x00,       /**< -6.75db */
} wm8978_max_gain_t;

/**
 * @brief wm8978 min gain enumeration definition
 */
typedef enum
{
    WM8978_MIN_GAIN_30_DB          = 0x07,       /**< 30db */
    WM8978_MIN_GAIN_24_DB          = 0x06,       /**< 24db */
    WM8978_MIN_GAIN_18_DB          = 0x05,       /**< 18db */
    WM8978_MIN_GAIN_12_DB          = 0x04,       /**< 12db */
    WM8978_MIN_GAIN_6_DB           = 0x03,       /**< 6db */
    WM8978_MIN_GAIN_0_DB           = 0x02,       /**< 0db */
    WM8978_MIN_GAIN_NEGATIVE_6_DB  = 0x01,       /**< -6db */
    WM8978_MIN_GAIN_NEGATIVE_12_DB = 0x00,       /**< -12db */
} wm8978_min_gain_t;

/**
 * @brief wm8978 alc mode enumeration definition
 */
typedef enum
{
    WM8978_ALC_MODE_ALC     = 0x00,       /**< alc mode */
    WM8978_ALC_MODE_LIMITER = 0x01,       /**< limiter mode */
} wm8978_alc_mode_t;

/**
 * @brief wm8978 avdd enumeration definition
 */
typedef enum
{
    WM8978_AVDD_0P9  = 0x00,       /**< 0.9 avdd */
    WM8978_AVDD_0P65 = 0x01,       /**< 0.65 avdd */
} wm8978_avdd_t;

/**
 * @brief wm8978 vref enumeration definition
 */
typedef enum
{
    WM8978_VREF_1K  = 0x00,       /**< 1k */
    WM8978_VREF_30K = 0x01,       /**< 30k */
} wm8978_vref_t;

/**
 * @brief wm8978 alc level enumeration definition
 */
typedef enum
{
    WM8978_ALC_LEVEL_NEGATIVE_1P5  = 0x0F,       /**< -1.5dB */
    WM8978_ALC_LEVEL_NEGATIVE_3    = 0x0D,       /**< -3dB */
    WM8978_ALC_LEVEL_NEGATIVE_4P5  = 0x0C,       /**< -4.5dB */
    WM8978_ALC_LEVEL_NEGATIVE_21   = 0x01,       /**< -21dB */
    WM8978_ALC_LEVEL_NEGATIVE_22P5 = 0x00,       /**< -22.5dB */
} wm8978_alc_level_t;

/**
 * @brief wm8978 handle structure definition
 */
typedef struct wm8978_handle_s
{
    uint8_t iic_addr;                                                                   /**< iic device address */
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint16_t reg[58];                                                                   /**< reg buffer */
    uint8_t inited;                                                                     /**< inited flag */
} wm8978_handle_t;

/**
 * @brief wm8978 information structure definition
 */
typedef struct wm8978_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} wm8978_info_t;

/**
 * @}
 */

/**
 * @defgroup wm8978_link_driver wm8978 link driver function
 * @brief    wm8978 link driver modules
 * @ingroup  wm8978_driver
 * @{
 */

/**
 * @brief     initialize wm8978_handle_t structure
 * @param[in] HANDLE points to a wm8978 handle structure
 * @param[in] STRUCTURE is wm8978_handle_t
 * @note      none
 */
#define DRIVER_WM8978_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to a wm8978 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_WM8978_LINK_IIC_INIT(HANDLE, FUC)     (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to a wm8978 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_WM8978_LINK_IIC_DEINIT(HANDLE, FUC)   (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to a wm8978 handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_WM8978_LINK_IIC_WRITE(HANDLE, FUC)    (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a wm8978 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_WM8978_LINK_DELAY_MS(HANDLE, FUC)     (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a wm8978 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_WM8978_LINK_DEBUG_PRINT(HANDLE, FUC)  (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup wm8978_base_driver wm8978 base driver function
 * @brief    wm8978 base driver modules
 * @ingroup  wm8978_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a wm8978 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t wm8978_info(wm8978_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a wm8978 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 * @note      none
 */
uint8_t wm8978_init(wm8978_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a wm8978 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t wm8978_deinit(wm8978_handle_t *handle);

/**
 * @brief     soft reset
 * @param[in] *handle points to a wm8978 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_soft_reset(wm8978_handle_t *handle);

/**
 * @brief     enable or disable dc buffer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set dc buffer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_dc_buffer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable out4 mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set out4 mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_out4_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable out3 mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set out3 mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_out3_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable pll
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set pll failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_pll(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable microphone bias
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set microphone bias failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_microphone_bias(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable analogue amplifier bias
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set analogue amplifier bias failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_analogue_amplifier_bias(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable unused input output tie off buffer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set unused input output tie off buffer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_unused_input_output_tie_off_buffer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set reference impedance
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] impedance is the set reference impedance 
 * @return    status code
 *            - 0 success
 *            - 1 set reference impedance failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_reference_impedance(wm8978_handle_t *handle, wm8978_impedance_t impedance);

/**
 * @brief     enable or disable right out1
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right out1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_out1(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left out1
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left out1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_out1(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable sleep
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set sleep failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_sleep(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right channel input boost
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right channel input boost failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_channel_input_boost(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left channel input boost
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left channel input boost failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_channel_input_boost(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right channel input pga
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right channel input pga failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_channel_input_pga(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left channel input pga
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left channel input pga failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_channel_input_pga(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right channel adc
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right channel adc failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_channel_adc(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left channel adc
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left channel adc failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_channel_adc(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable out4
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set out4 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_out4(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable out3
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set out3 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_out3(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left out2
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left out2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_out2(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right out2
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right out2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_out2(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right output channel mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right output channel mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_output_channel_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left output channel mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left output channel mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_output_channel_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right channel dac
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right channel dac failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_channel_dac(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left channel dac
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left channel dac failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_channel_dac(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set bclk polarity
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] polarity is the bclk polarity
 * @return    status code
 *            - 0 success
 *            - 1 set bclk polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_bclk_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity);

/**
 * @brief     set lrclk polarity
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] polarity is the lrclk polarity
 * @return    status code
 *            - 0 success
 *            - 1 set lrclk polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_lrclk_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity);

/**
 * @brief     set word length
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] word_length is the iis word length
 * @return    status code
 *            - 0 success
 *            - 1 set word length failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_word_length(wm8978_handle_t *handle, wm8978_word_length_t word_length);

/**
 * @brief     set data format
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] format is the data format
 * @return    status code
 *            - 0 success
 *            - 1 set data format failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_data_format(wm8978_handle_t *handle, wm8978_data_format_t format);

/**
 * @brief     set dac appear
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] appear is the dac appear side
 * @return    status code
 *            - 0 success
 *            - 1 set dac appear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_dac_appear(wm8978_handle_t *handle, wm8978_appear_t appear);

/**
 * @brief     set adc appear
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] appear is the adc appear side
 * @return    status code
 *            - 0 success
 *            - 1 set adc appear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_adc_appear(wm8978_handle_t *handle, wm8978_appear_t appear);

/**
 * @brief     set channel
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] channel is the audio channel
 * @return    status code
 *            - 0 success
 *            - 1 set channel failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_channel(wm8978_handle_t *handle, wm8978_channel_t channel);

/**
 * @brief     enable or disable companding 8bit mode
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set companding 8bit mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_companding_8bit_mode(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set dac companding
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] companding is the dac companding
 * @return    status code
 *            - 0 success
 *            - 1 set dac companding failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_dac_companding(wm8978_handle_t *handle, wm8978_companding_t companding);

/**
 * @brief     set adc companding
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] companding is the adc companding
 * @return    status code
 *            - 0 success
 *            - 1 set adc companding failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_adc_companding(wm8978_handle_t *handle, wm8978_companding_t companding);

/**
 * @brief     enable or disable loopback
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set loopback failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_loopback(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set clksel
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] clksel is the set clksel
 * @return    status code
 *            - 0 success
 *            - 1 set clksel failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_clksel(wm8978_handle_t *handle, wm8978_clksel_t clksel);

/**
 * @brief     set mclk div
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] d is the mclk div
 * @return    status code
 *            - 0 success
 *            - 1 set mclk div failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_mclk_div(wm8978_handle_t *handle, wm8978_mclk_div_t d);

/**
 * @brief     set bclk div
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] d is the bclk div
 * @return    status code
 *            - 0 success
 *            - 1 set bclk div failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_bclk_div(wm8978_handle_t *handle, wm8978_bclk_div_t d);

/**
 * @brief     set clock mode
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] mode is the clock mode
 * @return    status code
 *            - 0 success
 *            - 1 set clock mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_clock_mode(wm8978_handle_t *handle, wm8978_clock_mode_t mode);

/**
 * @brief     set approximate sample rate
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] sample is the approximate sample rate
 * @return    status code
 *            - 0 success
 *            - 1 set approximate sample rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_approximate_sample_rate(wm8978_handle_t *handle, wm8978_approximate_sample_t sample);

/**
 * @brief     enable or disable slow clock
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set slow clock failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_slow_clock(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set pll div
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] d is the pll div
 * @return    status code
 *            - 0 success
 *            - 1 set pll div failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_pll_div(wm8978_handle_t *handle, wm8978_pll_div_t d);

/**
 * @brief     set gpio1 polarity
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] polarity is the gpio1 polarity
 * @return    status code
 *            - 0 success
 *            - 1 set gpio1 polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_gpio1_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity);

/**
 * @brief     set gpio1 select
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] sel is the gpio1 select
 * @return    status code
 *            - 0 success
 *            - 1 set gpio1 select failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_gpio1_select(wm8978_handle_t *handle, wm8978_gpio1_sel_t sel);

/**
 * @brief     enable or disable vmid 1
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set vmid 1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_vmid_1(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable vmid 0
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set vmid 0 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_vmid_0(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable jack detection
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set jack detection failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_jack_detection(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set jack gpio
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] sel is the jack gpio select
 * @return    status code
 *            - 0 success
 *            - 1 set jack gpio failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_jack_gpio(wm8978_handle_t *handle, wm8978_jack_sel_t sel);

/**
 * @brief     enable or disable soft mute
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set soft mute failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_soft_mute(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set dac oversample rate
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] rate is the dac oversample rate
 * @return    status code
 *            - 0 success
 *            - 1 set dac oversample rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_dac_oversample_rate(wm8978_handle_t *handle, wm8978_dac_oversample_rate_t rate);

/**
 * @brief     enable or disable amute
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set amute failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_amute(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set right dac output polarity
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] polarity is the right dac output polarity
 * @return    status code
 *            - 0 success
 *            - 1 set right dac output polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_dac_output_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity);

/**
 * @brief     set left dac output polarity
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] polarity is the left dac output polarity
 * @return    status code
 *            - 0 success
 *            - 1 set left dac output polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_dac_output_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity);

/**
 * @brief     set dac left volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value, update once flag
 * @param[in] volume is the set volume
 * @return    status code
 *            - 0 success
 *            - 1 set dac left volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_dac_left_volume(wm8978_handle_t *handle, wm8978_bool_t enable, uint8_t volume);

/**
 * @brief     set dac right volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value, update once flag
 * @param[in] volume is the set volume
 * @return    status code
 *            - 0 success
 *            - 1 set dac right volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_dac_right_volume(wm8978_handle_t *handle, wm8978_bool_t enable, uint8_t volume);

/**
 * @brief     set jack logic 1
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] jack is the jack operation
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set jack logic 1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_jack_logic_1(wm8978_handle_t *handle, wm8978_jack_t jack, wm8978_bool_t enable);

/**
 * @brief     set jack logic 0
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] jack is the jack operation
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set jack logic 0 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_jack_logic_0(wm8978_handle_t *handle, wm8978_jack_t jack, wm8978_bool_t enable);

/**
 * @brief     enable or disable high pass filter
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set high pass filter failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_high_pass_filter(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set chip mode
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] mode is the set mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_mode(wm8978_handle_t *handle, wm8978_mode_t mode);

/**
 * @brief     set high pass filter cut off
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] cut is the high pass filter cut off
 * @return    status code
 *            - 0 success
 *            - 1 set high pass filter cut off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_high_pass_filter_cut_off(wm8978_handle_t *handle, wm8978_high_pass_filter_cut_off_t cut);

/**
 * @brief     set adc oversample rate
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] rate is the adc oversample rate
 * @return    status code
 *            - 0 success
 *            - 1 set adc oversample rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_adc_oversample_rate(wm8978_handle_t *handle, wm8978_adc_oversample_rate_t rate);

/**
 * @brief     set adc right channel polarity
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] polarity is the adc polarity
 * @return    status code
 *            - 0 success
 *            - 1 set adc right channel polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_adc_right_channel_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity);

/**
 * @brief     set adc left channel polarity
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] polarity is the adc polarity
 * @return    status code
 *            - 0 success
 *            - 1 set adc left channel polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_adc_left_channel_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity);

/**
 * @brief     set adc left volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value, update once flag
 * @param[in] volume is the set volume
 * @return    status code
 *            - 0 success
 *            - 1 set adc left volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_adc_left_volume(wm8978_handle_t *handle, wm8978_bool_t enable, uint8_t volume);

/**
 * @brief     set adc right volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value, update once flag
 * @param[in] volume is the set volume
 * @return    status code
 *            - 0 success
 *            - 1 set adc right volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_adc_right_volume(wm8978_handle_t *handle, wm8978_bool_t enable, uint8_t volume);

/**
 * @brief      convert the volume data to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the volume db
 * @param[out] *reg points to a volume raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_volume_convert_to_register(wm8978_handle_t *handle, float db, uint8_t *reg);

/**
 * @brief      convert the volume register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the volume raw data
 * @param[out] *db points to a volume real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, float *db);

/**
 * @brief     set equaliser apply
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] equaliser is the set equaliser
 * @return    status code
 *            - 0 success
 *            - 1 set equaliser apply failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_equaliser_apply(wm8978_handle_t *handle, wm8978_equaliser_t equaliser);

/**
 * @brief     set eq1 cut off
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] cut_off is the cut off freq
 * @return    status code
 *            - 0 success
 *            - 1 set eq1 cut off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_eq1_cut_off(wm8978_handle_t *handle, wm8978_eq1_band_cut_off_t cut_off);

/**
 * @brief     set eq1 gain
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] gain is the eq1 gain
 * @return    status code
 *            - 0 success
 *            - 1 set eq1 gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 gain > 0x1F
 * @note      none
 */
uint8_t wm8978_set_eq1_gain(wm8978_handle_t *handle, uint8_t gain);

/**
 * @brief     set eq2 bandwidth
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] width is the set bandwidth
 * @return    status code
 *            - 0 success
 *            - 1 set eq2 bandwidth failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_eq2_bandwidth(wm8978_handle_t *handle, wm8978_eq_bandwidth_t width);

/**
 * @brief     set eq2 centre freq
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] freq is the centre freq
 * @return    status code
 *            - 0 success
 *            - 1 set eq2 centre freq failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_eq2_centre_freq(wm8978_handle_t *handle, wm8978_eq2_band_centre_freq_t freq);

/**
 * @brief     set eq2 gain
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] gain is the eq2 gain
 * @return    status code
 *            - 0 success
 *            - 1 set eq2 gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 gain > 0x1F
 * @note      none
 */
uint8_t wm8978_set_eq2_gain(wm8978_handle_t *handle, uint8_t gain);

/**
 * @brief     set eq3 bandwidth
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] width is the set bandwidth
 * @return    status code
 *            - 0 success
 *            - 1 set eq3 bandwidth failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_eq3_bandwidth(wm8978_handle_t *handle, wm8978_eq_bandwidth_t width);

/**
 * @brief     set eq3 centre freq
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] freq is the centre freq
 * @return    status code
 *            - 0 success
 *            - 1 set eq3 centre freq failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_eq3_centre_freq(wm8978_handle_t *handle, wm8978_eq3_band_centre_freq_t freq);

/**
 * @brief     set eq3 gain
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] gain is the eq3 gain
 * @return    status code
 *            - 0 success
 *            - 1 set eq3 gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 gain > 0x1F
 * @note      none
 */
uint8_t wm8978_set_eq3_gain(wm8978_handle_t *handle, uint8_t gain);

/**
 * @brief     set eq4 bandwidth
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] width is the set bandwidth
 * @return    status code
 *            - 0 success
 *            - 1 set eq4 bandwidth failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_eq4_bandwidth(wm8978_handle_t *handle, wm8978_eq_bandwidth_t width);

/**
 * @brief     set eq4 centre freq
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] freq is the centre freq
 * @return    status code
 *            - 0 success
 *            - 1 set eq4 centre freq failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_eq4_centre_freq(wm8978_handle_t *handle, wm8978_eq4_band_centre_freq_t freq);

/**
 * @brief     set eq4 gain
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] gain is the eq4 gain
 * @return    status code
 *            - 0 success
 *            - 1 set eq4 gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 gain > 0x1F
 * @note      none
 */
uint8_t wm8978_set_eq4_gain(wm8978_handle_t *handle, uint8_t gain);

/**
 * @brief     set eq5 cut off
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] cut_off is the cut off freq
 * @return    status code
 *            - 0 success
 *            - 1 set eq5 cut off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_eq5_cut_off(wm8978_handle_t *handle, wm8978_eq5_band_cut_off_t cut_off);

/**
 * @brief     set eq5 gain
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] gain is the eq5 gain
 * @return    status code
 *            - 0 success
 *            - 1 set eq5 gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 gain > 0x1F
 * @note      none
 */
uint8_t wm8978_set_eq5_gain(wm8978_handle_t *handle, uint8_t gain);

/**
 * @brief      convert the eq gain to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the eq gain in db
 * @param[out] *reg points to an eq gain raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_eq_gain_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the eq gain register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the volume raw data
 * @param[out] *db points to an eq gain real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_eq_gain_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable dac digital limiter
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set dac digital limiter failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_dac_digital_limiter(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set dac limiter decay
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] decay is the dac limiter decay
 * @return    status code
 *            - 0 success
 *            - 1 set dac limiter decay failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_dac_limiter_decay(wm8978_handle_t *handle, wm8978_dac_limiter_decay_t decay);

/**
 * @brief     set dac limiter attack
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] attack is the dac limiter attack
 * @return    status code
 *            - 0 success
 *            - 1 set dac limiter attack failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_dac_limiter_attack(wm8978_handle_t *handle, wm8978_dac_limiter_attack_t attack);

/**
 * @brief     set dac limiter level
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] level is the dac limiter level
 * @return    status code
 *            - 0 success
 *            - 1 set dac limiter level failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_dac_limiter_level(wm8978_handle_t *handle, wm8978_dac_limiter_level_t level);

/**
 * @brief     set dac limiter volume boost
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] db is the set db
 * @return    status code
 *            - 0 success
 *            - 1 set dac limiter volume boost failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 db > 12
 * @note      none
 */
uint8_t wm8978_set_dac_limiter_volume_boost(wm8978_handle_t *handle, uint8_t db);

/**
 * @brief     enable or disable notch filter
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set notch filter failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_notch_filter(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set notch filter a0 coefficient bit13 - bit7
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] update_once is a bool value
 * @param[in] coefficient is the set coefficient
 * @return    status code
 *            - 0 success
 *            - 1 set notch filter a0 coefficient failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 coefficient > 0x7F
 * @note      none
 */
uint8_t wm8978_set_notch_filter_a0_coefficient_bit_13_7(wm8978_handle_t *handle, wm8978_bool_t update_once, uint8_t coefficient);

/**
 * @brief     set notch filter a0 coefficient bit6 - bit0
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] update_once is a bool value
 * @param[in] coefficient is the set coefficient
 * @return    status code
 *            - 0 success
 *            - 1 set notch filter a0 coefficient failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 coefficient > 0x7F
 * @note      none
 */
uint8_t wm8978_set_notch_filter_a0_coefficient_bit_6_0(wm8978_handle_t *handle, wm8978_bool_t update_once, uint8_t coefficient);

/**
 * @brief     set notch filter a1 coefficient bit13 - bit7
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] update_once is a bool value
 * @param[in] coefficient is the set coefficient
 * @return    status code
 *            - 0 success
 *            - 1 set notch filter a1 coefficient failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 coefficient > 0x7F
 * @note      none
 */
uint8_t wm8978_set_notch_filter_a1_coefficient_bit_13_7(wm8978_handle_t *handle, wm8978_bool_t update_once, uint8_t coefficient);

/**
 * @brief     set notch filter a1 coefficient bit6 - bit0
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] update_once is a bool value
 * @param[in] coefficient is the set coefficient
 * @return    status code
 *            - 0 success
 *            - 1 set notch filter a1 coefficient failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 coefficient > 0x7F
 * @note      none
 */
uint8_t wm8978_set_notch_filter_a1_coefficient_bit_6_0(wm8978_handle_t *handle, wm8978_bool_t update_once, uint8_t coefficient);

/**
 * @brief     set alc
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] alc is the set alc
 * @return    status code
 *            - 0 success
 *            - 1 set alc failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_alc(wm8978_handle_t *handle, wm8978_alc_t alc);

/**
 * @brief     set alc max gain
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] gain is the alc max gain
 * @return    status code
 *            - 0 success
 *            - 1 set alc max gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_alc_max_gain(wm8978_handle_t *handle, wm8978_max_gain_t gain);

/**
 * @brief     set alc min gain
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] gain is the alc min gain
 * @return    status code
 *            - 0 success
 *            - 1 set alc min gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_alc_min_gain(wm8978_handle_t *handle, wm8978_min_gain_t gain);

/**
 * @brief     set alc hold time
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] t is the alc hold time
 * @return    status code
 *            - 0 success
 *            - 1 set alc hold time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 t > 0xF
 * @note      none
 */
uint8_t wm8978_set_alc_hold_time(wm8978_handle_t *handle, uint8_t t);

/**
 * @brief      convert the alc hold time to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  ms is the alc hold time in ms
 * @param[out] *reg points to an alc hold time raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_alc_hold_time_convert_to_register(wm8978_handle_t *handle, float ms, uint8_t *reg);

/**
 * @brief      convert the alc hold time register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *ms points to an alc hold time real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_alc_hold_time_convert_to_data(wm8978_handle_t *handle, uint8_t reg, float *ms);

/**
 * @brief     set alc level
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] level is the set level
 * @return    status code
 *            - 0 success
 *            - 1 set alc level failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_alc_level(wm8978_handle_t *handle, wm8978_alc_level_t level);

/**
 * @brief     set alc mode
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] mode is the alc mode
 * @return    status code
 *            - 0 success
 *            - 1 set alc mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_alc_mode(wm8978_handle_t *handle, wm8978_alc_mode_t mode);

/**
 * @brief     set alc decay
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] decay is the set decay
 * @return    status code
 *            - 0 success
 *            - 1 set alc decay failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 decay > 0xF
 * @note      none
 */
uint8_t wm8978_set_alc_decay(wm8978_handle_t *handle, uint8_t decay);

/**
 * @brief     set alc attack
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] attack is the set attack
 * @return    status code
 *            - 0 success
 *            - 1 set alc attack failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 decay > 0xF
 * @note      none
 */
uint8_t wm8978_set_alc_attack(wm8978_handle_t *handle, uint8_t attack);

/**
 * @brief     enable or disable alc noise gate
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set alc noise gate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_alc_noise_gate(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set alc noise gate threshold
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] threshold is the alc noise gate threshold
 * @return    status code
 *            - 0 success
 *            - 1 set alc noise gate threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 threshold > 0x7
 * @note      none
 */
uint8_t wm8978_set_alc_noise_gate_threshold(wm8978_handle_t *handle, uint8_t threshold);

/**
 * @brief      convert the alc noise gate threshold to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the alc noise gate threshold in db
 * @param[out] *reg points to an alc noise gate threshold raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_alc_noise_gate_threshold_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the alc noise gate threshold register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to an alc noise gate threshold real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_alc_noise_gate_threshold_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable mclk divide by 2
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set mclk divide by 2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_mclk_divide_by_2(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set plln
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] n is the set pll
 * @return    status code
 *            - 0 success
 *            - 1 set plln failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 n > 0xF
 * @note      none
 */
uint8_t wm8978_set_plln(wm8978_handle_t *handle, uint8_t n);

/**
 * @brief     set pll freq
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] freq is the pll freq
 * @return    status code
 *            - 0 success
 *            - 1 set pll freq failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_pll_freq(wm8978_handle_t *handle, uint32_t freq);

/**
 * @brief     set depth 3d
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] depth is the 3d depth
 * @return    status code
 *            - 0 success
 *            - 1 set depth 3d failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 depth > 0xF
 * @note      none
 */
uint8_t wm8978_set_depth_3d(wm8978_handle_t *handle, uint8_t depth);

/**
 * @brief      convert the depth 3d to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  percent is the set percent
 * @param[out] *reg points to a depth 3d raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_depth_3d_convert_to_register(wm8978_handle_t *handle, float percent, uint8_t *reg);

/**
 * @brief      convert the depth 3d register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *percent points to a depth 3d real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_depth_3d_convert_to_data(wm8978_handle_t *handle, uint8_t reg, float *percent);

/**
 * @brief     enable or disable mute input to inv rout2 mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set mute input to inv rout2 mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_mute_input_to_inv_rout2_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable inv rout2 mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set inv rout2 mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_inv_rout2_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set beep volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] vol is the set volume
 * @return    status code
 *            - 0 success
 *            - 1 set beep volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vol > 0x7
 * @note      none
 */
uint8_t wm8978_set_beep_volume(wm8978_handle_t *handle, uint8_t vol);

/**
 * @brief      convert the beep volume to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a beep volume raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_beep_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the beep volume register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_beep_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable beep
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set beep failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_beep(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set microphone bias voltage
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] avdd is the set avdd
 * @return    status code
 *            - 0 success
 *            - 1 set microphone bias voltage failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_microphone_bias_voltage(wm8978_handle_t *handle, wm8978_avdd_t avdd);

/**
 * @brief     enable or disable right channel input pga positive
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right channel input pga positive failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_channel_input_pga_positive(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right channel input pga negative
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right channel input pga negative failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_channel_input_pga_negative(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right channel input pga amplifier positive
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right channel input pga amplifier positive failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_channel_input_pga_amplifier_positive(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left channel input pga positive
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left channel input pga positive failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_channel_input_pga_positive(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left channel input pga negative
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left channel input pga negative failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_channel_input_pga_negative(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left channel input pga amplifier positive
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left channel input pga amplifier positive failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_channel_input_pga_amplifier_positive(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left input pga update
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left input pga update failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_input_pga_update(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left channel input pga zero cross
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left channel input pga zero cross failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_channel_input_pga_zero_cross(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left channel input pga mute
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left channel input pga mute failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_channel_input_pga_mute(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set left channel input pga volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] volume is the set volume
 * @return    status code
 *            - 0 success
 *            - 1 set left channel input pga volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 volume > 0x3F
 * @note      none
 */
uint8_t wm8978_set_left_channel_input_pga_volume(wm8978_handle_t *handle, uint8_t volume);

/**
 * @brief      convert the left channel input pga volume to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a volume raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_left_channel_input_pga_volume_convert_to_register(wm8978_handle_t *handle, float db, uint8_t *reg);

/**
 * @brief      convert the left channel input pga volume register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a volume real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_left_channel_input_pga_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, float *db);

/**
 * @brief     enable or disable right input pga update
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right input pga update failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_input_pga_update(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right channel input pga zero cross
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right channel input pga zero cross failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_channel_input_pga_zero_cross(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right channel input pga mute
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right channel input pga mute failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_channel_input_pga_mute(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set right channel input pga volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] volume is the set volume
 * @return    status code
 *            - 0 success
 *            - 1 set right channel input pga volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 volume > 0x3F
 * @note      none
 */
uint8_t wm8978_set_right_channel_input_pga_volume(wm8978_handle_t *handle, uint8_t volume);

/**
 * @brief      convert the right channel input pga volume to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a volume raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_right_channel_input_pga_volume_convert_to_register(wm8978_handle_t *handle, float db, uint8_t *reg);

/**
 * @brief      convert the right channel input pga volume register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a volume real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_right_channel_input_pga_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, float *db);

/**
 * @brief     enable or disable left channel input pga boost
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left channel input pga boost failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_channel_input_pga_boost(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set left channel input boost stage
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] stage is the set stage
 * @return    status code
 *            - 0 success
 *            - 1 set left channel input boost stage failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 stage > 0x7
 * @note      none
 */
uint8_t wm8978_set_left_channel_input_boost_stage(wm8978_handle_t *handle, uint8_t stage);

/**
 * @brief      convert the left channel input boost stage to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a volume raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_left_channel_input_boost_stage_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the left channel input boost stage register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_left_channel_input_boost_stage_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     set auxiliary amplifier left channel input boost stage
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] stage is the set stage
 * @return    status code
 *            - 0 success
 *            - 1 set auxiliary amplifier left channel input boost stage failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 stage > 0x7
 * @note      none
 */
uint8_t wm8978_set_auxiliary_amplifier_left_channel_input_boost_stage(wm8978_handle_t *handle, uint8_t stage);

/**
 * @brief      convert the auxiliary amplifier left channel input boost stage to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a volume raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_auxiliary_amplifier_left_channel_input_boost_stage_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the auxiliary amplifier left channel input boost stage register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_auxiliary_amplifier_left_channel_input_boost_stage_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable right channel input pga boost
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right channel input pga boost failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_channel_input_pga_boost(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set right channel input boost stage
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] stage is the set stage
 * @return    status code
 *            - 0 success
 *            - 1 set right channel input boost stage failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 stage > 0x7
 * @note      none
 */
uint8_t wm8978_set_right_channel_input_boost_stage(wm8978_handle_t *handle, uint8_t stage);

/**
 * @brief      convert the right channel input boost stage to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a volume raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_right_channel_input_boost_stage_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the right channel input boost stage register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_right_channel_input_boost_stage_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     set auxiliary amplifier right channel input boost stage
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] stage is the set stage
 * @return    status code
 *            - 0 success
 *            - 1 set auxiliary amplifier right channel input boost stage failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 stage > 0x7
 * @note      none
 */
uint8_t wm8978_set_auxiliary_amplifier_right_channel_input_boost_stage(wm8978_handle_t *handle, uint8_t stage);

/**
 * @brief      convert the auxiliary amplifier right channel input boost stage to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a db raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_auxiliary_amplifier_right_channel_input_boost_stage_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the auxiliary amplifier right channel input boost stage register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_auxiliary_amplifier_right_channel_input_boost_stage_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable left dac output to right output mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left dac output to right output mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_dac_output_to_right_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right dac output to left output mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right dac output to left output mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_dac_output_to_left_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable out4 boost
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set out4 boost failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_out4_boost(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable out3 boost
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set out3 boost failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_out3_boost(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable speaker boost
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set speaker boost failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_speaker_boost(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable thermal shutdown
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set thermal shutdown failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_thermal_shutdown(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set vref to analogue output resistance
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] vref is the set vref
 * @return    status code
 *            - 0 success
 *            - 1 set vref to analogue output resistance failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_vref_to_analogue_output_resistance(wm8978_handle_t *handle, wm8978_vref_t vref);

/**
 * @brief     set aux left channel input to left mixer volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] vol is the set vol
 * @return    status code
 *            - 0 success
 *            - 1 set aux left channel input to left mixer volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vol > 0x7
 * @note      none
 */
uint8_t wm8978_set_aux_left_channel_input_to_left_mixer_volume(wm8978_handle_t *handle, uint8_t vol);

/**
 * @brief      convert the aux left channel input to left mixer volume to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a db raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_aux_left_channel_input_to_left_mixer_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the aux left channel input to left mixer volume register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_aux_left_channel_input_to_left_mixer_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable left auxiliary input to left channel output mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left auxiliary input to left channel output mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_auxiliary_input_to_left_channel_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set left bypass volume control to output channel mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] vol is the set vol
 * @return    status code
 *            - 0 success
 *            - 1 set left bypass volume control to output channel mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vol > 0x7
 * @note      none
 */
uint8_t wm8978_set_left_bypass_volume_control_to_output_channel_mixer(wm8978_handle_t *handle, uint8_t vol);

/**
 * @brief      convert the left bypass volume control to output channel mixer to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a db raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_left_bypass_volume_control_to_output_channel_mixer_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the left bypass volume control to output channel mixer register raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_left_bypass_volume_control_to_output_channel_mixer_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable left bypass path to left output mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left bypass path to left output mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_bypass_path_to_left_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left dac output to left output mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left dac output to left output mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_dac_output_to_left_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set aux right channel input to right mixer volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] vol is the set vol
 * @return    status code
 *            - 0 success
 *            - 1 set aux right channel input to right mixer volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vol > 0x7
 * @note      none
 */
uint8_t wm8978_set_aux_right_channel_input_to_right_mixer_volume(wm8978_handle_t *handle, uint8_t vol);

/**
 * @brief      convert the aux right channel input to right mixer volume to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a db raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_aux_right_channel_input_to_right_mixer_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the aux right channel input to right mixer volume raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_aux_right_channel_input_to_right_mixer_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable right auxiliary input to right channel output mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right auxiliary input to right channel output mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_auxiliary_input_to_right_channel_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set right bypass volume control to output channel mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] vol is the set vol
 * @return    status code
 *            - 0 success
 *            - 1 set right bypass volume control to output channel mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vol > 0x7
 * @note      none
 */
uint8_t wm8978_set_right_bypass_volume_control_to_output_channel_mixer(wm8978_handle_t *handle, uint8_t vol);

/**
 * @brief      convert the right bypass volume control to output channel mixer to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a db raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_right_bypass_volume_control_to_output_channel_mixer_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the right bypass volume control to output channel mixer raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_right_bypass_volume_control_to_output_channel_mixer_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable right bypass path to right output mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right bypass path to right output mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_bypass_path_to_right_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right dac output to right output mixer
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right dac output to right output mixer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_dac_output_to_right_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable lout1 update
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set lout1 update failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_lout1_update(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable lout1 headphone volume zero cross
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set lout1 headphone volume zero cross failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_lout1_headphone_volume_zero_cross(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable lout1 left headphone output mute
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set lout1 left headphone output mute failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_lout1_left_headphone_output_mute(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set lout1 left headphone output volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] vol is the set volume
 * @return    status code
 *            - 0 success
 *            - 1 set lout1 left headphone output volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vol > 0x3F
 * @note      none
 */
uint8_t wm8978_set_lout1_left_headphone_output_volume(wm8978_handle_t *handle, uint8_t vol);

/**
 * @brief      convert the lout1 left headphone output volume to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a db raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_lout1_left_headphone_output_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the lout1 left headphone output volume raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_lout1_left_headphone_output_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable rout1 update
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set rout1 update failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_rout1_update(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable rout1 headphone volume zero cross
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set rout1 headphone volume zero cross failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_rout1_headphone_volume_zero_cross(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable rout1 right headphone output mute
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set rout1 right headphone output mute failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_rout1_right_headphone_output_mute(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set rout1 right headphone output volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] vol is the set volume
 * @return    status code
 *            - 0 success
 *            - 1 set rout1 right headphone output volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vol > 0x3F
 * @note      none
 */
uint8_t wm8978_set_rout1_right_headphone_output_volume(wm8978_handle_t *handle, uint8_t vol);

/**
 * @brief      convert the rout1 right headphone output volume to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a db raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_rout1_right_headphone_output_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the rout1 right headphone output volume raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_rout1_right_headphone_output_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable lout2 update
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set lout2 update failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_lout2_update(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable lout2 speaker volume zero cross
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set lout2 speaker volume zero cross failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_lout2_speaker_volume_zero_cross(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable lout2 left speaker output mute
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set lout2 left speaker output mute failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_lout2_left_speaker_output_mute(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set lout2 left speaker output volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] vol is the set volume
 * @return    status code
 *            - 0 success
 *            - 1 set lout2 left speaker output volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vol > 0x3F
 * @note      none
 */
uint8_t wm8978_set_lout2_left_speaker_output_volume(wm8978_handle_t *handle, uint8_t vol);

/**
 * @brief      convert the lout2 left speaker output volume to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a db raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_lout2_left_speaker_output_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the lout2 left speaker output volume raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_lout2_left_speaker_output_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable rout2 update
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set rout2 update failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_rout2_update(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable rout2 speaker volume zero cross
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set rout2 speaker volume zero cross failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_rout2_speaker_volume_zero_cross(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable rout2 right speaker output mute
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set rout2 right speaker output mute failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_rout2_right_speaker_output_mute(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     set rout2 right speaker output volume
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] vol is the set volume
 * @return    status code
 *            - 0 success
 *            - 1 set rout2 right speaker output volume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vol > 0x3F
 * @note      none
 */
uint8_t wm8978_set_rout2_right_speaker_output_volume(wm8978_handle_t *handle, uint8_t vol);

/**
 * @brief      convert the rout2 right speaker output volume to the register raw data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  db is the set db
 * @param[out] *reg points to a db raw data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_rout2_right_speaker_output_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg);

/**
 * @brief      convert the rout2 right speaker output volume raw data to the real data
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the raw data
 * @param[out] *db points to a db real data buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wm8978_rout2_right_speaker_output_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db);

/**
 * @brief     enable or disable out3 mute
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set out3 mute failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_out3_mute(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable out4 mixer output to out3
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set out4 mixer output to out3 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_out4_mixer_output_to_out3(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left adc input to out3
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left adc input to out3 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_adc_input_to_out3(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left dac mixer to out3
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left dac mixer to out3 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_dac_mixer_to_out3(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left dac output to out3
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left dac output to out3 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_dac_output_to_out3(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable out4 mute
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set out4 mute failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_out4_mute(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable out4 attenuated by 6db
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set out4 attenuated by 6db failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_out4_attenuated_by_6db(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left dac mixer to out4
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left dac mixer to out4 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_dac_mixer_to_out4(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable left dac to out4
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set left dac to out4 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_left_dac_to_out4(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right adc input to out4
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right adc input to out4 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_adc_input_to_out4(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right dac mixer to out4
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right dac mixer to out4 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_dac_mixer_to_out4(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @brief     enable or disable right dac output to out4
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set right dac output to out4 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_right_dac_output_to_out4(wm8978_handle_t *handle, wm8978_bool_t enable);

/**
 * @}
 */

/**
 * @defgroup wm8978_extend_driver wm8978 extend driver function
 * @brief    wm8978 extend driver modules
 * @ingroup  wm8978_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] reg is the iic register address
 * @param[in] value is the data write to the register
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wm8978_set_reg(wm8978_handle_t *handle, uint8_t reg, uint16_t value);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
