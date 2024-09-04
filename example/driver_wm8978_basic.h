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
 * @file      driver_wm8978_basic.h
 * @brief     driver wm8978 basic header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2023-07-31
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2023-07-31  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_WM8978_BASIC_H
#define DRIVER_WM8978_BASIC_H

#include "driver_wm8978_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup wm8978_example_driver wm8978 example driver function
 * @brief    wm8978 example driver modules
 * @ingroup  wm8978_driver
 * @{
 */

/**
 * @brief wm8978 basic example default definition
 */
#define WM8978_BASIC_DEFAULT_DC_BUFFER                                                    WM8978_BOOL_FALSE                            /**< disable dc buffer */
#define WM8978_BASIC_DEFAULT_OUT4_MIXER                                                   WM8978_BOOL_FALSE                            /**< disable out4 mixer */
#define WM8978_BASIC_DEFAULT_OUT3_MIXER                                                   WM8978_BOOL_FALSE                            /**< disable out3 mixer */
#define WM8978_BASIC_DEFAULT_PLL                                                          WM8978_BOOL_FALSE                            /**< disable pll */
#define WM8978_BASIC_DEFAULT_MICROPHONE_BIAS                                              WM8978_BOOL_TRUE                             /**< enable microphone bias */
#define WM8978_BASIC_DEFAULT_UNUSED_INPUT_OUTPUT_TIE_OFF_BUFFER                           WM8978_BOOL_FALSE                            /**< disable unused */
#define WM8978_BASIC_DEFAULT_ANALOGUE_AMPLIFIER_BIAS                                      WM8978_BOOL_TRUE                             /**< enable analogue */
#define WM8978_BASIC_DEFAULT_REFERENCE_IMPEDANCE                                          WM8978_IMPEDANCE_5K                          /**< 5k */
#define WM8978_BASIC_DEFAULT_OUT4                                                         WM8978_BOOL_FALSE                            /**< disable out4 */
#define WM8978_BASIC_DEFAULT_OUT3                                                         WM8978_BOOL_FALSE                            /**< disable out3 */
#define WM8978_BASIC_DEFAULT_BCLK_POLARITY                                                WM8978_POLARITY_NORMAL                       /**< normal polarity */
#define WM8978_BASIC_DEFAULT_LRCLK_POLARITY                                               WM8978_POLARITY_NORMAL                       /**< normal polarity */
#define WM8978_BASIC_DEFAULT_DAC_APPEAR                                                   WM8978_APPEAR_LEFT                           /**< appear left */
#define WM8978_BASIC_DEFAULT_ADC_APPEAR                                                   WM8978_APPEAR_LEFT                           /**< appear left */
#define WM8978_BASIC_DEFAULT_COMPANDING_8BIT_MODE                                         WM8978_BOOL_FALSE                            /**< disable companding 8bit mode */
#define WM8978_BASIC_DEFAULT_DATA_FORMAT                                                  WM8978_DATA_FORMAT_IIS                       /**< iis mode */
#define WM8978_BASIC_DEFAULT_LOOP_BACK                                                    WM8978_BOOL_FALSE                            /**< disable loop back */
#define WM8978_BASIC_DEFAULT_CLKSEL                                                       WM8978_CLKSEL_MCLK                           /**< mclk */
#define WM8978_BASIC_DEFAULT_MCLK_DIV                                                     WM8978_MCLK_DIV_BY_1                         /**< div 1 */
#define WM8978_BASIC_DEFAULT_BCLK_DIV                                                     WM8978_BCLK_DIV_BY_1                         /**< dib 1 */
#define WM8978_BASIC_DEFAULT_CLOCK_MODE                                                   WM8978_CLOCK_MODE_INPUT                      /**< input mode */
#define WM8978_BASIC_DEFAULT_APPROXIMATE_SAMPLE                                           WM8978_APPROXIMATE_SAMPLE_48_KHZ             /**< 48khz */
#define WM8978_BASIC_DEFAULT_SLOW_CLOCK                                                   WM8978_BOOL_FALSE                            /**< disable slow clock */
#define WM8978_BASIC_DEFAULT_PLL_DIV                                                      WM8978_PLL_DIV_BY_1                          /**< div 1 */
#define WM8978_BASIC_DEFAULT_GPIO1_POLARITY                                               WM8978_POLARITY_NORMAL                       /**< polarity normal */
#define WM8978_BASIC_DEFAULT_GPIO1_SELECT                                                 WM8978_GPIO1_SEL_INPUT                       /**< input */
#define WM8978_BASIC_DEFAULT_VMID_1                                                       WM8978_BOOL_TRUE                             /**< enable vmid 1 */
#define WM8978_BASIC_DEFAULT_VMID_0                                                       WM8978_BOOL_TRUE                             /**< enable vmid 0 */
#define WM8978_BASIC_DEFAULT_JACK_DETECTION                                               WM8978_BOOL_FALSE                            /**< disable jack detection */
#define WM8978_BASIC_DEFAULT_JACK_GPIO                                                    WM8978_JACK_SEL_GPIO2                        /**< use gpio2 */
#define WM8978_BASIC_DEFAULT_SOFT_MUTE                                                    WM8978_BOOL_FALSE                            /**< disable soft mute */
#define WM8978_BASIC_DEFAULT_DAC_OVERSAMPLE_RATE                                          WM8978_DAC_OVERSAMPLE_RATE_128X              /**< 128x */
#define WM8978_BASIC_DEFAULT_AMUTE                                                        WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_RIGHT_DAC_OUTPUT_POLARITY                                    WM8978_POLARITY_NORMAL                       /**< normal polarity */
#define WM8978_BASIC_DEFAULT_LEFT_DAC_OUTPUT_POLARITY                                     WM8978_POLARITY_NORMAL                       /**< normal polarity */
#define WM8978_BASIC_DEFAULT_DAC_VOLUME                                                   -10                                          /**< -10db */
#define WM8978_BASIC_DEFAULT_JACK_LOGIC_0_OUT1                                            WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_JACK_LOGIC_1_OUT1                                            WM8978_BOOL_TRUE                             /**< disable */
#define WM8978_BASIC_DEFAULT_JACK_LOGIC_0_OUT2                                            WM8978_BOOL_TRUE                             /**< disable */
#define WM8978_BASIC_DEFAULT_JACK_LOGIC_1_OUT2                                            WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_JACK_LOGIC_0_OUT3                                            WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_JACK_LOGIC_0_OUT4                                            WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_JACK_LOGIC_1_OUT3                                            WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_JACK_LOGIC_1_OUT4                                            WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_HIGH_PASS_FILTER                                             WM8978_BOOL_FALSE                            /**< disable high pass filter */
#define WM8978_BASIC_DEFAULT_MODE                                                         WM8978_MODE_AUDIO                            /**< audio mode */
#define WM8978_BASIC_DEFAULT_HIGH_PASS_FILTER_CUT_OFF                                     WM8978_HIGH_PASS_FILTER_CUT_OFF_0            /**< cut off 0 */
#define WM8978_BASIC_DEFAULT_ADC_OVERSAMPLE_RATE                                          WM8978_ADC_OVERSAMPLE_RATE_128X              /**< 128x */
#define WM8978_BASIC_DEFAULT_ADC_RIGHT_CHANNEL_POLARITY                                   WM8978_POLARITY_NORMAL                       /**< normal polarity */
#define WM8978_BASIC_DEFAULT_ADC_LEFT_CHANNEL_POLARITY                                    WM8978_POLARITY_NORMAL                       /**< normal polarity */
#define WM8978_BASIC_DEFAULT_ADC_VOLUME                                                   -10                                          /**< -10db */
#define WM8978_BASIC_DEFAULT_EQUALISER_APPLY                                              WM8978_EQUALISER_APPLIED_TO_DAC              /**< to dac */
#define WM8978_BASIC_DEFAULT_EQ1_BAND_CUT_OFF                                             WM8978_EQ1_BAND_CUT_OFF_80HZ                 /**< cut off 80hz */
#define WM8978_BASIC_DEFAULT_EQ1_GAIN                                                     0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_EQ2_BANDWIDTH                                                WM8978_EQ_BANDWIDTH_WIDE                     /**< bandwidth wide */
#define WM8978_BASIC_DEFAULT_EQ2_BAND_CENTRE_FREQ                                         WM8978_EQ2_BAND_CENTRE_FREQ_385HZ            /**< 385hz */
#define WM8978_BASIC_DEFAULT_EQ2_GAIN                                                     0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_EQ3_BANDWIDTH                                                WM8978_EQ_BANDWIDTH_WIDE                     /**< bandwidth wide */
#define WM8978_BASIC_DEFAULT_EQ3_BAND_CENTRE_FREQ                                         WM8978_EQ3_BAND_CENTRE_FREQ_1100HZ           /**< 1100hz */
#define WM8978_BASIC_DEFAULT_EQ3_GAIN                                                     0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_EQ4_BANDWIDTH                                                WM8978_EQ_BANDWIDTH_WIDE                     /**< bandwidth wide */
#define WM8978_BASIC_DEFAULT_EQ4_BAND_CENTRE_FREQ                                         WM8978_EQ4_BAND_CENTRE_FREQ_3200HZ           /**< 3200hz */
#define WM8978_BASIC_DEFAULT_EQ4_GAIN                                                     0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_EQ5_BAND_CUT_OFF                                             WM8978_EQ5_BAND_CUT_OFF_11700HZ              /**< 11700hz */
#define WM8978_BASIC_DEFAULT_EQ5_GAIN                                                     0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_DAC_DIGITAL_LIMITER                                          WM8978_BOOL_TRUE                             /**< enable digital limiter */
#define WM8978_BASIC_DEFAULT_DAC_LIMITER_DECAY                                            WM8978_DAC_LIMITER_DECAY_192MS               /**< 192ms */
#define WM8978_BASIC_DEFAULT_DAC_LIMITER_ATTACK                                           WM8978_DAC_LIMITER_ATTACK_12MS               /**< 12ms */
#define WM8978_BASIC_DEFAULT_DAC_LIMITER_LEVEL                                            WM8978_DAC_LIMITER_LEVEL_NEGATIVE_1DB        /**< -1db */
#define WM8978_BASIC_DEFAULT_DAC_LIMITER_VOLUME_BOOST                                     12                                           /**< 12db */
#define WM8978_BASIC_DEFAULT_NOTCH_FILTER                                                 WM8978_BOOL_FALSE                            /**< disable notch */
#define WM8978_BASIC_DEFAULT_NOTCH_FILTER_A0_BIT_13_7                                     0x00                                         /**< 0x00 */
#define WM8978_BASIC_DEFAULT_NOTCH_FILTER_A0_BIT_16_0                                     0x00                                         /**< 0x00 */
#define WM8978_BASIC_DEFAULT_NOTCH_FILTER_A1_BIT_13_7                                     0x00                                         /**< 0x00 */
#define WM8978_BASIC_DEFAULT_NOTCH_FILTER_A1_BIT_16_0                                     0x00                                         /**< 0x00 */
#define WM8978_BASIC_DEFAULT_ALC                                                          WM8978_ALC_BOTH                              /**< both */
#define WM8978_BASIC_DEFAULT_ALC_MAX_GAIN                                                 WM8978_MAX_GAIN_35P25_DB                     /**< 35.25db */
#define WM8978_BASIC_DEFAULT_ALC_MIN_GAIN                                                 WM8978_MIN_GAIN_NEGATIVE_12_DB               /**< -12db */
#define WM8978_BASIC_DEFAULT_ALC_HOLD_TIME                                                12.0f                                        /**< 12 ms */
#define WM8978_BASIC_DEFAULT_ALC_LEVEL                                                    WM8978_ALC_LEVEL_NEGATIVE_3                  /**< -3 */
#define WM8978_BASIC_DEFAULT_ALC_MODE                                                     WM8978_ALC_MODE_ALC                          /**< alc mode */
#define WM8978_BASIC_DEFAULT_ALC_DECAY                                                    0x00                                         /**< 0x00 */
#define WM8978_BASIC_DEFAULT_ALC_ATTACK                                                   0x00                                         /**< 0x00 */
#define WM8978_BASIC_DEFAULT_ALC_NOISE_GATE                                               WM8978_BOOL_TRUE                             /**< enable noise gate */
#define WM8978_BASIC_DEFAULT_ALC_NOISE_GATE_THRESHOLD                                     -39                                          /**< -39db */
#define WM8978_BASIC_DEFAULT_MCLK_DIVIDE_BY_2                                             WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_PLLN                                                         0x00                                         /**< 0x00 */
#define WM8978_BASIC_DEFAULT_PLL_FREQ                                                     0x00000000                                   /**< 0x00000000 */
#define WM8978_BASIC_DEFAULT_DEPTH_3D                                                     0.00f                                        /**< 0% */
#define WM8978_BASIC_DEFAULT_RIGHT_OUT1                                                   WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_LEFT_OUT1                                                    WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_RIGHT_CHANNEL_INPUT_BOOST                                    WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_LEFT_CHANNEL_INPUT_BOOST                                     WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_RIGHT_OUT2                                                   WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_LEFT_OUT2                                                    WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_RIGHT_OUTPUT_CHANNEL_MIXER                                   WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_LEFT_OUTPUT_CHANNEL_MIXER                                    WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_MUTE_INPUT_TO_INV_ROUT2_MIXER                                WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_INV_ROUT2_MIXER                                              WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_BEEP_VOLUME                                                  -15                                          /**< -15db */
#define WM8978_BASIC_DEFAULT_BEEP                                                         WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_MICROPHONE_BIAS_VOLTAGE                                      WM8978_AVDD_0P9                              /**< 0.9 avdd */
#define WM8978_BASIC_DEFAULT_RIGHT_CHANNEL_INPUT_PGA_POSITIVE                             WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_LEFT_CHANNEL_INPUT_PGA_POSITIVE                              WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_LEFT_DAC_OUTPUT_TO_RIGHT_OUTPUT_MIXER                        WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_RIGHT_DAC_OUTPUT_TO_LEFT_OUTPUT_MIXER                        WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_OUT4_BOOST                                                   WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_OUT3_BOOST                                                   WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_SPEAKER_BOOST                                                WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_THERMAL_SHUTDOWN                                             WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_VREF                                                         WM8978_VREF_1K                               /**< 1k */
#define WM8978_BASIC_DEFAULT_OUT3_MUTE                                                    WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_OUT4_MIXER_OUTPUT_TO_OUT3                                    WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_LEFT_ADC_INPUT_TO_OUT3                                       WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_LEFT_DAC_MIXER_TO_OUT3                                       WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_LEFT_DAC_OUTPUT_TO_OUT3                                      WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_OUT4_MUTE                                                    WM8978_BOOL_TRUE                             /**< enable */
#define WM8978_BASIC_DEFAULT_OUT4_ATTENUATED_BY_6DB                                       WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_LEFT_DAC_MIXER_TO_OUT4                                       WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_LEFT_DAC_TO_OUT4                                             WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_RIGHT_ADC_INPUT_TO_OUT4                                      WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_RIGHT_DAC_MIXER_TO_OUT4                                      WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_RIGHT_DAC_OUTPUT_TO_OUT4                                     WM8978_BOOL_FALSE                            /**< disable */
#define WM8978_BASIC_DEFAULT_LEFT_CHANNEL_INPUT_BOOST_STATA                               0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_RIGHT_CHANNEL_INPUT_BOOST_STATA                              0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_LEFT_BYPASS_VOLUME_CONTROL_TO_OUTPUT_CHANNEL_MIXER           0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_RIGHT_BYPASS_VOLUME_CONTROL_TO_OUTPUT_CHANNEL_MIXER          0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_LEFT_CHANNEL_INPUT_PGA_VOLUME                                0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_RIGHT_CHANNEL_INPUT_PGA_VOLUME                               0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_LOUT2_LEFT_SPEAKER_OUTPUT_VOLUME                             0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_LOUT2_RIGHT_SPEAKER_OUTPUT_VOLUME                            0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_LOUT1_LEFT_HEADPHONE_OUTPUT_VOLUME                           0                                            /**< 0db */
#define WM8978_BASIC_DEFAULT_LOUT1_RIGHT_HEADPHONE_OUTPUT_VOLUME                          0                                            /**< 0db */

/**
 * @brief wm8978 basic mode enumeration definition
 */
typedef enum
{
    WM8978_BASIC_MODE_PLAY   = 0x00,        /**< play mode */
    WM8978_BASIC_MODE_RECORD = 0x01,        /**< record mode */
} wm8978_basic_mode_t;

/**
 * @brief     basic example init
 * @param[in] mode is the basic mode
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t wm8978_basic_init(wm8978_basic_mode_t mode);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t wm8978_basic_deinit(void);

/**
 * @brief     basic example config
 * @param[in] companding is the set companding
 * @param[in] channel is the set channel
 * @param[in] length is the word length
 * @return    status code
 *            - 0 success
 *            - 1 config failed
 * @note      none
 */
uint8_t wm8978_basic_config(wm8978_companding_t companding, wm8978_channel_t channel, wm8978_word_length_t length);

/**
 * @brief     basic example set dac volume
 * @param[in] db is the set db
 * @return    status code
 *            - 0 success
 *            - 1 set dac volume failed
 * @note      -127.0f <= db <= 0.0f
 */
uint8_t wm8978_basic_set_dac_volume(float db);

/**
 * @brief  basic example set dac mute
 * @return status code
 *         - 0 success
 *         - 1 set dac mute failed
 * @note   none
 */
uint8_t wm8978_basic_set_dac_mute(void);

/**
 * @brief     basic example set adc volume
 * @param[in] db is the set db
 * @return    status code
 *            - 0 success
 *            - 1 set adc volume failed
 * @note      -127.0f <= db <= 0.0f
 */
uint8_t wm8978_basic_set_adc_volume(float db);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
