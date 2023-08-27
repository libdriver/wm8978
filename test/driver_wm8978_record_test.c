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
 * @file      driver_wm8978_record_test.c
 * @brief     driver wm8978 record test source file
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
 
#include "driver_wm8978_record_test.h"
#include <stdlib.h>

static wav_handle_t gs_wav_handle;       /**< wav handle */
static wm8978_handle_t gs_handle;        /**< wm8978 handle */

/**
 * @brief  wm8978 config
 * @return status code
 *         - 0 success
 *         - 1 config failed
 * @note   none
 */
static uint8_t a_wm8978_config(void)
{
    uint8_t res;
    uint8_t reg;
    
    /* disable dc buffer */
    res = wm8978_set_dc_buffer(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable out4 mixer */
    res = wm8978_set_out4_mixer(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable out3 mixer */
    res = wm8978_set_out3_mixer(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable pll */
    res = wm8978_set_pll(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable microphone bias */
    res = wm8978_set_microphone_bias(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable analogue amplifier bias */
    res = wm8978_set_analogue_amplifier_bias(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable unused input output tie off buffer */
    res = wm8978_set_unused_input_output_tie_off_buffer(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* set reference impedance 5k */
    res = wm8978_set_reference_impedance(&gs_handle, WM8978_IMPEDANCE_5K);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable right out1 */
    res = wm8978_set_right_out1(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable left out1 */
    res = wm8978_set_left_out1(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable sleep */
    res = wm8978_set_sleep(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable right channel input boost */
    res = wm8978_set_right_channel_input_boost(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable left channel input boost */
    res = wm8978_set_left_channel_input_boost(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable right channel input pga */
    res = wm8978_set_right_channel_input_pga(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable left channel input pga */
    res = wm8978_set_left_channel_input_pga(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable right channel adc */
    res = wm8978_set_right_channel_adc(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable left channel adc */
    res = wm8978_set_left_channel_adc(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable out4 */
    res = wm8978_set_out4(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable out3 */
    res = wm8978_set_out3(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable left out2 */
    res = wm8978_set_left_out2(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable right out2 */
    res = wm8978_set_right_out2(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable right output channel mixer */
    res = wm8978_set_right_output_channel_mixer(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable left output channel mixer */
    res = wm8978_set_left_output_channel_mixer(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable right channel dac */
    res = wm8978_set_right_channel_dac(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable left channel dac */
    res = wm8978_set_left_channel_dac(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* bclk polarity normal */
    res = wm8978_set_bclk_polarity(&gs_handle, WM8978_POLARITY_NORMAL);
    if (res != 0)
    {
        return 1;
    }
    
    /* lrclk polarity normal */
    res = wm8978_set_lrclk_polarity(&gs_handle, WM8978_POLARITY_NORMAL);
    if (res != 0)
    {
        return 1;
    }
    
    /* iis data format */
    res = wm8978_set_data_format(&gs_handle, WM8978_DATA_FORMAT_IIS);
    if (res != 0)
    {
        return 1;
    }
    
    /* set dac appear left */
    res = wm8978_set_dac_appear(&gs_handle, WM8978_APPEAR_LEFT);
    if (res != 0)
    {
        return 1;
    }
    
    /* set adc appear left */
    res = wm8978_set_adc_appear(&gs_handle,WM8978_APPEAR_LEFT);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable companding 8bit mode */
    res = wm8978_set_companding_8bit_mode(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* set dac companding linear */
    res =  wm8978_set_dac_companding(&gs_handle, WM8978_COMPANDING_LINEAR);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set dac companding failed.\n");
        
        return 1;
    }
    
    /* set adc companding linear */
    res = wm8978_set_adc_companding(&gs_handle, WM8978_COMPANDING_LINEAR);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable loopback */
    res = wm8978_set_loopback(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* set mclk */
    res = wm8978_set_clksel(&gs_handle, WM8978_CLKSEL_MCLK);
    if (res != 0)
    {
        return 1;
    }
    
    /* mclk div by 1 */
    res = wm8978_set_mclk_div(&gs_handle, WM8978_MCLK_DIV_BY_1);
    if (res != 0)
    {
        return 1;
    }
    
    /* bclk div by 1 */
    res = wm8978_set_bclk_div(&gs_handle, WM8978_BCLK_DIV_BY_1);
    if (res != 0)
    {
        return 1;
    }
    
    /* input clock mode */
    res = wm8978_set_clock_mode(&gs_handle, WM8978_CLOCK_MODE_INPUT);
    if (res != 0)
    {
        return 1;
    }
    
    /* set approximate sample rate 48khz */
    res = wm8978_set_approximate_sample_rate(&gs_handle, WM8978_APPROXIMATE_SAMPLE_48_KHZ);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable slow clock */
    res = wm8978_set_slow_clock(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* pll div 1 */
    res = wm8978_set_pll_div(&gs_handle, WM8978_PLL_DIV_BY_1);
    if (res != 0)
    {
        return 1;
    }
    
    /* gpio1 polarity normal */
    res = wm8978_set_gpio1_polarity(&gs_handle, WM8978_POLARITY_NORMAL);
    if (res != 0)
    {
        return 1;
    }
    
    /* set logic 0 */
    res = wm8978_set_gpio1_select(&gs_handle, WM8978_GPIO1_SEL_LOGIC_0);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable vmid 1 */
    res = wm8978_set_vmid_1(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable vmid 0 */
    res = wm8978_set_vmid_0(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable jack detection */
    res = wm8978_set_jack_detection(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* jack use gpio2 */
    res = wm8978_set_jack_gpio(&gs_handle, WM8978_JACK_SEL_GPIO2);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable soft mute */
    res = wm8978_set_soft_mute(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* dac oversample rate 128x */
    res = wm8978_set_dac_oversample_rate(&gs_handle, WM8978_DAC_OVERSAMPLE_RATE_128X);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable amute */
    res = wm8978_set_amute(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* set right dac output polarity normal */
    res = wm8978_set_right_dac_output_polarity(&gs_handle, WM8978_POLARITY_NORMAL);
    if (res != 0)
    {
        return 1;
    }
    
    /* set left dac output polarity normal */
    res = wm8978_set_left_dac_output_polarity(&gs_handle, WM8978_POLARITY_NORMAL);
    if (res != 0)
    {
        return 1;
    }
    
    /* -10db */
    res = wm8978_volume_convert_to_register(&gs_handle, -10, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set dac left volume */
    res = wm8978_set_dac_left_volume(&gs_handle, WM8978_BOOL_TRUE, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set dac right volume */
    res = wm8978_set_dac_right_volume(&gs_handle, WM8978_BOOL_TRUE, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* out1 logic0 disable */
    res = wm8978_set_jack_logic_0(&gs_handle, WM8978_JACK_OUT1, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* out1 logic0 enable */
    res = wm8978_set_jack_logic_1(&gs_handle, WM8978_JACK_OUT1, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* out2 logic0 enable */
    res = wm8978_set_jack_logic_0(&gs_handle, WM8978_JACK_OUT2, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* out2 logic1 disable */
    res = wm8978_set_jack_logic_1(&gs_handle, WM8978_JACK_OUT2, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* out3 logic0 disable */
    res = wm8978_set_jack_logic_0(&gs_handle, WM8978_JACK_OUT3, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* out4 logic0 disable */
    res = wm8978_set_jack_logic_0(&gs_handle, WM8978_JACK_OUT4, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* out3 logic1 disable */
    res = wm8978_set_jack_logic_1(&gs_handle, WM8978_JACK_OUT3, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* out4 logic1 disable */
    res = wm8978_set_jack_logic_1(&gs_handle, WM8978_JACK_OUT4, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable high pass filter */
    res = wm8978_set_high_pass_filter(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* set audio mode */
    res = wm8978_set_mode(&gs_handle, WM8978_MODE_AUDIO);
    if (res != 0)
    {
        return 1;
    }
    
    /* set high pass filter cut off 0 */
    res = wm8978_set_high_pass_filter_cut_off(&gs_handle, WM8978_HIGH_PASS_FILTER_CUT_OFF_0);
    if (res != 0)
    {
        return 1;
    }
    
    /* set adc oversample rate 128x */
    res = wm8978_set_adc_oversample_rate(&gs_handle, WM8978_ADC_OVERSAMPLE_RATE_128X);
    if (res != 0)
    {
        return 1;
    }
    
    /* set adc right channel polarity */
    res = wm8978_set_adc_right_channel_polarity(&gs_handle, WM8978_POLARITY_NORMAL);
    if (res != 0)
    {
        return 1;
    }
    
    /* set adc left channel polarity */
    res = wm8978_set_adc_left_channel_polarity(&gs_handle, WM8978_POLARITY_NORMAL);
    if (res != 0)
    {
        return 1;
    }
    
    /* -10db */
    res = wm8978_volume_convert_to_register(&gs_handle, -10.0f, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set adc left volume */
    res = wm8978_set_adc_left_volume(&gs_handle, WM8978_BOOL_TRUE, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set adc right volume */
    res = wm8978_set_adc_right_volume(&gs_handle, WM8978_BOOL_TRUE, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* apply to dac */
    res = wm8978_set_equaliser_apply(&gs_handle, WM8978_EQUALISER_APPLIED_TO_DAC);
    if (res != 0)
    {
        return 1;
    }
    
    /* eq1 cut off 80hz */
    res = wm8978_set_eq1_cut_off(&gs_handle, WM8978_EQ1_BAND_CUT_OFF_80HZ);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0db */
    res = wm8978_eq_gain_convert_to_register(&gs_handle, 0, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set eq1 gain */
    res = wm8978_set_eq1_gain(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set eq2 bandwidth wide */
    res = wm8978_set_eq2_bandwidth(&gs_handle, WM8978_EQ_BANDWIDTH_WIDE);
    if (res != 0)
    {
        return 1;
    }
    
    /* set eq2 centre freq 385hz */
    res = wm8978_set_eq2_centre_freq(&gs_handle, WM8978_EQ2_BAND_CENTRE_FREQ_385HZ);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0db */
    res = wm8978_eq_gain_convert_to_register(&gs_handle, 0, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set eq2 gain */
    res = wm8978_set_eq2_gain(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set eq3 bandwidth wide */
    res = wm8978_set_eq3_bandwidth(&gs_handle, WM8978_EQ_BANDWIDTH_WIDE);
    if (res != 0)
    {
        return 1;
    }
    
    /* set eq3 centre freq 1100hz */
    res = wm8978_set_eq3_centre_freq(&gs_handle, WM8978_EQ3_BAND_CENTRE_FREQ_1100HZ);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0db */
    res = wm8978_eq_gain_convert_to_register(&gs_handle, 0, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set eq3 gain */
    res = wm8978_set_eq3_gain(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set eq4 bandwidth wide */
    res = wm8978_set_eq4_bandwidth(&gs_handle, WM8978_EQ_BANDWIDTH_WIDE);
    if (res != 0)
    {
        return 1;
    }
    
    /* set eq4 centre freq 3200hz */
    res = wm8978_set_eq4_centre_freq(&gs_handle, WM8978_EQ4_BAND_CENTRE_FREQ_3200HZ);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0db */
    res = wm8978_eq_gain_convert_to_register(&gs_handle, 0, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set eq4 gain */
    res = wm8978_set_eq4_gain(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set eq5 cut off 11700hz */
    res = wm8978_set_eq5_cut_off(&gs_handle, WM8978_EQ5_BAND_CUT_OFF_11700HZ);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0db */
    res = wm8978_eq_gain_convert_to_register(&gs_handle, 0, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set eq5 gain */
    res = wm8978_set_eq5_gain(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable dac digital limiter */
    res = wm8978_set_dac_digital_limiter(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* set dac limiter decay 192ms */
    res = wm8978_set_dac_limiter_decay(&gs_handle, WM8978_DAC_LIMITER_DECAY_192MS);
    if (res != 0)
    {
        return 1;
    }
    
    /* set dac limiter attack 12ms */
    res = wm8978_set_dac_limiter_attack(&gs_handle, WM8978_DAC_LIMITER_ATTACK_12MS);
    if (res != 0)
    {
        return 1;
    }
    
    /* set dac limiter level -1db */
    res = wm8978_set_dac_limiter_level(&gs_handle, WM8978_DAC_LIMITER_LEVEL_NEGATIVE_1DB);
    if (res != 0)
    {
        return 1;
    }
    
    /* 12db */
    res = wm8978_set_dac_limiter_volume_boost(&gs_handle, 12);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable notch filter */
    res = wm8978_set_notch_filter(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0x00 */
    res = wm8978_set_notch_filter_a0_coefficient_bit_13_7(&gs_handle, WM8978_BOOL_TRUE, 0x00);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0x00 */
    res = wm8978_set_notch_filter_a0_coefficient_bit_6_0(&gs_handle, WM8978_BOOL_TRUE, 0x00);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0x00 */
    res = wm8978_set_notch_filter_a1_coefficient_bit_13_7(&gs_handle, WM8978_BOOL_TRUE, 0x00);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0x00 */
    res = wm8978_set_notch_filter_a1_coefficient_bit_6_0(&gs_handle, WM8978_BOOL_TRUE, 0x00);
    if (res != 0)
    {
        return 1;
    }
    
    /* both alc */
    res = wm8978_set_alc(&gs_handle, WM8978_ALC_BOTH);
    if (res != 0)
    {
        return 1;
    }
    
    /* alc max gain 35.25db */
    res = wm8978_set_alc_max_gain(&gs_handle, WM8978_MAX_GAIN_35P25_DB);
    if (res != 0)
    {
        return 1;
    }
    
    /* alc min gain -12.0db */
    res = wm8978_set_alc_min_gain(&gs_handle, WM8978_MIN_GAIN_NEGATIVE_12_DB);
    if (res != 0)
    {
        return 1;
    }
    
    /* 12ms */
    res = wm8978_alc_hold_time_convert_to_register(&gs_handle, 12.0f, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set alc hold time */
    res = wm8978_set_alc_hold_time(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set alc level -3 */
    res = wm8978_set_alc_level(&gs_handle, WM8978_ALC_LEVEL_NEGATIVE_3);
    if (res != 0)
    {
        return 1;
    }
    
    /* alc mode */
    res = wm8978_set_alc_mode(&gs_handle, WM8978_ALC_MODE_ALC);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0x00 */
    res = wm8978_set_alc_decay(&gs_handle, 0x00);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0x00 */
    res = wm8978_set_alc_attack(&gs_handle, 0x00);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable alc noise gate */
    res = wm8978_set_alc_noise_gate(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* -39db */
    res = wm8978_alc_noise_gate_threshold_convert_to_register(&gs_handle, -39, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set alc noise gate threshold */
    res = wm8978_set_alc_noise_gate_threshold(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable mclk divide by 2 */
    res = wm8978_set_mclk_divide_by_2(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0x00 */
    res = wm8978_set_plln(&gs_handle, 0x00);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0x00000000 */
    res = wm8978_set_pll_freq(&gs_handle, 0x00000000);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0.00% */
    res = wm8978_depth_3d_convert_to_register(&gs_handle, 0.00f, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set depth 3d */
    res = wm8978_set_depth_3d(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable mute input to inv rout2 mixer */
    res = wm8978_set_mute_input_to_inv_rout2_mixer(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable inv rout2 mixer */
    res = wm8978_set_inv_rout2_mixer(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* -15db */
    res = wm8978_beep_volume_convert_to_register(&gs_handle, -15, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set beep volume */
    res = wm8978_set_beep_volume(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable sleep */
    res = wm8978_set_beep(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* set microphone bias voltage 0.9 avdd */
    res = wm8978_set_microphone_bias_voltage(&gs_handle, WM8978_AVDD_0P9);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable right channel input pga positive */
    res = wm8978_set_right_channel_input_pga_positive(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable right channel input pga negative */
    res = wm8978_set_right_channel_input_pga_negative(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable right channel input pga amplifier positive */
    res = wm8978_set_right_channel_input_pga_amplifier_positive(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable left channel input pga positive */
    res = wm8978_set_left_channel_input_pga_positive(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable left channel input pga negative */
    res = wm8978_set_left_channel_input_pga_negative(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable left channel input pga amplifier positive */
    res = wm8978_set_left_channel_input_pga_amplifier_positive(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable left input pga update */
    res = wm8978_set_left_input_pga_update(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable left channel input pga zero cross */
    res = wm8978_set_left_channel_input_pga_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable left channel input pga mute */
    res = wm8978_set_left_channel_input_pga_mute(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* 22.5db */
    res = wm8978_left_channel_input_pga_volume_convert_to_register(&gs_handle, 22.5f, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set left channel input pga volume */
    res = wm8978_set_left_channel_input_pga_volume(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable right input pga update */
    res = wm8978_set_right_input_pga_update(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable right channel input pga zero cross */
    res = wm8978_set_right_channel_input_pga_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable right channel input pga mute */
    res = wm8978_set_right_channel_input_pga_mute(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* 22.5db */
    res = wm8978_right_channel_input_pga_volume_convert_to_register(&gs_handle, 22.5f, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set right channel input pga volume */
    res = wm8978_set_right_channel_input_pga_volume(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable left channel input pga boost */
    res = wm8978_set_left_channel_input_pga_boost(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0db */
    res = wm8978_left_channel_input_boost_stage_convert_to_register(&gs_handle, 0, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set left channel input boost stage */
    res = wm8978_set_left_channel_input_boost_stage(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* -15db */
    res = wm8978_auxiliary_amplifier_left_channel_input_boost_stage_convert_to_register(&gs_handle, -15, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set auxiliary amplifier left channel input boost stage */
    res = wm8978_set_auxiliary_amplifier_left_channel_input_boost_stage(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable right channel input pga boost */
    res = wm8978_set_right_channel_input_pga_boost(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0db */
    res = wm8978_right_channel_input_boost_stage_convert_to_register(&gs_handle, 0, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set right channel input boost stage */
    res = wm8978_set_right_channel_input_boost_stage(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* -15db */
    res = wm8978_auxiliary_amplifier_right_channel_input_boost_stage_convert_to_register(&gs_handle, -15, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set auxiliary amplifier right channel input boost stage */
    res = wm8978_set_auxiliary_amplifier_right_channel_input_boost_stage(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable left dac output to right output mixer */
    res = wm8978_set_left_dac_output_to_right_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable right dac output to left output mixer */
    res = wm8978_set_right_dac_output_to_left_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable out4 boost */
    res = wm8978_set_out4_boost(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable out3 boost */
    res = wm8978_set_out3_boost(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable speaker boost */
    res = wm8978_set_speaker_boost(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable thermal shutdown */
    res = wm8978_set_thermal_shutdown(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* set vref to analogue output resistance 1K */
    res = wm8978_set_vref_to_analogue_output_resistance(&gs_handle, WM8978_VREF_1K);
    if (res != 0)
    {
        return 1;
    }
    
    /* -15db */
    res = wm8978_aux_left_channel_input_to_left_mixer_volume_convert_to_register(&gs_handle, -15, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set aux left channel input to left mixer volume */
    res = wm8978_set_aux_left_channel_input_to_left_mixer_volume(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable left auxiliary input to left channel output mixer */
    res = wm8978_set_left_auxiliary_input_to_left_channel_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0db */
    res = wm8978_left_bypass_volume_control_to_output_channel_mixer_convert_to_register(&gs_handle, 0, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set left bypass volume control to output channel mixer */
    res = wm8978_set_left_bypass_volume_control_to_output_channel_mixer(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable left bypass path to left output mixer */
    res = wm8978_set_left_bypass_path_to_left_output_mixer(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable left dac output to left output mixer */
    res = wm8978_set_left_dac_output_to_left_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* -15db */
    res = wm8978_aux_right_channel_input_to_right_mixer_volume_convert_to_register(&gs_handle, -15, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set aux right channel input to right mixer volume */
    res = wm8978_set_aux_right_channel_input_to_right_mixer_volume(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable right auxiliary input to right channel output mixer */
    res = wm8978_set_right_auxiliary_input_to_right_channel_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0db */
    res = wm8978_right_bypass_volume_control_to_output_channel_mixer_convert_to_register(&gs_handle, 0, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set right bypass volume control to output channel mixer */
    res = wm8978_set_right_bypass_volume_control_to_output_channel_mixer(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable right bypass path to right output mixer */
    res = wm8978_set_right_bypass_path_to_right_output_mixer(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable right dac output to right output mixer */
    res = wm8978_set_right_dac_output_to_right_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable lout1 update */
    res = wm8978_set_lout1_update(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable lout1 headphone volume zero cross */
    res = wm8978_set_lout1_headphone_volume_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable lout1 left headphone output mute */
    res = wm8978_set_lout1_left_headphone_output_mute(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0db */
    res = wm8978_lout1_left_headphone_output_volume_convert_to_register(&gs_handle, 0, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set lout1 left headphone output volume */
    res = wm8978_set_lout1_left_headphone_output_volume(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable rout1 update */
    res = wm8978_set_rout1_update(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable rout1 headphone volume zero cross */
    res = wm8978_set_rout1_headphone_volume_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable rout1 right headphone output mute */
    res = wm8978_set_rout1_right_headphone_output_mute(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* 0db */
    res = wm8978_rout1_right_headphone_output_volume_convert_to_register(&gs_handle, 0, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set rout1 right headphone output volume */
    res = wm8978_set_rout1_right_headphone_output_volume(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable lout2 update */
    res = wm8978_set_lout2_update(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable lout2 speaker volume zero cross */
    res = wm8978_set_lout2_speaker_volume_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable lout2 left speaker output mute */
    res = wm8978_set_lout2_left_speaker_output_mute(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* -57db */
    res = wm8978_lout2_left_speaker_output_volume_convert_to_register(&gs_handle, -57, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set lout2 left speaker output volume */
    res = wm8978_set_lout2_left_speaker_output_volume(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable rout2 update */
    res = wm8978_set_rout2_update(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable rout2 speaker volume zero cross */
    res = wm8978_set_rout2_speaker_volume_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable rout2 right speaker output mute */
    res = wm8978_set_rout2_right_speaker_output_mute(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* -57db */
    res = wm8978_rout2_right_speaker_output_volume_convert_to_register(&gs_handle, -57, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set rout2 right speaker output volume */
    res = wm8978_set_rout2_right_speaker_output_volume(&gs_handle, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable out3 mute */
    res = wm8978_set_out3_mute(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable out4 mixer output to out3 */
    res = wm8978_set_out4_mixer_output_to_out3(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable left adc input to out3 */
    res = wm8978_set_left_adc_input_to_out3(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable left dac mixer to out3 */
    res = wm8978_set_left_dac_mixer_to_out3(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable left dac output to out3 */
    res = wm8978_set_left_dac_output_to_out3(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* enable out4 mute */
    res = wm8978_set_out4_mute(&gs_handle, WM8978_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable out4 attenuated by 6db */
    res = wm8978_set_out4_attenuated_by_6db(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable left dac mixer to out4 */
    res = wm8978_set_left_dac_mixer_to_out4(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable left dac to out4 */
    res = wm8978_set_left_dac_to_out4(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable right adc input to out4 */
    res = wm8978_set_right_adc_input_to_out4(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable right dac mixer to out4 */
    res = wm8978_set_right_dac_mixer_to_out4(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    /* disable right dac output to out4 */
    res = wm8978_set_right_dac_output_to_out4(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  record get handle
 * @return points to a wav handle
 * @note   none
 */
wav_handle_t *wm8978_record_get_handle(void)
{
    return &gs_wav_handle;
}

/**
 * @brief     record file fill
 * @param[in] index is the buffer index
 * @return    status code
 *            - 0 success
 *            - 1 fill failed
 * @note      none
 */
uint8_t wm8978_record_file_fill(uint8_t index)
{
    if (wav_record_file_fill(&gs_wav_handle, index) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     record test
 * @param[in] *path points to a path buffer
 * @param[in] second is the record second
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t wm8978_record_test(char *path, uint32_t second)
{
    uint8_t res;
    uint32_t timeout;
    wm8978_info_t info;
    
    /* link interface function */
    WAV_LINK_INIT(&gs_wav_handle, wav_handle_t);
    WAV_LINK_AUDIO_INIT(&gs_wav_handle, wav_audio_init);
    WAV_LINK_AUDIO_DEINIT(&gs_wav_handle, wav_audio_deinit);
    WAV_LINK_AUDIO_READ(&gs_wav_handle, wav_audio_read);
    WAV_LINK_AUDIO_WRITE(&gs_wav_handle, wav_audio_write);
    WAV_LINK_IIS_INIT(&gs_wav_handle, wav_iis_init);
    WAV_LINK_IIS_DEINIT(&gs_wav_handle, wav_iis_deinit);
    WAV_LINK_IIS_STOP(&gs_wav_handle, wav_iis_stop);
    WAV_LINK_IIS_PAUSE(&gs_wav_handle, wav_iis_pause);
    WAV_LINK_IIS_RESUME(&gs_wav_handle, wav_iis_resume);
    WAV_LINK_IIS_SET_FREQ(&gs_wav_handle, wav_iis_set_freq);
    WAV_LINK_IIS_WRITE(&gs_wav_handle, wav_iis_write);
    WAV_LINK_IIS_READ(&gs_wav_handle, wav_iis_read);
    WAV_LINK_DELAY_MS(&gs_wav_handle, wav_delay_ms);
    WAV_LINK_DEBUG_PRINT(&gs_wav_handle, wav_debug_print);
    
    /* link interface function */
    DRIVER_WM8978_LINK_INIT(&gs_handle, wm8978_handle_t); 
    DRIVER_WM8978_LINK_IIC_INIT(&gs_handle, wm8978_interface_iic_init);
    DRIVER_WM8978_LINK_IIC_DEINIT(&gs_handle, wm8978_interface_iic_deinit);
    DRIVER_WM8978_LINK_IIC_WRITE(&gs_handle, wm8978_interface_iic_write);
    DRIVER_WM8978_LINK_DELAY_MS(&gs_handle, wm8978_interface_delay_ms);
    DRIVER_WM8978_LINK_DEBUG_PRINT(&gs_handle, wm8978_interface_debug_print);
    
    /* get information */
    res = wm8978_info(&info);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        wm8978_interface_debug_print("wm8978: chip is %s.\n", info.chip_name);
        wm8978_interface_debug_print("wm8978: manufacturer is %s.\n", info.manufacturer_name);
        wm8978_interface_debug_print("wm8978: interface is %s.\n", info.interface);
        wm8978_interface_debug_print("wm8978: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        wm8978_interface_debug_print("wm8978: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        wm8978_interface_debug_print("wm8978: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        wm8978_interface_debug_print("wm8978: max current is %0.2fmA.\n", info.max_current_ma);
        wm8978_interface_debug_print("wm8978: max temperature is %0.1fC.\n", info.temperature_max);
        wm8978_interface_debug_print("wm8978: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start record test */
    wm8978_interface_debug_print("wm8978: start record test.\n");
    
    /* wm8978 init */
    res = wm8978_init(&gs_handle);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: init failed.\n");
        
        return 1;
    }
    
    /* config */
    res = a_wm8978_config();
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: config failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wav init */
    res = wav_init(&gs_wav_handle);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: wav init failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* 2 channels */
    res = wm8978_set_channel(&gs_handle, WM8978_CHANNEL_STEREO);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set channel failed.\n");
        (void)wav_deinit(&gs_wav_handle);
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set 16bits */
    res = wm8978_set_word_length(&gs_handle, WM8978_WORD_LENGTH_16_BITS);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set word length failed.\n");
        (void)wav_deinit(&gs_wav_handle);
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wav player config */
    res = wav_player_config(&gs_wav_handle, I2S_STANDARD_PHILIPS, 
                            I2S_MODE_MASTER_TX, I2S_CPOL_LOW, 
                            I2S_DATAFORMAT_16B, I2S_MCLKOUTPUT_ENABLE, 22050);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: wav record config failed.\n");
        (void)wav_deinit(&gs_wav_handle);
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* record start */
    res = wav_record_start(&gs_wav_handle, 22050, path);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: wav record start failed.\n");
        (void)wav_deinit(&gs_wav_handle);
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set timeout */
    timeout = second;
    
    /* loop */
    while (timeout != 0)
    {
        wav_delay_ms(1000);
        timeout--;
        wav_debug_print("wav: record %d bytes time %d/%ds.\n", gs_wav_handle.pos, second - timeout, second);
    }
    
    /* record stop */
    res = wav_record_stop(&gs_wav_handle);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: wav record stop failed.\n");
        (void)wav_deinit(&gs_wav_handle);
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish record */
    wm8978_interface_debug_print("wm8978: finish record test.\n");
    (void)wav_deinit(&gs_wav_handle);
    (void)wm8978_deinit(&gs_handle);
    
    return 0;
}
