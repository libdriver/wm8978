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
 * @file      driver_wm8978_basic.c
 * @brief     driver wm8978 basic source file
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

#include "driver_wm8978_basic.h"

static wm8978_handle_t gs_handle;        /**< wm8978 handle */

/**
 * @brief     basic example init
 * @param[in] mode is the basic mode
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t wm8978_basic_init(wm8978_basic_mode_t mode)
{
    uint8_t res;
    uint8_t reg;
    
    /* link interface function */
    DRIVER_WM8978_LINK_INIT(&gs_handle, wm8978_handle_t); 
    DRIVER_WM8978_LINK_IIC_INIT(&gs_handle, wm8978_interface_iic_init);
    DRIVER_WM8978_LINK_IIC_DEINIT(&gs_handle, wm8978_interface_iic_deinit);
    DRIVER_WM8978_LINK_IIC_WRITE(&gs_handle, wm8978_interface_iic_write);
    DRIVER_WM8978_LINK_DELAY_MS(&gs_handle, wm8978_interface_delay_ms);
    DRIVER_WM8978_LINK_DEBUG_PRINT(&gs_handle, wm8978_interface_debug_print);
    
    /* wm8978 init */
    res = wm8978_init(&gs_handle);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: init failed.\n");
        
        return 1;
    }
    
    /* set default dc buffer */
    res = wm8978_set_dc_buffer(&gs_handle, WM8978_BASIC_DEFAULT_DC_BUFFER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set dc buffer failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default out4 mixer */
    res = wm8978_set_out4_mixer(&gs_handle, WM8978_BASIC_DEFAULT_OUT4_MIXER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set out4 mixer failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default out3 mixer */
    res = wm8978_set_out3_mixer(&gs_handle, WM8978_BASIC_DEFAULT_OUT3_MIXER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set out3 mixer failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pll */
    res = wm8978_set_pll(&gs_handle, WM8978_BASIC_DEFAULT_PLL);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set pll failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default microphone bias */
    res = wm8978_set_microphone_bias(&gs_handle, WM8978_BASIC_DEFAULT_MICROPHONE_BIAS);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set microphone bias failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default analogue amplifier bias */
    res = wm8978_set_analogue_amplifier_bias(&gs_handle, WM8978_BASIC_DEFAULT_ANALOGUE_AMPLIFIER_BIAS);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set analogue amplifier bias failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default unused input output tie off buffer */
    res = wm8978_set_unused_input_output_tie_off_buffer(&gs_handle, WM8978_BASIC_DEFAULT_UNUSED_INPUT_OUTPUT_TIE_OFF_BUFFER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set unused input output tie off buffer failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default reference impedance */
    res = wm8978_set_reference_impedance(&gs_handle, WM8978_BASIC_DEFAULT_REFERENCE_IMPEDANCE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set reference impedance failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable sleep */
    res = wm8978_set_sleep(&gs_handle, WM8978_BOOL_FALSE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set sleep failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }

    /* set default out4 */
    res = wm8978_set_out4(&gs_handle, WM8978_BASIC_DEFAULT_OUT4);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set out4 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default out3 */
    res = wm8978_set_out3(&gs_handle, WM8978_BASIC_DEFAULT_OUT3);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set out3 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default bclk polarity */
    res = wm8978_set_bclk_polarity(&gs_handle, WM8978_BASIC_DEFAULT_BCLK_POLARITY);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set bclk polarity failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default lrclk polarity */
    res = wm8978_set_lrclk_polarity(&gs_handle, WM8978_BASIC_DEFAULT_LRCLK_POLARITY);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set lrclk polarity failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dac appear */
    res = wm8978_set_dac_appear(&gs_handle, WM8978_BASIC_DEFAULT_DAC_APPEAR);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set dac appear failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default adc appear */
    res = wm8978_set_adc_appear(&gs_handle,WM8978_BASIC_DEFAULT_ADC_APPEAR);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set adc appear failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default companding 8bit mode */
    res = wm8978_set_companding_8bit_mode(&gs_handle, WM8978_BASIC_DEFAULT_COMPANDING_8BIT_MODE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set companding 8bit mode failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default data format */
    res = wm8978_set_data_format(&gs_handle, WM8978_BASIC_DEFAULT_DATA_FORMAT);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set data format failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default loopback */
    res = wm8978_set_loopback(&gs_handle, WM8978_BASIC_DEFAULT_LOOP_BACK);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set loopback failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default clksel */
    res = wm8978_set_clksel(&gs_handle, WM8978_BASIC_DEFAULT_CLKSEL);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set clksel failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default mclk div */
    res = wm8978_set_mclk_div(&gs_handle, WM8978_BASIC_DEFAULT_MCLK_DIV);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set mclk div failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default bclk div */
    res = wm8978_set_bclk_div(&gs_handle, WM8978_BASIC_DEFAULT_BCLK_DIV);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set bclk div failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default clock mode */
    res = wm8978_set_clock_mode(&gs_handle, WM8978_BASIC_DEFAULT_CLOCK_MODE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set clock mode failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default approximate sample rate */
    res = wm8978_set_approximate_sample_rate(&gs_handle, WM8978_BASIC_DEFAULT_APPROXIMATE_SAMPLE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set approximate sample rate failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default slow clock */
    res = wm8978_set_slow_clock(&gs_handle, WM8978_BASIC_DEFAULT_SLOW_CLOCK);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set slow clock failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pll div */
    res = wm8978_set_pll_div(&gs_handle, WM8978_BASIC_DEFAULT_PLL_DIV);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set pll div failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default gpio1 polarity */
    res = wm8978_set_gpio1_polarity(&gs_handle, WM8978_BASIC_DEFAULT_GPIO1_POLARITY);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set gpio1 polarity failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default gpio1 select */
    res = wm8978_set_gpio1_select(&gs_handle, WM8978_BASIC_DEFAULT_GPIO1_SELECT);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set gpio1 select failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default vmid 1 */
    res = wm8978_set_vmid_1(&gs_handle, WM8978_BASIC_DEFAULT_VMID_1);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set vmid 1 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default vmid 0 */
    res = wm8978_set_vmid_0(&gs_handle, WM8978_BASIC_DEFAULT_VMID_0);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set vmid 0 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default jack detection */
    res = wm8978_set_jack_detection(&gs_handle, WM8978_BASIC_DEFAULT_JACK_DETECTION);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set jack detection failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default jack gpio */
    res = wm8978_set_jack_gpio(&gs_handle, WM8978_BASIC_DEFAULT_JACK_GPIO);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set jack gpio failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default soft mute */
    res = wm8978_set_soft_mute(&gs_handle, WM8978_BASIC_DEFAULT_SOFT_MUTE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set soft mute failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dac oversample rate */
    res = wm8978_set_dac_oversample_rate(&gs_handle, WM8978_BASIC_DEFAULT_DAC_OVERSAMPLE_RATE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set dac oversample rate failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default amute */
    res = wm8978_set_amute(&gs_handle, WM8978_BASIC_DEFAULT_AMUTE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set amute failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default right dac output polarity */
    res = wm8978_set_right_dac_output_polarity(&gs_handle, WM8978_BASIC_DEFAULT_RIGHT_DAC_OUTPUT_POLARITY);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set right dac output polarity failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default left dac output polarity */
    res = wm8978_set_left_dac_output_polarity(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_DAC_OUTPUT_POLARITY);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set left dac output polarity failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default volume */
    res = wm8978_volume_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_DAC_VOLUME, &reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: volume convert to register failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set dac left volume */
    res = wm8978_set_dac_left_volume(&gs_handle, WM8978_BOOL_TRUE, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set dac left volume failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set dac right volume */
    res = wm8978_set_dac_right_volume(&gs_handle, WM8978_BOOL_TRUE, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set dac right volume failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default jack logic 0 */
    res = wm8978_set_jack_logic_0(&gs_handle, WM8978_JACK_OUT1, WM8978_BASIC_DEFAULT_JACK_LOGIC_0_OUT1);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set jack logic 0 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default jack logic 1 */
    res = wm8978_set_jack_logic_1(&gs_handle, WM8978_JACK_OUT1, WM8978_BASIC_DEFAULT_JACK_LOGIC_1_OUT1);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set jack logic 1 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default jack logic 0 */
    res = wm8978_set_jack_logic_0(&gs_handle, WM8978_JACK_OUT2, WM8978_BASIC_DEFAULT_JACK_LOGIC_0_OUT2);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set jack logic 0 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default jack logic 1 */
    res = wm8978_set_jack_logic_1(&gs_handle, WM8978_JACK_OUT2, WM8978_BASIC_DEFAULT_JACK_LOGIC_1_OUT2);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set jack logic 1 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default jack logic 0 */
    res = wm8978_set_jack_logic_0(&gs_handle, WM8978_JACK_OUT3, WM8978_BASIC_DEFAULT_JACK_LOGIC_0_OUT3);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set jack logic 0 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default jack logic 0 */
    res = wm8978_set_jack_logic_0(&gs_handle, WM8978_JACK_OUT4, WM8978_BASIC_DEFAULT_JACK_LOGIC_0_OUT4);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set jack logic 0 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default jack logic 1 */
    res = wm8978_set_jack_logic_1(&gs_handle, WM8978_JACK_OUT3, WM8978_BASIC_DEFAULT_JACK_LOGIC_1_OUT3);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set jack logic 1 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default jack logic 1 */
    res = wm8978_set_jack_logic_1(&gs_handle, WM8978_JACK_OUT4, WM8978_BASIC_DEFAULT_JACK_LOGIC_1_OUT4);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set jack logic 1 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default high pass filter */
    res = wm8978_set_high_pass_filter(&gs_handle, WM8978_BASIC_DEFAULT_HIGH_PASS_FILTER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set high pass filter failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default mode */
    res = wm8978_set_mode(&gs_handle, WM8978_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set mode failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default high pass filter cut off */
    res = wm8978_set_high_pass_filter_cut_off(&gs_handle, WM8978_BASIC_DEFAULT_HIGH_PASS_FILTER_CUT_OFF);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set high pass filter cut off failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default adc oversample rate */
    res = wm8978_set_adc_oversample_rate(&gs_handle, WM8978_BASIC_DEFAULT_ADC_OVERSAMPLE_RATE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set adc oversample rate failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default adc right channel polarity */
    res = wm8978_set_adc_right_channel_polarity(&gs_handle, WM8978_BASIC_DEFAULT_ADC_RIGHT_CHANNEL_POLARITY);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set adc right channel polarity failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default adc left channel polarity */
    res = wm8978_set_adc_left_channel_polarity(&gs_handle, WM8978_BASIC_DEFAULT_ADC_LEFT_CHANNEL_POLARITY);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set adc left channel polarity failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default adc volume */
    res = wm8978_volume_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_ADC_VOLUME, &reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: volume convert to register failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set adc left volume */
    res = wm8978_set_adc_left_volume(&gs_handle, WM8978_BOOL_TRUE, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set adc left volume failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set adc right volume */
    res = wm8978_set_adc_right_volume(&gs_handle, WM8978_BOOL_TRUE, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set adc right volume failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default equaliser apply */
    res = wm8978_set_equaliser_apply(&gs_handle, WM8978_BASIC_DEFAULT_EQUALISER_APPLY);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set equaliser apply failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq1 cut off */
    res = wm8978_set_eq1_cut_off(&gs_handle, WM8978_BASIC_DEFAULT_EQ1_BAND_CUT_OFF);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq1 cut off failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq1 gain */
    res = wm8978_eq_gain_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_EQ1_GAIN, &reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: eq gain convert to register failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set eq1 gain */
    res = wm8978_set_eq1_gain(&gs_handle, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq1 gain failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq2 bandwidth */
    res = wm8978_set_eq2_bandwidth(&gs_handle, WM8978_BASIC_DEFAULT_EQ2_BANDWIDTH);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq2 bandwidth failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq2 centre freq */
    res = wm8978_set_eq2_centre_freq(&gs_handle, WM8978_BASIC_DEFAULT_EQ2_BAND_CENTRE_FREQ);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq2 centre freq failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq2 gain */
    res = wm8978_eq_gain_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_EQ2_GAIN, &reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: eq gain convert to register failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set eq2 gain */
    res = wm8978_set_eq2_gain(&gs_handle, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq2 gain failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq3 bandwidth */
    res = wm8978_set_eq3_bandwidth(&gs_handle, WM8978_BASIC_DEFAULT_EQ3_BANDWIDTH);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq3 bandwidth failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq3 centre freq */
    res = wm8978_set_eq3_centre_freq(&gs_handle, WM8978_BASIC_DEFAULT_EQ3_BAND_CENTRE_FREQ);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq3 centre freq failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq3 gain */
    res = wm8978_eq_gain_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_EQ3_GAIN, &reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: eq gain convert to register failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set eq3 gain */
    res = wm8978_set_eq3_gain(&gs_handle, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq3 gain failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq4 bandwidth */
    res = wm8978_set_eq4_bandwidth(&gs_handle, WM8978_BASIC_DEFAULT_EQ4_BANDWIDTH);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq4 bandwidth failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq4 centre freq */
    res = wm8978_set_eq4_centre_freq(&gs_handle, WM8978_BASIC_DEFAULT_EQ4_BAND_CENTRE_FREQ);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq4 centre freq failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq4 gain */
    res = wm8978_eq_gain_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_EQ4_GAIN, &reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: eq gain convert to register failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set eq4 gain */
    res = wm8978_set_eq4_gain(&gs_handle, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq4 gain failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq5 cut off */
    res = wm8978_set_eq5_cut_off(&gs_handle, WM8978_BASIC_DEFAULT_EQ5_BAND_CUT_OFF);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq5 cut off failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default eq5 gain */
    res = wm8978_eq_gain_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_EQ5_GAIN, &reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: eq gain convert to register failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set eq5 gain */
    res = wm8978_set_eq5_gain(&gs_handle, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set eq5 gain failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dac digital limiter */
    res = wm8978_set_dac_digital_limiter(&gs_handle, WM8978_BASIC_DEFAULT_DAC_DIGITAL_LIMITER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set dac digital limiter failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dac limiter decay */
    res = wm8978_set_dac_limiter_decay(&gs_handle, WM8978_BASIC_DEFAULT_DAC_LIMITER_DECAY);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set dac limiter decay failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dac limiter attack */
    res = wm8978_set_dac_limiter_attack(&gs_handle, WM8978_BASIC_DEFAULT_DAC_LIMITER_ATTACK);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set dac limiter attack failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dac limiter level */
    res = wm8978_set_dac_limiter_level(&gs_handle, WM8978_BASIC_DEFAULT_DAC_LIMITER_LEVEL);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set dac limiter level failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dac limiter volume boost */
    res = wm8978_set_dac_limiter_volume_boost(&gs_handle, WM8978_BASIC_DEFAULT_DAC_LIMITER_VOLUME_BOOST);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set dac limiter volume boost failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default notch filter */
    res = wm8978_set_notch_filter(&gs_handle, WM8978_BASIC_DEFAULT_NOTCH_FILTER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set notch filter failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default notch filter a0 */
    res = wm8978_set_notch_filter_a0_coefficient_bit_13_7(&gs_handle, WM8978_BOOL_TRUE, WM8978_BASIC_DEFAULT_NOTCH_FILTER_A0_BIT_13_7);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set notch filter a0 coefficient bit 13 7 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default notch filter a0 */
    res = wm8978_set_notch_filter_a0_coefficient_bit_6_0(&gs_handle, WM8978_BOOL_TRUE, WM8978_BASIC_DEFAULT_NOTCH_FILTER_A0_BIT_16_0);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set notch filter a0 coefficient bit 6 0 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default notch filter a1 */
    res = wm8978_set_notch_filter_a1_coefficient_bit_13_7(&gs_handle, WM8978_BOOL_TRUE, WM8978_BASIC_DEFAULT_NOTCH_FILTER_A1_BIT_13_7);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set notch filter a1 coefficient bit 13 7 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default notch filter a1 */
    res = wm8978_set_notch_filter_a1_coefficient_bit_6_0(&gs_handle, WM8978_BOOL_TRUE, WM8978_BASIC_DEFAULT_NOTCH_FILTER_A1_BIT_16_0);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set notch filter a1 coefficient bit 6 0 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default alc */
    res = wm8978_set_alc(&gs_handle, WM8978_BASIC_DEFAULT_ALC);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set alc failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default alc max gain */
    res = wm8978_set_alc_max_gain(&gs_handle, WM8978_BASIC_DEFAULT_ALC_MAX_GAIN);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set alc max gain failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default alc min gain */
    res = wm8978_set_alc_min_gain(&gs_handle, WM8978_BASIC_DEFAULT_ALC_MIN_GAIN);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set alc min gain failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default alc hold time */
    res = wm8978_alc_hold_time_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_ALC_HOLD_TIME, &reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: alc hold time convert to register failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set alc hold time */
    res = wm8978_set_alc_hold_time(&gs_handle, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set alc hold time failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default alc level */
    res = wm8978_set_alc_level(&gs_handle, WM8978_BASIC_DEFAULT_ALC_LEVEL);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set alc level failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default alc mode */
    res = wm8978_set_alc_mode(&gs_handle, WM8978_BASIC_DEFAULT_ALC_MODE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set alc mode failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default alc decay */
    res = wm8978_set_alc_decay(&gs_handle, WM8978_BASIC_DEFAULT_ALC_DECAY);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set alc decay failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default alc attack */
    res = wm8978_set_alc_attack(&gs_handle, WM8978_BASIC_DEFAULT_ALC_ATTACK);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set alc attack failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default alc noise gate */
    res = wm8978_set_alc_noise_gate(&gs_handle, WM8978_BASIC_DEFAULT_ALC_NOISE_GATE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set alc noise gate failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default alc noise gate threshold */
    res = wm8978_alc_noise_gate_threshold_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_ALC_NOISE_GATE_THRESHOLD, &reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: alc noise gate threshold convert to register failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set alc noise gate threshold */
    res = wm8978_set_alc_noise_gate_threshold(&gs_handle, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set alc noise gate threshold failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default mclk divide by 2 */
    res = wm8978_set_mclk_divide_by_2(&gs_handle, WM8978_BASIC_DEFAULT_MCLK_DIVIDE_BY_2);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set mclk divide by 2 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default plln */
    res = wm8978_set_plln(&gs_handle, WM8978_BASIC_DEFAULT_PLLN);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set plln failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pll freq */
    res = wm8978_set_pll_freq(&gs_handle, WM8978_BASIC_DEFAULT_PLL_FREQ);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set pll freq failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default depth 3d */
    res = wm8978_depth_3d_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_DEPTH_3D, &reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: depth 3d convert to register failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set depth 3d */
    res = wm8978_set_depth_3d(&gs_handle, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set depth 3d failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default right out1 */
    res = wm8978_set_right_out1(&gs_handle, WM8978_BASIC_DEFAULT_RIGHT_OUT1);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set right out1 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default left out1 */
    res = wm8978_set_left_out1(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_OUT1);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set left out1 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default right channel input boost */
    res = wm8978_set_right_channel_input_boost(&gs_handle, WM8978_BASIC_DEFAULT_RIGHT_CHANNEL_INPUT_BOOST);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set right channel input boost failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default left channel input boost */
    res = wm8978_set_left_channel_input_boost(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_CHANNEL_INPUT_BOOST);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set left channel input boost failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default left out2 */
    res = wm8978_set_left_out2(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_OUT2);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set left out2 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default right out2 */
    res = wm8978_set_right_out2(&gs_handle, WM8978_BASIC_DEFAULT_RIGHT_OUT2);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set right out2 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default right output channel mixer */
    res = wm8978_set_right_output_channel_mixer(&gs_handle, WM8978_BASIC_DEFAULT_RIGHT_OUTPUT_CHANNEL_MIXER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set right output channel mixer failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default left output channel mixer */
    res = wm8978_set_left_output_channel_mixer(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_OUTPUT_CHANNEL_MIXER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set left output channel mixer failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default mute input to inv rout2 mixer */
    res = wm8978_set_mute_input_to_inv_rout2_mixer(&gs_handle, WM8978_BASIC_DEFAULT_MUTE_INPUT_TO_INV_ROUT2_MIXER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set mute input to inv rout2 mixer failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default inv rout2 mixer */
    res = wm8978_set_inv_rout2_mixer(&gs_handle, WM8978_BASIC_DEFAULT_INV_ROUT2_MIXER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set inv rout2 mixer failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set beep volume */
    res = wm8978_beep_volume_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_BEEP_VOLUME, &reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: beep volume convert to register failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set beep volume */
    res = wm8978_set_beep_volume(&gs_handle, reg);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set beep volume failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default sleep */
    res = wm8978_set_beep(&gs_handle, WM8978_BASIC_DEFAULT_BEEP);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set beep failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default microphone bias voltage */
    res = wm8978_set_microphone_bias_voltage(&gs_handle, WM8978_BASIC_DEFAULT_MICROPHONE_BIAS_VOLTAGE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set microphone bias voltage failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default right channel input pga positive */
    res = wm8978_set_right_channel_input_pga_positive(&gs_handle, WM8978_BASIC_DEFAULT_RIGHT_CHANNEL_INPUT_PGA_POSITIVE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set right channel input pga positive failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default left channel input pga positive */
    res = wm8978_set_left_channel_input_pga_positive(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_CHANNEL_INPUT_PGA_POSITIVE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set left channel input pga positive failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default left dac output to right output mixer */
    res = wm8978_set_left_dac_output_to_right_output_mixer(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_DAC_OUTPUT_TO_RIGHT_OUTPUT_MIXER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set left dac output to right output mixer failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default right dac output to left output mixer */
    res = wm8978_set_right_dac_output_to_left_output_mixer(&gs_handle, WM8978_BASIC_DEFAULT_RIGHT_DAC_OUTPUT_TO_LEFT_OUTPUT_MIXER);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set right dac output to left output mixer failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default out4 boost */
    res = wm8978_set_out4_boost(&gs_handle, WM8978_BASIC_DEFAULT_OUT4_BOOST);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set out4 boost failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default out3 boost */
    res = wm8978_set_out3_boost(&gs_handle, WM8978_BASIC_DEFAULT_OUT3_BOOST);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set out3 boost failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default speaker boost */
    res = wm8978_set_speaker_boost(&gs_handle, WM8978_BASIC_DEFAULT_SPEAKER_BOOST);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set speaker boost failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default thermal shutdown */
    res = wm8978_set_thermal_shutdown(&gs_handle, WM8978_BASIC_DEFAULT_THERMAL_SHUTDOWN);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set thermal shutdown failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default vref to analogue output resistance */
    res = wm8978_set_vref_to_analogue_output_resistance(&gs_handle, WM8978_BASIC_DEFAULT_VREF);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set vref to analogue output resistance failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default out3 mute */
    res = wm8978_set_out3_mute(&gs_handle, WM8978_BASIC_DEFAULT_OUT3_MUTE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set out3 mute failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default out4 mixer output to out3 */
    res = wm8978_set_out4_mixer_output_to_out3(&gs_handle, WM8978_BASIC_DEFAULT_OUT4_MIXER_OUTPUT_TO_OUT3);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set out4 mixer output to out3 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default left adc input to out3 */
    res = wm8978_set_left_adc_input_to_out3(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_ADC_INPUT_TO_OUT3);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set left adc input to out3 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default left dac mixer to out3 */
    res = wm8978_set_left_dac_mixer_to_out3(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_DAC_MIXER_TO_OUT3);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set left dac mixer to out3 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default left dac output to out3 */
    res = wm8978_set_left_dac_output_to_out3(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_DAC_OUTPUT_TO_OUT3);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set left dac output to out3 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default out4 mute */
    res = wm8978_set_out4_mute(&gs_handle, WM8978_BASIC_DEFAULT_OUT4_MUTE);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set out4 mute failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default out4 attenuated by 6db */
    res = wm8978_set_out4_attenuated_by_6db(&gs_handle, WM8978_BASIC_DEFAULT_OUT4_ATTENUATED_BY_6DB);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set out4 attenuated by 6db failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default left dac mixer to out4 */
    res = wm8978_set_left_dac_mixer_to_out4(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_DAC_MIXER_TO_OUT4);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set left dac mixer to out4 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default left dac to out4 */
    res = wm8978_set_left_dac_to_out4(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_DAC_TO_OUT4);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set left dac to out4 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default right adc input to out4 */
    res = wm8978_set_right_adc_input_to_out4(&gs_handle, WM8978_BASIC_DEFAULT_RIGHT_ADC_INPUT_TO_OUT4);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set right adc input to out4 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default right dac mixer to out4 */
    res = wm8978_set_right_dac_mixer_to_out4(&gs_handle, WM8978_BASIC_DEFAULT_RIGHT_DAC_MIXER_TO_OUT4);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set right dac mixer to out4 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default right dac output to out4 */
    res = wm8978_set_right_dac_output_to_out4(&gs_handle, WM8978_BASIC_DEFAULT_RIGHT_DAC_OUTPUT_TO_OUT4);
    if (res != 0)
    {
        wm8978_interface_debug_print("wm8978: set right dac output to out4 failed.\n");
        (void)wm8978_deinit(&gs_handle);
        
        return 1;
    }
    
    if (mode == WM8978_BASIC_MODE_PLAY)
    {
        /* enable right channel dac */
        res = wm8978_set_right_channel_dac(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel dac failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable left channel dac */
        res = wm8978_set_left_channel_dac(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel dac failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable right channel adc */
        res = wm8978_set_right_channel_adc(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel adc failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left channel adc */
        res = wm8978_set_left_channel_adc(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel adc failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable right channel input pga */
        res = wm8978_set_right_channel_input_pga(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left channel input pga */
        res = wm8978_set_left_channel_input_pga(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable right channel input pga negative */
        res = wm8978_set_right_channel_input_pga_negative(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga negative failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable right channel input pga amplifier positive */
        res = wm8978_set_right_channel_input_pga_amplifier_positive(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga amplifier positive failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left channel input pga negative */
        res = wm8978_set_left_channel_input_pga_negative(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga negative failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left channel input pga amplifier positive */
        res = wm8978_set_left_channel_input_pga_amplifier_positive(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga amplifier positive failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable left channel input pga boost */
        res = wm8978_set_left_channel_input_pga_boost(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga boost failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -15db */
        res = wm8978_left_channel_input_boost_stage_convert_to_register(&gs_handle, -15, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: left channel input boost stage convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set left channel input boost stage */
        res = wm8978_set_left_channel_input_boost_stage(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input boost stage failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable right channel input pga boost */
        res = wm8978_set_right_channel_input_pga_boost(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga boost failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -15db */
        res = wm8978_right_channel_input_boost_stage_convert_to_register(&gs_handle, -15, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: right channel input boost stage convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set right channel input boost stage */
        res = wm8978_set_right_channel_input_boost_stage(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input boost stage failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -15db */
        res = wm8978_auxiliary_amplifier_left_channel_input_boost_stage_convert_to_register(&gs_handle, -15, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: auxiliary amplifier left channel input boost stage convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set auxiliary amplifier left channel input boost stage */
        res = wm8978_set_auxiliary_amplifier_left_channel_input_boost_stage(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set auxiliary amplifier left channel input boost stage failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -15db */
        res = wm8978_auxiliary_amplifier_right_channel_input_boost_stage_convert_to_register(&gs_handle, -15, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: auxiliary amplifier right channel input boost stage convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set auxiliary amplifier right channel input boost stage */
        res = wm8978_set_auxiliary_amplifier_right_channel_input_boost_stage(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set auxiliary amplifier right channel input boost stage failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -15db */
        res = wm8978_left_bypass_volume_control_to_output_channel_mixer_convert_to_register(&gs_handle, -15, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: left bypass volume control to output channel mixer convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set left bypass volume control to output channel mixer */
        res = wm8978_set_left_bypass_volume_control_to_output_channel_mixer(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left bypass volume control to output channel mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left bypass path to left output mixer */
        res = wm8978_set_left_bypass_path_to_left_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left bypass path to left output mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable left dac output to left output mixer */
        res = wm8978_set_left_dac_output_to_left_output_mixer(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left dac output to left output mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -15db */
        res = wm8978_right_bypass_volume_control_to_output_channel_mixer_convert_to_register(&gs_handle, -15, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: right bypass volume control to output channel mixer convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set right bypass volume control to output channel mixer */
        res = wm8978_set_right_bypass_volume_control_to_output_channel_mixer(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right bypass volume control to output channel mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable right bypass path to right output mixer */
        res = wm8978_set_right_bypass_path_to_right_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right bypass path to right output mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable right dac output to right output mixer */
        res = wm8978_set_right_dac_output_to_right_output_mixer(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right dac output to right output mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left auxiliary input to left channel output mixer */
        res = wm8978_set_left_auxiliary_input_to_left_channel_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left auxiliary input to left channel output mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -15db */
        res = wm8978_aux_left_channel_input_to_left_mixer_volume_convert_to_register(&gs_handle, -15, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: aux left channel input to left mixer volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set aux left channel input to left mixer volume */
        res = wm8978_set_aux_left_channel_input_to_left_mixer_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set aux left channel input to left mixer volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable right auxiliary input to right channel output mixer */
        res = wm8978_set_right_auxiliary_input_to_right_channel_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right auxiliary input to right channel output mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -15db */
        res = wm8978_aux_right_channel_input_to_right_mixer_volume_convert_to_register(&gs_handle, -15, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: aux right channel input to right mixer volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set aux right channel input to right mixer volume */
        res = wm8978_set_aux_right_channel_input_to_right_mixer_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set aux right channel input to right mixer volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable left input pga update */
        res = wm8978_set_left_input_pga_update(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left input pga update failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left channel input pga zero cross */
        res = wm8978_set_left_channel_input_pga_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga zero cross failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left channel input pga mute */
        res = wm8978_set_left_channel_input_pga_mute(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga mute failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -12db */
        res = wm8978_left_channel_input_pga_volume_convert_to_register(&gs_handle, -12.0f, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: left channel input pga volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set left channel input pga volume */
        res = wm8978_set_left_channel_input_pga_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable right input pga update */
        res = wm8978_set_right_input_pga_update(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right input pga update failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable right channel input pga zero cross */
        res = wm8978_set_right_channel_input_pga_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga zero cross failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable right channel input pga mute */
        res = wm8978_set_right_channel_input_pga_mute(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga mute failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -12db */
        res = wm8978_right_channel_input_pga_volume_convert_to_register(&gs_handle, -12.0f, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: right channel input pga volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set right channel input pga volume */
        res = wm8978_set_right_channel_input_pga_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable lout2 update */
        res = wm8978_set_lout2_update(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout2 update failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable lout2 speaker volume zero cross */
        res = wm8978_set_lout2_speaker_volume_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout2 speaker volume zero cross failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable lout2 left speaker output mute */
        res = wm8978_set_lout2_left_speaker_output_mute(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout2 left speaker output mute failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set default lout2 left speaker output volume */
        res = wm8978_lout2_left_speaker_output_volume_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_LOUT2_LEFT_SPEAKER_OUTPUT_VOLUME, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: lout2 left speaker output volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set lout2 left speaker output volume */
        res = wm8978_set_lout2_left_speaker_output_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout2 left speaker output volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable rout2 update */
        res = wm8978_set_rout2_update(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout2 update failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable rout2 speaker volume zero cross */
        res = wm8978_set_rout2_speaker_volume_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout2 speaker volume zero cross failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable rout2 right speaker output mute */
        res = wm8978_set_rout2_right_speaker_output_mute(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout2 right speaker output mute failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set default rout2 right speaker output volume */
        res = wm8978_rout2_right_speaker_output_volume_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_LOUT2_RIGHT_SPEAKER_OUTPUT_VOLUME, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: rout2 right speaker output volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set rout2 right speaker output volume */
        res = wm8978_set_rout2_right_speaker_output_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout2 right speaker output volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable lout1 update */
        res = wm8978_set_lout1_update(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout1 update failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable lout1 headphone volume zero cross */
        res = wm8978_set_lout1_headphone_volume_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout1 headphone volume zero cross failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable lout1 left headphone output mute */
        res = wm8978_set_lout1_left_headphone_output_mute(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout1 left headphone output mute failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set default lout1 left headphone output volume */
        res = wm8978_lout1_left_headphone_output_volume_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_LOUT1_LEFT_HEADPHONE_OUTPUT_VOLUME, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: lout1 left headphone output volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set lout1 left headphone output volume */
        res = wm8978_set_lout1_left_headphone_output_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout1 left headphone output volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable rout1 update */
        res = wm8978_set_rout1_update(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout1 update failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable rout1 headphone volume zero cross */
        res = wm8978_set_rout1_headphone_volume_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout1 headphone volume zero cross failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable rout1 right headphone output mute */
        res = wm8978_set_rout1_right_headphone_output_mute(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout1 right headphone output mute failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set default set rout1 right headphone output volume */
        res = wm8978_rout1_right_headphone_output_volume_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_LOUT1_RIGHT_HEADPHONE_OUTPUT_VOLUME, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: rout1 right headphone output volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set rout1 right headphone output volume */
        res = wm8978_set_rout1_right_headphone_output_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout1 right headphone output volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
    }
    else
    {
        /* disable right channel dac */
        res = wm8978_set_right_channel_dac(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel dac failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left channel dac */
        res = wm8978_set_left_channel_dac(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel dac failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable right channel adc */
        res = wm8978_set_right_channel_adc(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel adc failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable left channel adc */
        res = wm8978_set_left_channel_adc(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel adc failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable right channel input pga */
        res = wm8978_set_right_channel_input_pga(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable left channel input pga */
        res = wm8978_set_left_channel_input_pga(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable right channel input pga negative */
        res = wm8978_set_right_channel_input_pga_negative(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga negative failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable right channel input pga amplifier positive */
        res = wm8978_set_right_channel_input_pga_amplifier_positive(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga amplifier positive failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable left channel input pga negative */
        res = wm8978_set_left_channel_input_pga_negative(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga negative failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable left channel input pga amplifier positive */
        res = wm8978_set_left_channel_input_pga_amplifier_positive(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga amplifier positive failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable left channel input pga boost */
        res = wm8978_set_left_channel_input_pga_boost(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga boost failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set default left channel input boost stage */
        res = wm8978_left_channel_input_boost_stage_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_CHANNEL_INPUT_BOOST_STATA, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: left channel input boost stage convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set left channel input boost stage */
        res = wm8978_set_left_channel_input_boost_stage(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input boost stage failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable right channel input pga boost */
        res = wm8978_set_right_channel_input_pga_boost(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga boost failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set default right channel input boost stage */
        res = wm8978_right_channel_input_boost_stage_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_RIGHT_CHANNEL_INPUT_BOOST_STATA, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: right channel input boost stage convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set right channel input boost stage */
        res = wm8978_set_right_channel_input_boost_stage(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input boost stage failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -15db */
        res = wm8978_auxiliary_amplifier_left_channel_input_boost_stage_convert_to_register(&gs_handle, -15, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: auxiliary amplifier left channel input boost stage convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set auxiliary amplifier left channel input boost stage */
        res = wm8978_set_auxiliary_amplifier_left_channel_input_boost_stage(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set auxiliary amplifier left channel input boost stage failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -15db */
        res = wm8978_auxiliary_amplifier_right_channel_input_boost_stage_convert_to_register(&gs_handle, -15, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: auxiliary amplifier right channel input boost stage convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set auxiliary amplifier right channel input boost stage */
        res = wm8978_set_auxiliary_amplifier_right_channel_input_boost_stage(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set auxiliary amplifier right channel input boost stage failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set default left bypass volume control to output channel mixer */
        res = wm8978_left_bypass_volume_control_to_output_channel_mixer_convert_to_register(&gs_handle, 
                                                                                            WM8978_BASIC_DEFAULT_LEFT_BYPASS_VOLUME_CONTROL_TO_OUTPUT_CHANNEL_MIXER,
                                                                                            &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: left bypass volume control to output channel mixer convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set left bypass volume control to output channel mixer */
        res = wm8978_set_left_bypass_volume_control_to_output_channel_mixer(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left bypass volume control to output channel mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable left bypass path to left output mixer */
        res = wm8978_set_left_bypass_path_to_left_output_mixer(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left bypass path to left output mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left dac output to left output mixer */
        res = wm8978_set_left_dac_output_to_left_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left dac output to left output mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set default right bypass volume control to output channel mixer */
        res = wm8978_right_bypass_volume_control_to_output_channel_mixer_convert_to_register(&gs_handle, 
                                                                                             WM8978_BASIC_DEFAULT_RIGHT_BYPASS_VOLUME_CONTROL_TO_OUTPUT_CHANNEL_MIXER,
                                                                                             &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: right bypass volume control to output channel mixer convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set right bypass volume control to output channel mixer */
        res = wm8978_set_right_bypass_volume_control_to_output_channel_mixer(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right bypass volume control to output channel mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable right bypass path to right output mixer */
        res = wm8978_set_right_bypass_path_to_right_output_mixer(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right bypass path to right output mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable right dac output to right output mixer */
        res = wm8978_set_right_dac_output_to_right_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right dac output to right output mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left auxiliary input to left channel output mixer */
        res = wm8978_set_left_auxiliary_input_to_left_channel_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left auxiliary input to left channel output mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -15db */
        res = wm8978_aux_left_channel_input_to_left_mixer_volume_convert_to_register(&gs_handle, -15, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: aux left channel input to left mixer volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set aux left channel input to left mixer volume */
        res = wm8978_set_aux_left_channel_input_to_left_mixer_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set aux left channel input to left mixer volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable right auxiliary input to right channel output mixer */
        res = wm8978_set_right_auxiliary_input_to_right_channel_output_mixer(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right auxiliary input to right channel output mixer failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -15db */
        res = wm8978_aux_right_channel_input_to_right_mixer_volume_convert_to_register(&gs_handle, -15, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: aux right channel input to right mixer volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set aux right channel input to right mixer volume */
        res = wm8978_set_aux_right_channel_input_to_right_mixer_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set aux right channel input to right mixer volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable left input pga update */
        res = wm8978_set_left_input_pga_update(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left input pga update failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left channel input pga zero cross */
        res = wm8978_set_left_channel_input_pga_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga zero cross failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable left channel input pga mute */
        res = wm8978_set_left_channel_input_pga_mute(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga mute failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set default left channel input pga volume */
        res = wm8978_left_channel_input_pga_volume_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_LEFT_CHANNEL_INPUT_PGA_VOLUME, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: left channel input pga volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set left channel input pga volume */
        res = wm8978_set_left_channel_input_pga_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set left channel input pga volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable right input pga update */
        res = wm8978_set_right_input_pga_update(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right input pga update failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable right channel input pga zero cross */
        res = wm8978_set_right_channel_input_pga_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga zero cross failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable right channel input pga mute */
        res = wm8978_set_right_channel_input_pga_mute(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga mute failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set default right channel input pga volume */
        res = wm8978_right_channel_input_pga_volume_convert_to_register(&gs_handle, WM8978_BASIC_DEFAULT_RIGHT_CHANNEL_INPUT_PGA_VOLUME, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: right channel input pga volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set right channel input pga volume */
        res = wm8978_set_right_channel_input_pga_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set right channel input pga volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable lout2 update */
        res = wm8978_set_lout2_update(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout2 update failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable lout2 speaker volume zero cross */
        res = wm8978_set_lout2_speaker_volume_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout2 speaker volume zero cross failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable lout2 left speaker output mute */
        res = wm8978_set_lout2_left_speaker_output_mute(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout2 left speaker output mute failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -57db */
        res = wm8978_lout2_left_speaker_output_volume_convert_to_register(&gs_handle, -57, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: lout2 left speaker output volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set lout2 left speaker output volume */
        res = wm8978_set_lout2_left_speaker_output_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout2 left speaker output volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable rout2 update */
        res = wm8978_set_rout2_update(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout2 update failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable rout2 speaker volume zero cross */
        res = wm8978_set_rout2_speaker_volume_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout2 speaker volume zero cross failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable rout2 right speaker output mute */
        res = wm8978_set_rout2_right_speaker_output_mute(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout2 right speaker output mute failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -57db */
        res = wm8978_rout2_right_speaker_output_volume_convert_to_register(&gs_handle, -57, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: rout2 right speaker output volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set rout2 right speaker output volume */
        res = wm8978_set_rout2_right_speaker_output_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout2 right speaker output volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable lout1 update */
        res = wm8978_set_lout1_update(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout1 update failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable lout1 headphone volume zero cross */
        res = wm8978_set_lout1_headphone_volume_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout1 headphone volume zero cross failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable lout1 left headphone output mute */
        res = wm8978_set_lout1_left_headphone_output_mute(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout1 left headphone output mute failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -57db */
        res = wm8978_lout1_left_headphone_output_volume_convert_to_register(&gs_handle, -57, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: lout1 left headphone output volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set lout1 left headphone output volume */
        res = wm8978_set_lout1_left_headphone_output_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set lout1 left headphone output volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable rout1 update */
        res = wm8978_set_rout1_update(&gs_handle, WM8978_BOOL_TRUE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout1 update failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable rout1 headphone volume zero cross */
        res = wm8978_set_rout1_headphone_volume_zero_cross(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout1 headphone volume zero cross failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* disable rout1 right headphone output mute */
        res = wm8978_set_rout1_right_headphone_output_mute(&gs_handle, WM8978_BOOL_FALSE);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout1 right headphone output mute failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* -57db */
        res = wm8978_rout1_right_headphone_output_volume_convert_to_register(&gs_handle, -57, &reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: rout1 right headphone output volume convert to register failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set rout1 right headphone output volume */
        res = wm8978_set_rout1_right_headphone_output_volume(&gs_handle, reg);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: set rout1 right headphone output volume failed.\n");
            (void)wm8978_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    return 0;
}

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
uint8_t wm8978_basic_config(wm8978_companding_t companding, wm8978_channel_t channel, wm8978_word_length_t length)
{
    uint8_t res;
    
    /* set dac companding */
    res =  wm8978_set_dac_companding(&gs_handle, companding);
    if (res != 0)
    {
        return 1;
    }
    
    /* set adc companding linear */
    res = wm8978_set_adc_companding(&gs_handle, companding);
    if (res != 0)
    {
        return 1;
    }
    
    /* set channels */
    res = wm8978_set_channel(&gs_handle, channel);
    if (res != 0)
    {
        return 1;
    }
    
    /* set word length */
    res = wm8978_set_word_length(&gs_handle, length);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t wm8978_basic_deinit(void)
{
    uint8_t res;
    
    /* deinit wm8978 */
    res = wm8978_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set dac volume
 * @param[in] db is the set db
 * @return    status code
 *            - 0 success
 *            - 1 set dac volume failed
 * @note      -127.0f <= db <= 0.0f
 */
uint8_t wm8978_basic_set_dac_volume(float db)
{
    uint8_t res;
    uint8_t reg;
    
    /* convert volume */
    res = wm8978_volume_convert_to_register(&gs_handle, db, &reg);
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
    
    return 0;
}

/**
 * @brief  basic example set dac mute
 * @return status code
 *         - 0 success
 *         - 1 set dac mute failed
 * @note   none
 */
uint8_t wm8978_basic_set_dac_mute(void)
{
    uint8_t res;
    
    /* set dac left volume */
    res = wm8978_set_dac_left_volume(&gs_handle, WM8978_BOOL_TRUE, 0x00);
    if (res != 0)
    {
        return 1;
    }
    
    /* set dac right volume */
    res = wm8978_set_dac_right_volume(&gs_handle, WM8978_BOOL_TRUE, 0x00);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set adc volume
 * @param[in] db is the set db
 * @return    status code
 *            - 0 success
 *            - 1 set adc volume failed
 * @note      -127.0f <= db <= 0.0f
 */
uint8_t wm8978_basic_set_adc_volume(float db)
{
    uint8_t res;
    uint8_t reg;
    
    /* set default adc volume */
    res = wm8978_volume_convert_to_register(&gs_handle, db, &reg);
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
    
    return 0;
}
