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
 * @file      driver_wm8978.c
 * @brief     driver wm8978 source file
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

#include "driver_wm8978.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Cirrus Logic WM8978"        /**< chip name */
#define MANUFACTURER_NAME         "Cirrus Logic"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.5f                         /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                         /**< chip max supply voltage */
#define MAX_CURRENT               18.0f                        /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                       /**< chip min operating temperature */
#define TEMPERATURE_MAX           100.0f                       /**< chip max operating temperature */
#define DRIVER_VERSION            1000                         /**< driver version */

/**
 * @brief chip address definition
 */
#define WM8978_ADDRESS       (0x1A << 1)        /**< chip iic address */

/**
 * @brief chip register definition
 */
#define WM8978_REG_SOFTWARE_RESET         0x00        /**< software reset register */
#define WM8978_REG_POWER_MANAGE_1         0x01        /**< power manage 1 register */
#define WM8978_REG_POWER_MANAGE_2         0x02        /**< power manage 2 register */
#define WM8978_REG_POWER_MANAGE_3         0x03        /**< power manage 3 register */
#define WM8978_REG_AUDIO_INTERFACE        0x04        /**< audio interface register */
#define WM8978_REG_COMPANDING_CTRL        0x05        /**< companding ctrl register */
#define WM8978_REG_CLOCK_GEN_CTRL         0x06        /**< clock gen ctrl register */
#define WM8978_REG_ADDITIONAL_CTRL        0x07        /**< additional ctrl register */
#define WM8978_REG_GPIO                   0x08        /**< gpio register */
#define WM8978_REG_JACK_DETECT_CONTROL    0x09        /**< jack detect control register */
#define WM8978_REG_DAC_CONTROL            0x0A        /**< dac control register */
#define WM8978_REG_LEFT_DAC_DIGITAL_VOL   0x0B        /**< left dac digital vol register */
#define WM8978_REG_RIGHT_DAC_DIGITAL_VOL  0x0C        /**< right dac digital vol register */
#define WM8978_REG_JACK_DETECT_CONTROL2   0x0D        /**< jack detect control2 register */
#define WM8978_REG_ADC_CONTROL            0x0E        /**< adc control register */
#define WM8978_REG_LEFT_ADC_DIGITAL_VOL   0x0F        /**< left adc digital vol register */
#define WM8978_REG_RIGHT_ADC_DIGITAL_VOL  0x10        /**< right adc digital vol register */
#define WM8978_REG_EQ1                    0x12        /**< eq1 low shelf register */
#define WM8978_REG_EQ2                    0x13        /**< eq2 peak1 register */
#define WM8978_REG_EQ3                    0x14        /**< eq3 peak2 register */
#define WM8978_REG_EQ4                    0x15        /**< eq4 peak3 register */
#define WM8978_REG_EQ5                    0x16        /**< eq5 high shelf register */
#define WM8978_REG_DAC_LIMITER_1          0x18        /**< dac limiter 1 register */
#define WM8978_REG_DAC_LIMITER_2          0x19        /**< dac limiter 2 register */
#define WM8978_REG_NOTCH_FILTER_1         0x1B        /**< notch filter 1 register */
#define WM8978_REG_NOTCH_FILTER_2         0x1C        /**< notch filter 2 register */
#define WM8978_REG_NOTCH_FILTER_3         0x1D        /**< notch filter 3 register */
#define WM8978_REG_NOTCH_FILTER_4         0x1E        /**< notch filter 4 register */
#define WM8978_REG_ALC_CONTROL_1          0x20        /**< alc control 1 register */
#define WM8978_REG_ALC_CONTROL_2          0x21        /**< alc control 2 register */
#define WM8978_REG_ALC_CONTROL_3          0x22        /**< alc control 3 register */
#define WM8978_REG_NOISE_GATE             0x23        /**< noise gate register */
#define WM8978_REG_PLL_N                  0x24        /**< pll n register */
#define WM8978_REG_PLL_K1                 0x25        /**< pll k1 register */
#define WM8978_REG_PLL_K2                 0x26        /**< pll k2 register */
#define WM8978_REG_PLL_K3                 0x27        /**< pll k3 register */
#define WM8978_REG_3D_CONTROL             0x29        /**< 3d control register */
#define WM8978_REG_BEEP_CONTROL           0x2B        /**< beep control register */
#define WM8978_REG_INPUT_CTRL             0x2C        /**< input ctrl register */
#define WM8978_REG_LEFT_INP_PGA_CTRL      0x2D        /**< left inp pga gain ctrl register */
#define WM8978_REG_RIGHT_INP_PGA_CTRL     0x2E        /**< right inp pga gain ctrl register */
#define WM8978_REG_LEFT_ADC_BOOST_CTRL    0x2F        /**< left adc boost ctrl register */
#define WM8978_REG_RIGHT_ADC_BOOST_CTRL   0x30        /**< right adc boost ctrl register */
#define WM8978_REG_OUTPUT_CTRL            0x31        /**< output ctrl register */
#define WM8978_REG_LEFT_MIXER_CTRL        0x32        /**< left mixer ctrl register */
#define WM8978_REG_RIGHT_MIXER_CTRL       0x33        /**< right mixer ctrl register */
#define WM8978_REG_LOUT1_CTRL             0x34        /**< lout1 register */
#define WM8978_REG_ROUT1_CTRL             0x35        /**< rout1 register */
#define WM8978_REG_LOUT2_CTRL             0x36        /**< lout2 register */
#define WM8978_REG_ROUT2_CTRL             0x37        /**< rout2 register */
#define WM8978_REG_OUT3_MIXER_CTRL        0x38        /**< out3 mixer register */
#define WM8978_REG_OUT4_MIXER_CTRL        0x39        /**< out4 mixer register */

/**
 * @brief wm8978 register inited value definition
 */
static const uint16_t gsc_wm8978_init_reg[58] =
{
    0X0000, 0X0000, 0X0000, 0X0000, 0X0050, 0X0000, 0X0140, 0X0000,
    0X0000, 0X0000, 0X0000, 0X00FF, 0X00FF, 0X0000, 0X0100, 0X00FF,
    0X00FF, 0X0000, 0X012C, 0X002C, 0X002C, 0X002C, 0X002C, 0X0000,
    0X0032, 0X0000, 0X0000, 0X0000, 0X0000, 0X0000, 0X0000, 0X0000,
    0X0038, 0X000B, 0X0032, 0X0000, 0X0008, 0X000C, 0X0093, 0X00E9,
    0X0000, 0X0000, 0X0000, 0X0000, 0X0003, 0X0010, 0X0010, 0X0100,
    0X0100, 0X0002, 0X0001, 0X0001, 0X0039, 0X0039, 0X0039, 0X0039,
    0X0001, 0X0001
}; 

/**
 * @brief      read config
 * @param[in]  *handle points to a wm8978 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *config points to a config buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_wm8978_iic_read(wm8978_handle_t *handle, uint8_t reg, uint16_t *config)
{
    if (reg > 57)                          /* check range 57 */
    {
        *config = 0x0000;                  /* init 0 */
        
        return 1;                          /* return error */
    }
    else
    {
        *config = handle->reg[reg];        /* get register config */
        
        return 0;                          /* success return 0 */
    }
}

/**
 * @brief     write config
 * @param[in] *handle points to a wm8978 handle structure
 * @param[in] reg is the iic register address
 * @param[in] config is the write config
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_wm8978_iic_write(wm8978_handle_t *handle, uint8_t reg, uint16_t config)
{
    uint8_t buf[1];
  
    buf[0] = config & 0xFF;                                                              /* set LSB */
    if (handle->iic_write(WM8978_ADDRESS, 
                         (reg << 1) | ((config >> 8) & 0x01), (uint8_t *)buf, 1) != 0)   /* write data */
    {
        return 1;                                                                        /* return error */
    }
    handle->reg[reg] = config;                                                           /* save the config */
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t wm8978_soft_reset(wm8978_handle_t *handle)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    conf = 0x0000;                                                           /* set any value */
    res = a_wm8978_iic_write(handle, WM8978_REG_SOFTWARE_RESET, conf);       /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_ms(100);                                                   /* delay 100ms */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_dc_buffer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_1, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 8);                                                        /* clear config */
    conf |= enable << 8;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_1, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_out4_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_1, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 7);                                                        /* clear config */
    conf |= enable << 7;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_1, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_out3_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_1, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 6);                                                        /* clear config */
    conf |= enable << 6;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_1, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_pll(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_1, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 5);                                                        /* clear config */
    conf |= enable << 5;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_1, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_microphone_bias(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_1, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 4);                                                        /* clear config */
    conf |= enable << 4;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_1, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_analogue_amplifier_bias(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_1, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 3);                                                        /* clear config */
    conf |= enable << 3;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_1, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_unused_input_output_tie_off_buffer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_1, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 2);                                                        /* clear config */
    conf |= enable << 2;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_1, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_reference_impedance(wm8978_handle_t *handle, wm8978_impedance_t impedance)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_1, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(3 << 0);                                                        /* clear config */
    conf |= impedance << 0;                                                   /* set impedance */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_1, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_right_out1(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_2, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 8);                                                        /* clear config */
    conf |= enable << 8;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_2, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_left_out1(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_2, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 7);                                                        /* clear config */
    conf |= enable << 7;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_2, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_sleep(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_2, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 6);                                                        /* clear config */
    conf |= enable << 6;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_2, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_right_channel_input_boost(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_2, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 5);                                                        /* clear config */
    conf |= enable << 5;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_2, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_left_channel_input_boost(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_2, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 4);                                                        /* clear config */
    conf |= enable << 4;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_2, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_right_channel_input_pga(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_2, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 3);                                                        /* clear config */
    conf |= enable << 3;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_2, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_left_channel_input_pga(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_2, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 2);                                                        /* clear config */
    conf |= enable << 2;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_2, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_right_channel_adc(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_2, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 1);                                                        /* clear config */
    conf |= enable << 1;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_2, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_left_channel_adc(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_2, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 0);                                                        /* clear config */
    conf |= enable << 0;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_2, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_out4(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_3, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 8);                                                        /* clear config */
    conf |= enable << 8;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_3, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_out3(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_3, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 7);                                                        /* clear config */
    conf |= enable << 7;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_3, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_left_out2(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_3, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 6);                                                        /* clear config */
    conf |= enable << 6;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_3, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_right_out2(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_3, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 5);                                                        /* clear config */
    conf |= enable << 5;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_3, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_right_output_channel_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_3, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 3);                                                        /* clear config */
    conf |= enable << 3;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_3, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_left_output_channel_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_3, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 2);                                                        /* clear config */
    conf |= enable << 2;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_3, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_right_channel_dac(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_3, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 1);                                                        /* clear config */
    conf |= enable << 1;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_3, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_left_channel_dac(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_3, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 0);                                                        /* clear config */
    conf |= enable << 0;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_3, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_bclk_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_AUDIO_INTERFACE, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 8);                                                        /* clear config */
    conf |= polarity << 8;                                                    /* set polarity */
    res = a_wm8978_iic_write(handle, WM8978_REG_AUDIO_INTERFACE, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_lrclk_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_AUDIO_INTERFACE, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 7);                                                        /* clear config */
    conf |= polarity << 7;                                                    /* set polarity */
    res = a_wm8978_iic_write(handle, WM8978_REG_AUDIO_INTERFACE, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_word_length(wm8978_handle_t *handle, wm8978_word_length_t word_length)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_AUDIO_INTERFACE, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(3 << 5);                                                        /* clear config */
    conf |= word_length << 5;                                                 /* set word length */
    res = a_wm8978_iic_write(handle, WM8978_REG_AUDIO_INTERFACE, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_data_format(wm8978_handle_t *handle, wm8978_data_format_t format)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_AUDIO_INTERFACE, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(3 << 3);                                                        /* clear config */
    conf |= format << 3;                                                      /* set format */
    res = a_wm8978_iic_write(handle, WM8978_REG_AUDIO_INTERFACE, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_dac_appear(wm8978_handle_t *handle, wm8978_appear_t appear)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_AUDIO_INTERFACE, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 2);                                                        /* clear config */
    conf |= appear << 2;                                                      /* set appear */
    res = a_wm8978_iic_write(handle, WM8978_REG_AUDIO_INTERFACE, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_adc_appear(wm8978_handle_t *handle, wm8978_appear_t appear)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_AUDIO_INTERFACE, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 1);                                                        /* clear config */
    conf |= appear << 1;                                                      /* set appear */
    res = a_wm8978_iic_write(handle, WM8978_REG_AUDIO_INTERFACE, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_channel(wm8978_handle_t *handle, wm8978_channel_t channel)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_AUDIO_INTERFACE, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 0);                                                        /* clear config */
    conf |= channel << 0;                                                     /* set channel */
    res = a_wm8978_iic_write(handle, WM8978_REG_AUDIO_INTERFACE, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_companding_8bit_mode(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_COMPANDING_CTRL, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 5);                                                        /* clear config */
    conf |= enable << 5;                                                      /* set channel */
    res = a_wm8978_iic_write(handle, WM8978_REG_COMPANDING_CTRL, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_dac_companding(wm8978_handle_t *handle, wm8978_companding_t companding)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_COMPANDING_CTRL, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(3 << 3);                                                        /* clear config */
    conf |= companding << 3;                                                  /* set companding */
    res = a_wm8978_iic_write(handle, WM8978_REG_COMPANDING_CTRL, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_adc_companding(wm8978_handle_t *handle, wm8978_companding_t companding)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_COMPANDING_CTRL, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(3 << 1);                                                        /* clear config */
    conf |= companding << 1;                                                  /* set companding */
    res = a_wm8978_iic_write(handle, WM8978_REG_COMPANDING_CTRL, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_loopback(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_COMPANDING_CTRL, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 0);                                                        /* clear config */
    conf |= enable << 0;                                                      /* set channel */
    res = a_wm8978_iic_write(handle, WM8978_REG_COMPANDING_CTRL, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_clksel(wm8978_handle_t *handle, wm8978_clksel_t clksel)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_CLOCK_GEN_CTRL, &conf);       /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 8);                                                       /* clear config */
    conf |= clksel << 8;                                                     /* set clk */
    res = a_wm8978_iic_write(handle, WM8978_REG_CLOCK_GEN_CTRL, conf);       /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_mclk_div(wm8978_handle_t *handle, wm8978_mclk_div_t d)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_CLOCK_GEN_CTRL, &conf);       /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(7 << 5);                                                       /* clear config */
    conf |= d << 5;                                                          /* set div */
    res = a_wm8978_iic_write(handle, WM8978_REG_CLOCK_GEN_CTRL, conf);       /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_bclk_div(wm8978_handle_t *handle, wm8978_bclk_div_t d)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_CLOCK_GEN_CTRL, &conf);       /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(7 << 2);                                                       /* clear config */
    conf |= d << 2;                                                          /* set div */
    res = a_wm8978_iic_write(handle, WM8978_REG_CLOCK_GEN_CTRL, conf);       /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_clock_mode(wm8978_handle_t *handle, wm8978_clock_mode_t mode)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_CLOCK_GEN_CTRL, &conf);       /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 0);                                                       /* clear config */
    conf |= mode << 0;                                                       /* set mode */
    res = a_wm8978_iic_write(handle, WM8978_REG_CLOCK_GEN_CTRL, conf);       /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_approximate_sample_rate(wm8978_handle_t *handle, wm8978_approximate_sample_t sample)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ADDITIONAL_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(7 << 1);                                                       /* clear config */
    conf |= sample << 1;                                                     /* set sample */
    res = a_wm8978_iic_write(handle, WM8978_REG_ADDITIONAL_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_slow_clock(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ADDITIONAL_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 0);                                                       /* clear config */
    conf |= enable << 0;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_ADDITIONAL_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_pll_div(wm8978_handle_t *handle, wm8978_pll_div_t d)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_GPIO, &conf);          /* read config */
    if (res != 0)                                                     /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");         /* read config failed */
        
        return 1;                                                     /* return error */
    }
    conf &= ~(3 << 4);                                                /* clear config */
    conf |= d << 4;                                                   /* set div */
    res = a_wm8978_iic_write(handle, WM8978_REG_GPIO, conf);          /* write config */
    if (res != 0)                                                     /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");        /* write config failed */
        
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t wm8978_set_gpio1_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_GPIO, &conf);          /* read config */
    if (res != 0)                                                     /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");         /* read config failed */
        
        return 1;                                                     /* return error */
    }
    conf &= ~(1 << 3);                                                /* clear config */
    conf |= polarity << 3;                                            /* set polarity */
    res = a_wm8978_iic_write(handle, WM8978_REG_GPIO, conf);          /* write config */
    if (res != 0)                                                     /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");        /* write config failed */
        
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t wm8978_set_gpio1_select(wm8978_handle_t *handle, wm8978_gpio1_sel_t sel)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_GPIO, &conf);          /* read config */
    if (res != 0)                                                     /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");         /* read config failed */
        
        return 1;                                                     /* return error */
    }
    conf &= ~(7 << 0);                                                /* clear config */
    conf |= sel << 0;                                                 /* set select */
    res = a_wm8978_iic_write(handle, WM8978_REG_GPIO, conf);          /* write config */
    if (res != 0)                                                     /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");        /* write config failed */
        
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t wm8978_set_vmid_1(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_JACK_DETECT_CONTROL, &conf);        /* read config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                      /* read config failed */
        
        return 1;                                                                  /* return error */
    }
    conf &= ~(1 << 8);                                                             /* clear config */
    conf |= enable << 8;                                                           /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_JACK_DETECT_CONTROL, conf);        /* write config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                     /* write config failed */
        
        return 1;                                                                  /* return error */
    }
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t wm8978_set_vmid_0(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_JACK_DETECT_CONTROL, &conf);        /* read config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                      /* read config failed */
        
        return 1;                                                                  /* return error */
    }
    conf &= ~(1 << 7);                                                             /* clear config */
    conf |= enable << 7;                                                           /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_JACK_DETECT_CONTROL, conf);        /* write config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                     /* write config failed */
        
        return 1;                                                                  /* return error */
    }
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t wm8978_set_jack_detection(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_JACK_DETECT_CONTROL, &conf);        /* read config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                      /* read config failed */
        
        return 1;                                                                  /* return error */
    }
    conf &= ~(1 << 6);                                                             /* clear config */
    conf |= enable << 6;                                                           /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_JACK_DETECT_CONTROL, conf);        /* write config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                     /* write config failed */
        
        return 1;                                                                  /* return error */
    }
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t wm8978_set_jack_gpio(wm8978_handle_t *handle, wm8978_jack_sel_t sel)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_JACK_DETECT_CONTROL, &conf);        /* read config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                      /* read config failed */
        
        return 1;                                                                  /* return error */
    }
    conf &= ~(3 << 4);                                                             /* clear config */
    conf |= sel << 4;                                                              /* set sel */
    res = a_wm8978_iic_write(handle, WM8978_REG_JACK_DETECT_CONTROL, conf);        /* write config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                     /* write config failed */
        
        return 1;                                                                  /* return error */
    }
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t wm8978_set_soft_mute(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_DAC_CONTROL, &conf);        /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");              /* read config failed */
        
        return 1;                                                          /* return error */
    }
    conf &= ~(1 << 6);                                                     /* clear config */
    conf |= enable << 6;                                                   /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_DAC_CONTROL, conf);        /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");             /* write config failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t wm8978_set_dac_oversample_rate(wm8978_handle_t *handle, wm8978_dac_oversample_rate_t rate)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_DAC_CONTROL, &conf);        /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");              /* read config failed */
        
        return 1;                                                          /* return error */
    }
    conf &= ~(1 << 3);                                                     /* clear config */
    conf |= rate << 3;                                                     /* set rate */
    res = a_wm8978_iic_write(handle, WM8978_REG_DAC_CONTROL, conf);        /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");             /* write config failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t wm8978_set_amute(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_DAC_CONTROL, &conf);        /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");              /* read config failed */
        
        return 1;                                                          /* return error */
    }
    conf &= ~(1 << 2);                                                     /* clear config */
    conf |= enable << 2;                                                   /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_DAC_CONTROL, conf);        /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");             /* write config failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t wm8978_set_right_dac_output_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_DAC_CONTROL, &conf);        /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");              /* read config failed */
        
        return 1;                                                          /* return error */
    }
    conf &= ~(1 << 1);                                                     /* clear config */
    conf |= polarity << 1;                                                 /* set polarity */
    res = a_wm8978_iic_write(handle, WM8978_REG_DAC_CONTROL, conf);        /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");             /* write config failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t wm8978_set_left_dac_output_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_DAC_CONTROL, &conf);        /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");              /* read config failed */
        
        return 1;                                                          /* return error */
    }
    conf &= ~(1 << 0);                                                     /* clear config */
    conf |= polarity << 0;                                                 /* set polarity */
    res = a_wm8978_iic_write(handle, WM8978_REG_DAC_CONTROL, conf);        /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");             /* write config failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t wm8978_set_dac_left_volume(wm8978_handle_t *handle, wm8978_bool_t enable, uint8_t volume)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    conf = (enable << 8) | volume;                                                  /* set volume */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_DAC_DIGITAL_VOL, conf);        /* write config */
    if (res != 0)                                                                   /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                      /* write config failed */
        
        return 1;                                                                   /* return error */
    }
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t wm8978_set_dac_right_volume(wm8978_handle_t *handle, wm8978_bool_t enable, uint8_t volume)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    conf = (enable << 8) | volume;                                                  /* set volume */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_DAC_DIGITAL_VOL, conf);       /* write config */
    if (res != 0)                                                                   /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                      /* write config failed */
        
        return 1;                                                                   /* return error */
    }
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t wm8978_set_jack_logic_1(wm8978_handle_t *handle, wm8978_jack_t jack, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_JACK_DETECT_CONTROL2, &conf);        /* read config */
    if (res != 0)                                                                   /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                       /* read config failed */
        
        return 1;                                                                   /* return error */
    }
    if (enable != 0)                                                                /* if enable */
    {
        conf |= jack << 4;                                                          /* set 1 */
    }
    else
    {
        conf &= ~(jack << 4);                                                       /* set 0 */
    }
    res = a_wm8978_iic_write(handle, WM8978_REG_JACK_DETECT_CONTROL2, conf);        /* write config */
    if (res != 0)                                                                   /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                      /* write config failed */
        
        return 1;                                                                   /* return error */
    }
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t wm8978_set_jack_logic_0(wm8978_handle_t *handle, wm8978_jack_t jack, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_JACK_DETECT_CONTROL2, &conf);        /* read config */
    if (res != 0)                                                                   /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                       /* read config failed */
        
        return 1;                                                                   /* return error */
    }
    if (enable != 0)                                                                /* if enable */
    {
        conf |= jack << 0;                                                          /* set 1 */
    }
    else
    {
        conf &= ~(jack << 0);                                                       /* set 0 */
    }
    res = a_wm8978_iic_write(handle, WM8978_REG_JACK_DETECT_CONTROL2, conf);        /* write config */
    if (res != 0)                                                                   /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                      /* write config failed */
        
        return 1;                                                                   /* return error */
    }
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t wm8978_set_high_pass_filter(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ADC_CONTROL, &conf);        /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");              /* read config failed */
        
        return 1;                                                          /* return error */
    }
    conf &= ~(1 << 8);                                                     /* clear config */
    conf |= enable << 8;                                                   /* set enable */
    res = a_wm8978_iic_write(handle, WM8978_REG_ADC_CONTROL, conf);        /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");             /* write config failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t wm8978_set_mode(wm8978_handle_t *handle, wm8978_mode_t mode)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ADC_CONTROL, &conf);        /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");              /* read config failed */
        
        return 1;                                                          /* return error */
    }
    conf &= ~(1 << 7);                                                     /* clear config */
    conf |= mode << 7;                                                     /* set mode */
    res = a_wm8978_iic_write(handle, WM8978_REG_ADC_CONTROL, conf);        /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");             /* write config failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t wm8978_set_high_pass_filter_cut_off(wm8978_handle_t *handle, wm8978_high_pass_filter_cut_off_t cut)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ADC_CONTROL, &conf);        /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");              /* read config failed */
        
        return 1;                                                          /* return error */
    }
    conf &= ~(7 << 4);                                                     /* clear config */
    conf |= cut << 4;                                                      /* set cut off */
    res = a_wm8978_iic_write(handle, WM8978_REG_ADC_CONTROL, conf);        /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");             /* write config failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t wm8978_set_adc_oversample_rate(wm8978_handle_t *handle, wm8978_adc_oversample_rate_t rate)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ADC_CONTROL, &conf);        /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");              /* read config failed */
        
        return 1;                                                          /* return error */
    }
    conf &= ~(1 << 3);                                                     /* clear config */
    conf |= rate << 3;                                                     /* set rate */
    res = a_wm8978_iic_write(handle, WM8978_REG_ADC_CONTROL, conf);        /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");             /* write config failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t wm8978_set_adc_right_channel_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ADC_CONTROL, &conf);        /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");              /* read config failed */
        
        return 1;                                                          /* return error */
    }
    conf &= ~(1 << 1);                                                     /* clear config */
    conf |= polarity << 1;                                                 /* set polarity */
    res = a_wm8978_iic_write(handle, WM8978_REG_ADC_CONTROL, conf);        /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");             /* write config failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t wm8978_set_adc_left_channel_polarity(wm8978_handle_t *handle, wm8978_polarity_t polarity)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ADC_CONTROL, &conf);        /* read config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");              /* read config failed */
        
        return 1;                                                          /* return error */
    }
    conf &= ~(1 << 0);                                                     /* clear config */
    conf |= polarity << 0;                                                 /* set polarity */
    res = a_wm8978_iic_write(handle, WM8978_REG_ADC_CONTROL, conf);        /* write config */
    if (res != 0)                                                          /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");             /* write config failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t wm8978_set_adc_left_volume(wm8978_handle_t *handle, wm8978_bool_t enable, uint8_t volume)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    conf = (enable << 8) | volume;                                                  /* set volume */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_ADC_DIGITAL_VOL, conf);        /* write config */
    if (res != 0)                                                                   /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                      /* write config failed */
        
        return 1;                                                                   /* return error */
    }
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t wm8978_set_adc_right_volume(wm8978_handle_t *handle, wm8978_bool_t enable, uint8_t volume)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    conf = (enable << 8) | volume;                                                  /* set volume */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_ADC_DIGITAL_VOL, conf);       /* write config */
    if (res != 0)                                                                   /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                      /* write config failed */
        
        return 1;                                                                   /* return error */
    }
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t wm8978_volume_convert_to_register(wm8978_handle_t *handle, float db, uint8_t *reg)
{
    if (handle == NULL)                                      /* check handle */
    {
        return 2;                                            /* return error */
    }
    if (handle->inited != 1)                                 /* check handle initialization */
    {
        return 3;                                            /* return error */
    }
    
    *reg = (uint8_t)((uint8_t)(db + 127.0f) * 2 + 1);        /* convert */
    
    return 0;                                                /* success return 0 */
}

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
uint8_t wm8978_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, float *db)
{
    if (handle == NULL)                            /* check handle */
    {
        return 2;                                  /* return error */
    }
    if (handle->inited != 1)                       /* check handle initialization */
    {
        return 3;                                  /* return error */
    }
    
    *db = -127.0f + (float)(reg - 1) * 0.5f;       /* convert */
    
    return 0;                                      /* success return 0 */
}

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
uint8_t wm8978_set_equaliser_apply(wm8978_handle_t *handle, wm8978_equaliser_t equaliser)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ1, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(1 << 8);                                             /* clear config */
    conf |= equaliser << 8;                                        /* set equaliser */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ1, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq1_cut_off(wm8978_handle_t *handle, wm8978_eq1_band_cut_off_t cut_off)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ1, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(3 << 5);                                             /* clear config */
    conf |= cut_off << 5;                                          /* set cut off */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ1, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq1_gain(wm8978_handle_t *handle, uint8_t gain)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    if (gain > 0x1F)                                               /* check gain */
    {
        handle->debug_print("wm8978: gain > 0x1F.\n");             /* gain > 0x1F */
        
        return 4;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ1, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(0x1F << 0);                                          /* clear config */
    conf |= gain << 0;                                             /* set gain */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ1, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq2_bandwidth(wm8978_handle_t *handle, wm8978_eq_bandwidth_t width)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ2, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(1 << 8);                                             /* clear config */
    conf |= width << 8;                                            /* set width */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ2, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq2_centre_freq(wm8978_handle_t *handle, wm8978_eq2_band_centre_freq_t freq)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ2, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(3 << 5);                                             /* clear config */
    conf |= freq << 5;                                             /* set freq */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ2, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq2_gain(wm8978_handle_t *handle, uint8_t gain)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    if (gain > 0x1F)                                               /* check gain */
    {
        handle->debug_print("wm8978: gain > 0x1F.\n");             /* gain > 0x1F */
        
        return 4;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ2, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(0x1F << 0);                                          /* clear config */
    conf |= gain << 0;                                             /* set gain */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ2, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq3_bandwidth(wm8978_handle_t *handle, wm8978_eq_bandwidth_t width)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ3, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(1 << 8);                                             /* clear config */
    conf |= width << 8;                                            /* set width */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ3, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq3_centre_freq(wm8978_handle_t *handle, wm8978_eq3_band_centre_freq_t freq)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ3, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(3 << 5);                                             /* clear config */
    conf |= freq << 5;                                             /* set freq */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ3, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq3_gain(wm8978_handle_t *handle, uint8_t gain)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    if (gain > 0x1F)                                               /* check gain */
    {
        handle->debug_print("wm8978: gain > 0x1F.\n");             /* gain > 0x1F */
        
        return 4;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ3, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(0x1F << 0);                                          /* clear config */
    conf |= gain << 0;                                             /* set gain */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ3, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq4_bandwidth(wm8978_handle_t *handle, wm8978_eq_bandwidth_t width)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ4, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(1 << 8);                                             /* clear config */
    conf |= width << 8;                                            /* set width */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ4, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq4_centre_freq(wm8978_handle_t *handle, wm8978_eq4_band_centre_freq_t freq)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ4, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(3 << 5);                                             /* clear config */
    conf |= freq << 5;                                             /* set freq */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ4, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq4_gain(wm8978_handle_t *handle, uint8_t gain)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    if (gain > 0x1F)                                               /* check gain */
    {
        handle->debug_print("wm8978: gain > 0x1F.\n");             /* gain > 0x1F */
        
        return 4;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ4, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(0x1F << 0);                                          /* clear config */
    conf |= gain << 0;                                             /* set gain */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ4, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq5_cut_off(wm8978_handle_t *handle, wm8978_eq5_band_cut_off_t cut_off)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ5, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(3 << 5);                                             /* clear config */
    conf |= cut_off << 5;                                          /* set cut off */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ5, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_set_eq5_gain(wm8978_handle_t *handle, uint8_t gain)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    if (gain > 0x1F)                                               /* check gain */
    {
        handle->debug_print("wm8978: gain > 0x1F.\n");             /* gain > 0x1F */
        
        return 4;                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_EQ5, &conf);        /* read config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");      /* read config failed */
        
        return 1;                                                  /* return error */
    }
    conf &= ~(0x1F << 0);                                          /* clear config */
    conf |= gain << 0;                                             /* set gain */
    res = a_wm8978_iic_write(handle, WM8978_REG_EQ5, conf);        /* write config */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");     /* write config failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wm8978_eq_gain_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                /* check handle */
    {
        return 2;                      /* return error */
    }
    if (handle->inited != 1)           /* check handle initialization */
    {
        return 3;                      /* return error */
    }
    
    *reg = (uint8_t)(-db + 12);        /* convert */
    
    return 0;                          /* success return 0 */
}

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
uint8_t wm8978_eq_gain_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    *db = (int8_t)(12 - reg);       /* convert */
    
    return 0;                       /* success return 0 */
}

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
uint8_t wm8978_set_dac_digital_limiter(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_DAC_LIMITER_1, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 8);                                                       /* clear config */
    conf |= enable << 8;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_DAC_LIMITER_1, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_dac_limiter_decay(wm8978_handle_t *handle, wm8978_dac_limiter_decay_t decay)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_DAC_LIMITER_1, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(0xF << 4);                                                     /* clear config */
    conf |= decay << 4;                                                      /* set decay */
    res = a_wm8978_iic_write(handle, WM8978_REG_DAC_LIMITER_1, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_dac_limiter_attack(wm8978_handle_t *handle, wm8978_dac_limiter_attack_t attack)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_DAC_LIMITER_1, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(0xF << 0);                                                     /* clear config */
    conf |= attack << 0;                                                     /* set attack */
    res = a_wm8978_iic_write(handle, WM8978_REG_DAC_LIMITER_1, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_dac_limiter_level(wm8978_handle_t *handle, wm8978_dac_limiter_level_t level)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_DAC_LIMITER_2, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(7 << 4);                                                       /* clear config */
    conf |= level << 4;                                                      /* set level */
    res = a_wm8978_iic_write(handle, WM8978_REG_DAC_LIMITER_2, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_dac_limiter_volume_boost(wm8978_handle_t *handle, uint8_t db)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (db > 12)                                                             /* check db */
    {
        handle->debug_print("wm8978: boost > 12.\n");                        /* boost > 12 */
        
        return 4;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_DAC_LIMITER_2, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(0xF << 0);                                                     /* clear config */
    conf |= db << 0;                                                         /* set db */
    res = a_wm8978_iic_write(handle, WM8978_REG_DAC_LIMITER_2, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_notch_filter(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_NOTCH_FILTER_1, &conf);       /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 7);                                                       /* clear config */
    conf |= enable << 7;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_NOTCH_FILTER_1, conf);       /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_notch_filter_a0_coefficient_bit_13_7(wm8978_handle_t *handle, wm8978_bool_t update_once, uint8_t coefficient)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (coefficient > 0x7F)                                                  /* check coefficient */
    {
        handle->debug_print("wm8978: coefficient > 0x7F.\n");                /* coefficient > 0x7F*/
        
        return 4;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_NOTCH_FILTER_1, &conf);       /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 8);                                                       /* clear config */
    conf |= update_once << 8;                                                /* set bool */
    conf &= ~(0x7F << 0);                                                    /* clear config */
    conf |= coefficient << 0;                                                /* set coefficient */
    res = a_wm8978_iic_write(handle, WM8978_REG_NOTCH_FILTER_1, conf);       /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_notch_filter_a0_coefficient_bit_6_0(wm8978_handle_t *handle, wm8978_bool_t update_once, uint8_t coefficient)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (coefficient > 0x7F)                                                  /* check coefficient */
    {
        handle->debug_print("wm8978: coefficient > 0x7F.\n");                /* coefficient > 0x7F*/
        
        return 4;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_NOTCH_FILTER_2, &conf);       /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 8);                                                       /* clear config */
    conf |= update_once << 8;                                                /* set bool */
    conf &= ~(0x7F << 0);                                                    /* clear config */
    conf |= coefficient << 0;                                                /* set coefficient */
    res = a_wm8978_iic_write(handle, WM8978_REG_NOTCH_FILTER_2, conf);       /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_notch_filter_a1_coefficient_bit_13_7(wm8978_handle_t *handle, wm8978_bool_t update_once, uint8_t coefficient)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (coefficient > 0x7F)                                                  /* check coefficient */
    {
        handle->debug_print("wm8978: coefficient > 0x7F.\n");                /* coefficient > 0x7F*/
        
        return 4;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_NOTCH_FILTER_3, &conf);       /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 8);                                                       /* clear config */
    conf |= update_once << 8;                                                /* set bool */
    conf &= ~(0x7F << 0);                                                    /* clear config */
    conf |= coefficient << 0;                                                /* set coefficient */
    res = a_wm8978_iic_write(handle, WM8978_REG_NOTCH_FILTER_3, conf);       /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_notch_filter_a1_coefficient_bit_6_0(wm8978_handle_t *handle, wm8978_bool_t update_once, uint8_t coefficient)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (coefficient > 0x7F)                                                  /* check coefficient */
    {
        handle->debug_print("wm8978: coefficient > 0x7F.\n");                /* coefficient > 0x7F*/
        
        return 4;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_NOTCH_FILTER_4, &conf);       /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 8);                                                       /* clear config */
    conf |= update_once << 8;                                                /* set bool */
    conf &= ~(0x7F << 0);                                                    /* clear config */
    conf |= coefficient << 0;                                                /* set coefficient */
    res = a_wm8978_iic_write(handle, WM8978_REG_NOTCH_FILTER_4, conf);       /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_alc(wm8978_handle_t *handle, wm8978_alc_t alc)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ALC_CONTROL_1, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(3 << 7);                                                       /* clear config */
    conf |= alc << 7;                                                        /* set alc */
    res = a_wm8978_iic_write(handle, WM8978_REG_ALC_CONTROL_1, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_alc_max_gain(wm8978_handle_t *handle, wm8978_max_gain_t gain)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ALC_CONTROL_1, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(7 << 3);                                                       /* clear config */
    conf |= gain << 3;                                                       /* set gain */
    res = a_wm8978_iic_write(handle, WM8978_REG_ALC_CONTROL_1, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_alc_min_gain(wm8978_handle_t *handle, wm8978_min_gain_t gain)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ALC_CONTROL_1, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(7 << 0);                                                       /* clear config */
    conf |= gain << 0;                                                       /* set gain */
    res = a_wm8978_iic_write(handle, WM8978_REG_ALC_CONTROL_1, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_alc_hold_time(wm8978_handle_t *handle, uint8_t t)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (t > 0xF)                                                             /* check t */
    {
        handle->debug_print("wm8978: t > 0xF.\n");                           /* t > 0xF */
        
        return 4;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ALC_CONTROL_2, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(0xF << 4);                                                     /* clear config */
    conf |= t << 4;                                                          /* set time */
    res = a_wm8978_iic_write(handle, WM8978_REG_ALC_CONTROL_2, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_alc_hold_time_convert_to_register(wm8978_handle_t *handle, float ms, uint8_t *reg)
{
    if (handle == NULL)                /* check handle */
    {
        return 2;                      /* return error */
    }
    if (handle->inited != 1)           /* check handle initialization */
    {
        return 3;                      /* return error */
    }
    
    *reg = (uint8_t)(ms / 2.67f);      /* convert */
    
    return 0;                          /* success return 0 */
}

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
uint8_t wm8978_alc_hold_time_convert_to_data(wm8978_handle_t *handle, uint8_t reg, float *ms)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    *ms = (float)(reg * 2.67f);     /* convert */
    
    return 0;                       /* success return 0 */
}

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
uint8_t wm8978_set_alc_level(wm8978_handle_t *handle, wm8978_alc_level_t level)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ALC_CONTROL_2, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(0xF << 0);                                                     /* clear config */
    conf |= level << 0;                                                      /* set level */
    res = a_wm8978_iic_write(handle, WM8978_REG_ALC_CONTROL_2, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_alc_mode(wm8978_handle_t *handle, wm8978_alc_mode_t mode)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ALC_CONTROL_3, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 8);                                                       /* clear config */
    conf |= mode << 8;                                                       /* set mode */
    res = a_wm8978_iic_write(handle, WM8978_REG_ALC_CONTROL_3, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_alc_decay(wm8978_handle_t *handle, uint8_t decay)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (decay > 0xF)                                                         /* check decay */
    {
        handle->debug_print("wm8978: decay > 0xF.\n");                       /* decay > 0xF */
        
        return 4;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ALC_CONTROL_3, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(0xF << 4);                                                     /* clear config */
    conf |= decay << 4;                                                      /* set decay */
    res = a_wm8978_iic_write(handle, WM8978_REG_ALC_CONTROL_3, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_alc_attack(wm8978_handle_t *handle, uint8_t attack)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (attack > 0xF)                                                        /* check attack */
    {
        handle->debug_print("wm8978: attack > 0xF.\n");                      /* attack > 0xF */
        
        return 4;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ALC_CONTROL_3, &conf);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(0xF << 0);                                                     /* clear config */
    conf |= attack << 0;                                                     /* set attack */
    res = a_wm8978_iic_write(handle, WM8978_REG_ALC_CONTROL_3, conf);        /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_alc_noise_gate(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_NOISE_GATE, &conf);        /* read config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");             /* read config failed */
        
        return 1;                                                         /* return error */
    }
    conf &= ~(1 << 3);                                                    /* clear config */
    conf |= enable << 3;                                                  /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_NOISE_GATE, conf);        /* write config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");            /* write config failed */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t wm8978_set_alc_noise_gate_threshold(wm8978_handle_t *handle, uint8_t threshold)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    if (threshold > 0x7)                                                  /* check threshold */
    {
        handle->debug_print("wm8978: threshold > 0x7.\n");                /* threshold > 0x7 */
        
        return 4;                                                         /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_NOISE_GATE, &conf);        /* read config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");             /* read config failed */
        
        return 1;                                                         /* return error */
    }
    conf &= ~(7 << 0);                                                    /* clear config */
    conf |= threshold << 0;                                               /* set threshold */
    res = a_wm8978_iic_write(handle, WM8978_REG_NOISE_GATE, conf);        /* write config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");            /* write config failed */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t wm8978_alc_noise_gate_threshold_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *reg = (uint8_t)((db + 39) / (-6));    /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_alc_noise_gate_threshold_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *db = (int8_t)(reg * (-6) - 39);       /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_set_mclk_divide_by_2(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_PLL_N, &conf);        /* read config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");        /* read config failed */
        
        return 1;                                                    /* return error */
    }
    conf &= ~(1 << 4);                                               /* clear config */
    conf |= enable << 4;                                             /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_PLL_N, conf);        /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t wm8978_set_plln(wm8978_handle_t *handle, uint8_t n)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    if (n > 0xF)                                                     /* check n */
    {
        handle->debug_print("wm8978: n > 0xF.\n");                   /* n > 0xF */
        
        return 4;                                                    /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_PLL_N, &conf);        /* read config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");        /* read config failed */
        
        return 1;                                                    /* return error */
    }
    conf &= ~(0xF << 0);                                             /* clear config */
    conf |= n << 0;                                                  /* set plln */
    res = a_wm8978_iic_write(handle, WM8978_REG_PLL_N, conf);        /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t wm8978_set_pll_freq(wm8978_handle_t *handle, uint32_t freq)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    conf = (freq >> 0) & 0x1FF;                                      /* set freq */
    res = a_wm8978_iic_write(handle, WM8978_REG_PLL_K3, conf);       /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    conf = (freq >> 9) & 0x1FF;                                      /* set freq */
    res = a_wm8978_iic_write(handle, WM8978_REG_PLL_K2, conf);       /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    conf = (freq >> 18) & 0x3F;                                      /* set freq */
    res = a_wm8978_iic_write(handle, WM8978_REG_PLL_K1, conf);       /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t wm8978_set_depth_3d(wm8978_handle_t *handle, uint8_t depth)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    if (depth > 0xF)                                                 /* check depth */
    {
        handle->debug_print("wm8978: depth > 0xF.\n");               /* depth > 0xF */
        
        return 4;                                                    /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_3D_CONTROL, &conf);   /* read config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");        /* read config failed */
        
        return 1;                                                    /* return error */
    }
    conf &= ~(0xF << 0);                                             /* clear config */
    conf |= depth << 0;                                              /* set depth */
    res = a_wm8978_iic_write(handle, WM8978_REG_3D_CONTROL, conf);   /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t wm8978_depth_3d_convert_to_register(wm8978_handle_t *handle, float percent, uint8_t *reg)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }
    if (handle->inited != 1)                   /* check handle initialization */
    {
        return 3;                              /* return error */
    }
    
    *reg = (uint8_t)(percent / 6.67f);         /* convert */
    
    return 0;                                  /* success return 0 */
}

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
uint8_t wm8978_depth_3d_convert_to_data(wm8978_handle_t *handle, uint8_t reg, float *percent)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *percent = (float)(reg) * 6.67f;       /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_set_mute_input_to_inv_rout2_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_BEEP_CONTROL, &conf);    /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 5);                                                  /* clear config */
    conf |= enable << 5;                                                /* set enable */
    res = a_wm8978_iic_write(handle, WM8978_REG_BEEP_CONTROL, conf);    /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_inv_rout2_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_BEEP_CONTROL, &conf);    /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 4);                                                  /* clear config */
    conf |= enable << 4;                                                /* set enable */
    res = a_wm8978_iic_write(handle, WM8978_REG_BEEP_CONTROL, conf);    /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_beep_volume(wm8978_handle_t *handle, uint8_t vol)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    if (vol > 0x7)                                                      /* check vol */
    {
        handle->debug_print("wm8978: vol > 0x7.\n");                    /* vol > 0x7 */
        
        return 4;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_BEEP_CONTROL, &conf);    /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(7 << 1);                                                  /* clear config */
    conf |= vol << 1;                                                   /* set vol */
    res = a_wm8978_iic_write(handle, WM8978_REG_BEEP_CONTROL, conf);    /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_beep_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *reg = (uint8_t)(db + 15) / 3;         /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_beep_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }
    if (handle->inited != 1)            /* check handle initialization */
    {
        return 3;                       /* return error */
    }
    
    *db = (int8_t)(reg * 3 - 15);       /* convert */
    
    return 0;                           /* success return 0 */
}

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
uint8_t wm8978_set_beep(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_BEEP_CONTROL, &conf);    /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 0);                                                  /* clear config */
    conf |= enable << 0;                                                /* set enable */
    res = a_wm8978_iic_write(handle, WM8978_REG_BEEP_CONTROL, conf);    /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_microphone_bias_voltage(wm8978_handle_t *handle, wm8978_avdd_t avdd)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_INPUT_CTRL, &conf);   /* read config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");        /* read config failed */
        
        return 1;                                                    /* return error */
    }
    conf &= ~(1 << 8);                                               /* clear config */
    conf |= avdd << 8;                                               /* set avdd */
    res = a_wm8978_iic_write(handle, WM8978_REG_INPUT_CTRL, conf);   /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t wm8978_set_right_channel_input_pga_positive(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_INPUT_CTRL, &conf);   /* read config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");        /* read config failed */
        
        return 1;                                                    /* return error */
    }
    conf &= ~(1 << 6);                                               /* clear config */
    conf |= enable << 6;                                             /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_INPUT_CTRL, conf);   /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t wm8978_set_right_channel_input_pga_negative(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_INPUT_CTRL, &conf);   /* read config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");        /* read config failed */
        
        return 1;                                                    /* return error */
    }
    conf &= ~(1 << 5);                                               /* clear config */
    conf |= enable << 5;                                             /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_INPUT_CTRL, conf);   /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t wm8978_set_right_channel_input_pga_amplifier_positive(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_INPUT_CTRL, &conf);   /* read config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");        /* read config failed */
        
        return 1;                                                    /* return error */
    }
    conf &= ~(1 << 4);                                               /* clear config */
    conf |= enable << 4;                                             /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_INPUT_CTRL, conf);   /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t wm8978_set_left_channel_input_pga_positive(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_INPUT_CTRL, &conf);   /* read config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");        /* read config failed */
        
        return 1;                                                    /* return error */
    }
    conf &= ~(1 << 2);                                               /* clear config */
    conf |= enable << 2;                                             /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_INPUT_CTRL, conf);   /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t wm8978_set_left_channel_input_pga_negative(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_INPUT_CTRL, &conf);   /* read config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");        /* read config failed */
        
        return 1;                                                    /* return error */
    }
    conf &= ~(1 << 1);                                               /* clear config */
    conf |= enable << 1;                                             /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_INPUT_CTRL, conf);   /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t wm8978_set_left_channel_input_pga_amplifier_positive(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_INPUT_CTRL, &conf);   /* read config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");        /* read config failed */
        
        return 1;                                                    /* return error */
    }
    conf &= ~(1 << 0);                                               /* clear config */
    conf |= enable << 0;                                             /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_INPUT_CTRL, conf);   /* write config */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");       /* write config failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t wm8978_set_left_input_pga_update(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LEFT_INP_PGA_CTRL, &conf);   /* read config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");               /* read config failed */
        
        return 1;                                                           /* return error */
    }
    conf &= ~(1 << 8);                                                      /* clear config */
    conf |= enable << 8;                                                    /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_INP_PGA_CTRL, conf);   /* write config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");              /* write config failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t wm8978_set_left_channel_input_pga_zero_cross(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LEFT_INP_PGA_CTRL, &conf);   /* read config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");               /* read config failed */
        
        return 1;                                                           /* return error */
    }
    conf &= ~(1 << 7);                                                      /* clear config */
    conf |= enable << 7;                                                    /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_INP_PGA_CTRL, conf);   /* write config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");              /* write config failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t wm8978_set_left_channel_input_pga_mute(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LEFT_INP_PGA_CTRL, &conf);   /* read config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");               /* read config failed */
        
        return 1;                                                           /* return error */
    }
    conf &= ~(1 << 6);                                                      /* clear config */
    conf |= enable << 6;                                                    /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_INP_PGA_CTRL, conf);   /* write config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");              /* write config failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t wm8978_set_left_channel_input_pga_volume(wm8978_handle_t *handle, uint8_t volume)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (volume > 0x3F)                                                      /* check volume */
    {
        handle->debug_print("wm8978: volume > 0x3F.\n");                    /* volume > 0x3F */
        
        return 4;                                                           /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LEFT_INP_PGA_CTRL, &conf);   /* read config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");               /* read config failed */
        
        return 1;                                                           /* return error */
    }
    conf &= ~(0x3F << 0);                                                   /* clear config */
    conf |= volume << 0;                                                    /* set volume */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_INP_PGA_CTRL, conf);   /* write config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");              /* write config failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t wm8978_left_channel_input_pga_volume_convert_to_register(wm8978_handle_t *handle, float db, uint8_t *reg)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }
    if (handle->inited != 1)                   /* check handle initialization */
    {
        return 3;                              /* return error */
    }
    
    *reg = (uint8_t)((db + 12.0f) / 0.75f);    /* convert */
    
    return 0;                                  /* success return 0 */
}

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
uint8_t wm8978_left_channel_input_pga_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, float *db)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *db = (float)(reg) * 0.75f - 12.0f;    /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_set_right_input_pga_update(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_RIGHT_INP_PGA_CTRL, &conf);  /* read config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");               /* read config failed */
        
        return 1;                                                           /* return error */
    }
    conf &= ~(1 << 8);                                                      /* clear config */
    conf |= enable << 8;                                                    /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_INP_PGA_CTRL, conf);  /* write config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");              /* write config failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t wm8978_set_right_channel_input_pga_zero_cross(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_RIGHT_INP_PGA_CTRL, &conf);  /* read config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");               /* read config failed */
        
        return 1;                                                           /* return error */
    }
    conf &= ~(1 << 7);                                                      /* clear config */
    conf |= enable << 7;                                                    /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_INP_PGA_CTRL, conf);  /* write config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");              /* write config failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t wm8978_set_right_channel_input_pga_mute(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_RIGHT_INP_PGA_CTRL, &conf);  /* read config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");               /* read config failed */
        
        return 1;                                                           /* return error */
    }
    conf &= ~(1 << 6);                                                      /* clear config */
    conf |= enable << 6;                                                    /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_INP_PGA_CTRL, conf);  /* write config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");              /* write config failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t wm8978_set_right_channel_input_pga_volume(wm8978_handle_t *handle, uint8_t volume)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (volume > 0x3F)                                                      /* check volume */
    {
        handle->debug_print("wm8978: volume > 0x3F.\n");                    /* volume > 0x3F */
        
        return 4;                                                           /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_RIGHT_INP_PGA_CTRL, &conf);  /* read config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");               /* read config failed */
        
        return 1;                                                           /* return error */
    }
    conf &= ~(0x3F << 0);                                                   /* clear config */
    conf |= volume << 0;                                                    /* set volume */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_INP_PGA_CTRL, conf);  /* write config */
    if (res != 0)                                                           /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");              /* write config failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t wm8978_right_channel_input_pga_volume_convert_to_register(wm8978_handle_t *handle, float db, uint8_t *reg)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }
    if (handle->inited != 1)                   /* check handle initialization */
    {
        return 3;                              /* return error */
    }
    
    *reg = (uint8_t)((db + 12.0f) / 0.75f);    /* convert */
    
    return 0;                                  /* success return 0 */
}

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
uint8_t wm8978_right_channel_input_pga_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, float *db)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *db = (float)(reg) * 0.75f - 12.0f;    /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_set_left_channel_input_pga_boost(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LEFT_ADC_BOOST_CTRL, &conf);        /* read config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                      /* read config failed */
        
        return 1;                                                                  /* return error */
    }
    conf &= ~(1 << 8);                                                             /* clear config */
    conf |= enable << 8;                                                           /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_ADC_BOOST_CTRL, conf);        /* write config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                     /* write config failed */
        
        return 1;                                                                  /* return error */
    }
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t wm8978_set_left_channel_input_boost_stage(wm8978_handle_t *handle, uint8_t stage)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    if (stage > 0x7)                                                               /* check stage */
    {
        handle->debug_print("wm8978: stage > 0x7.\n");                             /* stage > 0x7 */
        
        return 4;                                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LEFT_ADC_BOOST_CTRL, &conf);        /* read config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                      /* read config failed */
        
        return 1;                                                                  /* return error */
    }
    conf &= ~(0x7 << 4);                                                           /* clear config */
    conf |= stage << 4;                                                            /* set stage */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_ADC_BOOST_CTRL, conf);        /* write config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                     /* write config failed */
        
        return 1;                                                                  /* return error */
    }
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t wm8978_left_channel_input_boost_stage_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *reg = (uint8_t)(db + 15) / 3;         /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_left_channel_input_boost_stage_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }
    if (handle->inited != 1)            /* check handle initialization */
    {
        return 3;                       /* return error */
    }
    
    *db = (int8_t)(reg * 3 - 15);       /* convert */
    
    return 0;                           /* success return 0 */
}

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
uint8_t wm8978_set_auxiliary_amplifier_left_channel_input_boost_stage(wm8978_handle_t *handle, uint8_t stage)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    if (stage > 0x7)                                                               /* check stage */
    {
        handle->debug_print("wm8978: stage > 0x7.\n");                             /* stage > 0x7 */
        
        return 4;                                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LEFT_ADC_BOOST_CTRL, &conf);        /* read config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                      /* read config failed */
        
        return 1;                                                                  /* return error */
    }
    conf &= ~(0x7 << 0);                                                           /* clear config */
    conf |= stage << 0;                                                            /* set stage */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_ADC_BOOST_CTRL, conf);        /* write config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                     /* write config failed */
        
        return 1;                                                                  /* return error */
    }
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t wm8978_auxiliary_amplifier_left_channel_input_boost_stage_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *reg = (uint8_t)(db + 15) / 3;         /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_auxiliary_amplifier_left_channel_input_boost_stage_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }
    if (handle->inited != 1)            /* check handle initialization */
    {
        return 3;                       /* return error */
    }
    
    *db = (int8_t)(reg * 3 - 15);       /* convert */
    
    return 0;                           /* success return 0 */
}

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
uint8_t wm8978_set_right_channel_input_pga_boost(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_RIGHT_ADC_BOOST_CTRL, &conf);       /* read config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                      /* read config failed */
        
        return 1;                                                                  /* return error */
    }
    conf &= ~(1 << 8);                                                             /* clear config */
    conf |= enable << 8;                                                           /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_ADC_BOOST_CTRL, conf);       /* write config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                     /* write config failed */
        
        return 1;                                                                  /* return error */
    }
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t wm8978_set_right_channel_input_boost_stage(wm8978_handle_t *handle, uint8_t stage)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    if (stage > 0x7)                                                               /* check stage */
    {
        handle->debug_print("wm8978: stage > 0x7.\n");                             /* stage > 0x7 */
        
        return 4;                                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_RIGHT_ADC_BOOST_CTRL, &conf);       /* read config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                      /* read config failed */
        
        return 1;                                                                  /* return error */
    }
    conf &= ~(0x7 << 4);                                                           /* clear config */
    conf |= stage << 4;                                                            /* set stage */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_ADC_BOOST_CTRL, conf);       /* write config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                     /* write config failed */
        
        return 1;                                                                  /* return error */
    }
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t wm8978_right_channel_input_boost_stage_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *reg = (uint8_t)(db + 15) / 3;         /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_right_channel_input_boost_stage_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }
    if (handle->inited != 1)            /* check handle initialization */
    {
        return 3;                       /* return error */
    }
    
    *db = (int8_t)(reg * 3 - 15);       /* convert */
    
    return 0;                           /* success return 0 */
}

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
uint8_t wm8978_set_auxiliary_amplifier_right_channel_input_boost_stage(wm8978_handle_t *handle, uint8_t stage)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    if (stage > 0x7)                                                               /* check stage */
    {
        handle->debug_print("wm8978: stage > 0x7.\n");                             /* stage > 0x7 */
        
        return 4;                                                                  /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_RIGHT_ADC_BOOST_CTRL, &conf);       /* read config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                      /* read config failed */
        
        return 1;                                                                  /* return error */
    }
    conf &= ~(0x7 << 0);                                                           /* clear config */
    conf |= stage << 0;                                                            /* set stage */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_ADC_BOOST_CTRL, conf);       /* write config */
    if (res != 0)                                                                  /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                     /* write config failed */
        
        return 1;                                                                  /* return error */
    }
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t wm8978_auxiliary_amplifier_right_channel_input_boost_stage_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *reg = (uint8_t)(db + 15) / 3;         /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_auxiliary_amplifier_right_channel_input_boost_stage_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }
    if (handle->inited != 1)            /* check handle initialization */
    {
        return 3;                       /* return error */
    }
    
    *db = (int8_t)(reg * 3 - 15);       /* convert */
    
    return 0;                           /* success return 0 */
}

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
uint8_t wm8978_set_left_dac_output_to_right_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUTPUT_CTRL, &conf);       /* read config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");             /* read config failed */
        
        return 1;                                                         /* return error */
    }
    conf &= ~(1 << 6);                                                    /* clear config */
    conf |= enable << 6;                                                  /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUTPUT_CTRL, conf);       /* write config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");            /* write config failed */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t wm8978_set_right_dac_output_to_left_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUTPUT_CTRL, &conf);       /* read config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");             /* read config failed */
        
        return 1;                                                         /* return error */
    }
    conf &= ~(1 << 5);                                                    /* clear config */
    conf |= enable << 5;                                                  /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUTPUT_CTRL, conf);       /* write config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");            /* write config failed */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t wm8978_set_out4_boost(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUTPUT_CTRL, &conf);       /* read config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");             /* read config failed */
        
        return 1;                                                         /* return error */
    }
    conf &= ~(1 << 4);                                                    /* clear config */
    conf |= enable << 4;                                                  /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUTPUT_CTRL, conf);       /* write config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");            /* write config failed */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t wm8978_set_out3_boost(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUTPUT_CTRL, &conf);       /* read config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");             /* read config failed */
        
        return 1;                                                         /* return error */
    }
    conf &= ~(1 << 3);                                                    /* clear config */
    conf |= enable << 3;                                                  /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUTPUT_CTRL, conf);       /* write config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");            /* write config failed */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t wm8978_set_speaker_boost(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUTPUT_CTRL, &conf);       /* read config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");             /* read config failed */
        
        return 1;                                                         /* return error */
    }
    conf &= ~(1 << 2);                                                    /* clear config */
    conf |= enable << 2;                                                  /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUTPUT_CTRL, conf);       /* write config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");            /* write config failed */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t wm8978_set_thermal_shutdown(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUTPUT_CTRL, &conf);       /* read config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");             /* read config failed */
        
        return 1;                                                         /* return error */
    }
    conf &= ~(1 << 1);                                                    /* clear config */
    conf |= enable << 1;                                                  /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUTPUT_CTRL, conf);       /* write config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");            /* write config failed */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t wm8978_set_vref_to_analogue_output_resistance(wm8978_handle_t *handle, wm8978_vref_t vref)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUTPUT_CTRL, &conf);       /* read config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");             /* read config failed */
        
        return 1;                                                         /* return error */
    }
    conf &= ~(1 << 0);                                                    /* clear config */
    conf |= vref << 0;                                                    /* set vref */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUTPUT_CTRL, conf);       /* write config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");            /* write config failed */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t wm8978_set_aux_left_channel_input_to_left_mixer_volume(wm8978_handle_t *handle, uint8_t vol)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (vol > 0x7)                                                            /* check vol */
    {
        handle->debug_print("wm8978: vol > 0x7.\n");                          /* vol > 0x7 */
        
        return 4;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LEFT_MIXER_CTRL, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(7 << 6);                                                        /* clear config */
    conf |= vol << 6;                                                         /* set vol */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_MIXER_CTRL, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_aux_left_channel_input_to_left_mixer_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *reg = (uint8_t)(db + 15) / 3;         /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_aux_left_channel_input_to_left_mixer_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }
    if (handle->inited != 1)            /* check handle initialization */
    {
        return 3;                       /* return error */
    }
    
    *db = (int8_t)(reg * 3 - 15);       /* convert */
    
    return 0;                           /* success return 0 */
}

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
uint8_t wm8978_set_left_auxiliary_input_to_left_channel_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LEFT_MIXER_CTRL, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 5);                                                        /* clear config */
    conf |= enable << 5;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_MIXER_CTRL, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_left_bypass_volume_control_to_output_channel_mixer(wm8978_handle_t *handle, uint8_t vol)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (vol > 0x7)                                                            /* check vol */
    {
        handle->debug_print("wm8978: vol > 0x7.\n");                          /* vol > 0x7 */
        
        return 4;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LEFT_MIXER_CTRL, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(7 << 2);                                                        /* clear config */
    conf |= vol << 2;                                                         /* set vol */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_MIXER_CTRL, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_left_bypass_volume_control_to_output_channel_mixer_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *reg = (uint8_t)(db + 15) / 3;         /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_left_bypass_volume_control_to_output_channel_mixer_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }
    if (handle->inited != 1)            /* check handle initialization */
    {
        return 3;                       /* return error */
    }
    
    *db = (int8_t)(reg * 3 - 15);       /* convert */
    
    return 0;                           /* success return 0 */
}

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
uint8_t wm8978_set_left_bypass_path_to_left_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LEFT_MIXER_CTRL, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 1);                                                        /* clear config */
    conf |= enable << 1;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_MIXER_CTRL, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_left_dac_output_to_left_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LEFT_MIXER_CTRL, &conf);       /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 0);                                                        /* clear config */
    conf |= enable << 0;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LEFT_MIXER_CTRL, conf);       /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_aux_right_channel_input_to_right_mixer_volume(wm8978_handle_t *handle, uint8_t vol)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (vol > 0x7)                                                            /* check vol */
    {
        handle->debug_print("wm8978: vol > 0x7.\n");                          /* vol > 0x7 */
        
        return 4;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_RIGHT_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(7 << 6);                                                        /* clear config */
    conf |= vol << 6;                                                         /* set vol */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_aux_right_channel_input_to_right_mixer_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *reg = (uint8_t)(db + 15) / 3;         /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_aux_right_channel_input_to_right_mixer_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }
    if (handle->inited != 1)            /* check handle initialization */
    {
        return 3;                       /* return error */
    }
    
    *db = (int8_t)(reg * 3 - 15);       /* convert */
    
    return 0;                           /* success return 0 */
}

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
uint8_t wm8978_set_right_auxiliary_input_to_right_channel_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_RIGHT_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 5);                                                        /* clear config */
    conf |= enable << 5;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_right_bypass_volume_control_to_output_channel_mixer(wm8978_handle_t *handle, uint8_t vol)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (vol > 0x7)                                                            /* check vol */
    {
        handle->debug_print("wm8978: vol > 0x7.\n");                          /* vol > 0x7 */
        
        return 4;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_RIGHT_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(7 << 2);                                                        /* clear config */
    conf |= vol << 2;                                                         /* set vol */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_right_bypass_volume_control_to_output_channel_mixer_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *reg = (uint8_t)(db + 15) / 3;         /* convert */
    
    return 0;                              /* success return 0 */
}

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
uint8_t wm8978_right_bypass_volume_control_to_output_channel_mixer_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }
    if (handle->inited != 1)            /* check handle initialization */
    {
        return 3;                       /* return error */
    }
    
    *db = (int8_t)(reg * 3 - 15);       /* convert */
    
    return 0;                           /* success return 0 */
}

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
uint8_t wm8978_set_right_bypass_path_to_right_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_RIGHT_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 1);                                                        /* clear config */
    conf |= enable << 1;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_right_dac_output_to_right_output_mixer(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_RIGHT_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 1;                                                             /* return error */
    }
    conf &= ~(1 << 0);                                                        /* clear config */
    conf |= enable << 0;                                                      /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_RIGHT_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_lout1_update(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LOUT1_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 8);                                                  /* clear config */
    conf |= enable << 8;                                                /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LOUT1_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_lout1_headphone_volume_zero_cross(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LOUT1_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 7);                                                  /* clear config */
    conf |= enable << 7;                                                /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LOUT1_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_lout1_left_headphone_output_mute(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LOUT1_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 6);                                                  /* clear config */
    conf |= enable << 6;                                                /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LOUT1_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_lout1_left_headphone_output_volume(wm8978_handle_t *handle, uint8_t vol)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    if (vol > 0x3F)                                                     /* check vol */
    {
        handle->debug_print("wm8978: vol > 0x3F.\n");                   /* vol > 0x3F */
        
        return 4;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LOUT1_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(0x3F << 0);                                               /* clear config */
    conf |= vol << 0;                                                   /* set vol */
    res = a_wm8978_iic_write(handle, WM8978_REG_LOUT1_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_lout1_left_headphone_output_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                /* check handle */
    {
        return 2;                      /* return error */
    }
    if (handle->inited != 1)           /* check handle initialization */
    {
        return 3;                      /* return error */
    }
    
    *reg = (uint8_t)(db + 57);         /* convert */
    
    return 0;                          /* success return 0 */
}

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
uint8_t wm8978_lout1_left_headphone_output_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    *db = (int8_t)(reg - 57);       /* convert */
    
    return 0;                       /* success return 0 */
}

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
uint8_t wm8978_set_rout1_update(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ROUT1_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 8);                                                  /* clear config */
    conf |= enable << 8;                                                /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_ROUT1_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_rout1_headphone_volume_zero_cross(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ROUT1_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 7);                                                  /* clear config */
    conf |= enable << 7;                                                /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_ROUT1_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_rout1_right_headphone_output_mute(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ROUT1_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 6);                                                  /* clear config */
    conf |= enable << 6;                                                /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_ROUT1_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_rout1_right_headphone_output_volume(wm8978_handle_t *handle, uint8_t vol)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    if (vol > 0x3F)                                                     /* check vol */
    {
        handle->debug_print("wm8978: vol > 0x3F.\n");                   /* vol > 0x3F */
        
        return 4;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ROUT1_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(0x3F << 0);                                               /* clear config */
    conf |= vol << 0;                                                   /* set vol */
    res = a_wm8978_iic_write(handle, WM8978_REG_ROUT1_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_rout1_right_headphone_output_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                /* check handle */
    {
        return 2;                      /* return error */
    }
    if (handle->inited != 1)           /* check handle initialization */
    {
        return 3;                      /* return error */
    }
    
    *reg = (uint8_t)(db + 57);         /* convert */
    
    return 0;                          /* success return 0 */
}

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
uint8_t wm8978_rout1_right_headphone_output_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    *db = (int8_t)(reg - 57);       /* convert */
    
    return 0;                       /* success return 0 */
}

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
uint8_t wm8978_set_lout2_update(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LOUT2_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 8);                                                  /* clear config */
    conf |= enable << 8;                                                /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LOUT2_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_lout2_speaker_volume_zero_cross(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LOUT2_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 7);                                                  /* clear config */
    conf |= enable << 7;                                                /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LOUT2_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_lout2_left_speaker_output_mute(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LOUT2_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 6);                                                  /* clear config */
    conf |= enable << 6;                                                /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_LOUT2_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_lout2_left_speaker_output_volume(wm8978_handle_t *handle, uint8_t vol)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    if (vol > 0x3F)                                                     /* check vol */
    {
        handle->debug_print("wm8978: vol > 0x3F.\n");                   /* vol > 0x3F */
        
        return 4;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_LOUT2_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(0x3F << 0);                                               /* clear config */
    conf |= vol << 0;                                                   /* set vol */
    res = a_wm8978_iic_write(handle, WM8978_REG_LOUT2_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_lout2_left_speaker_output_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                /* check handle */
    {
        return 2;                      /* return error */
    }
    if (handle->inited != 1)           /* check handle initialization */
    {
        return 3;                      /* return error */
    }
    
    *reg = (uint8_t)(db + 57);         /* convert */
    
    return 0;                          /* success return 0 */
}

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
uint8_t wm8978_lout2_left_speaker_output_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    *db = (int8_t)(reg - 57);       /* convert */
    
    return 0;                       /* success return 0 */
}

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
uint8_t wm8978_set_rout2_update(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ROUT2_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 8);                                                  /* clear config */
    conf |= enable << 8;                                                /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_ROUT2_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_rout2_speaker_volume_zero_cross(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ROUT2_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 7);                                                  /* clear config */
    conf |= enable << 7;                                                /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_ROUT2_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_rout2_right_speaker_output_mute(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ROUT2_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(1 << 6);                                                  /* clear config */
    conf |= enable << 6;                                                /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_ROUT2_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_set_rout2_right_speaker_output_volume(wm8978_handle_t *handle, uint8_t vol)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    if (vol > 0x3F)                                                     /* check vol */
    {
        handle->debug_print("wm8978: vol > 0x3F.\n");                   /* vol > 0x3F */
        
        return 4;                                                       /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_ROUT2_CTRL, &conf);      /* read config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");           /* read config failed */
        
        return 1;                                                       /* return error */
    }
    conf &= ~(0x3F << 0);                                               /* clear config */
    conf |= vol << 0;                                                   /* set vol */
    res = a_wm8978_iic_write(handle, WM8978_REG_ROUT2_CTRL, conf);      /* write config */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");          /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t wm8978_rout2_right_speaker_output_volume_convert_to_register(wm8978_handle_t *handle, int8_t db, uint8_t *reg)
{
    if (handle == NULL)                /* check handle */
    {
        return 2;                      /* return error */
    }
    if (handle->inited != 1)           /* check handle initialization */
    {
        return 3;                      /* return error */
    }
    
    *reg = (uint8_t)(db + 57);         /* convert */
    
    return 0;                          /* success return 0 */
}

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
uint8_t wm8978_rout2_right_speaker_output_volume_convert_to_data(wm8978_handle_t *handle, uint8_t reg, int8_t *db)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    *db = (int8_t)(reg - 57);       /* convert */
    
    return 0;                       /* success return 0 */
}

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
uint8_t wm8978_set_out3_mute(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUT3_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 6);                                                       /* clear config */
    conf |= enable << 6;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUT3_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_out4_mixer_output_to_out3(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUT3_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 3);                                                       /* clear config */
    conf |= enable << 3;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUT3_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_left_adc_input_to_out3(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUT3_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 2);                                                       /* clear config */
    conf |= enable << 2;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUT3_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_left_dac_mixer_to_out3(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUT3_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 1);                                                       /* clear config */
    conf |= enable << 1;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUT3_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_left_dac_output_to_out3(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUT3_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 0);                                                       /* clear config */
    conf |= enable << 0;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUT3_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_out4_mute(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUT4_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 6);                                                       /* clear config */
    conf |= enable << 6;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUT4_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_out4_attenuated_by_6db(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUT4_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 5);                                                       /* clear config */
    conf |= enable << 5;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUT4_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_left_dac_mixer_to_out4(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUT4_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 4);                                                       /* clear config */
    conf |= enable << 4;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUT4_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_left_dac_to_out4(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUT4_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 3);                                                       /* clear config */
    conf |= enable << 3;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUT4_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_right_adc_input_to_out4(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUT4_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 2);                                                       /* clear config */
    conf |= enable << 2;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUT4_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_right_dac_mixer_to_out4(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUT4_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 1);                                                       /* clear config */
    conf |= enable << 1;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUT4_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_set_right_dac_output_to_out4(wm8978_handle_t *handle, wm8978_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_OUT4_MIXER_CTRL, &conf);      /* read config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                /* read config failed */
        
        return 1;                                                            /* return error */
    }
    conf &= ~(1 << 0);                                                       /* clear config */
    conf |= enable << 0;                                                     /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_OUT4_MIXER_CTRL, conf);      /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_init(wm8978_handle_t *handle)
{
    uint8_t res;
    uint8_t i;
    uint16_t conf;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->debug_print == NULL)                                         /* check debug_print */
    {
        return 3;                                                            /* return error */
    }
    if (handle->iic_init == NULL)                                            /* check iic_init */
    {
        handle->debug_print("wm8978: iic_init is null.\n");                  /* iic_init is null */
        
        return 3;                                                            /* return error */
    }
    if (handle->iic_deinit == NULL)                                          /* check iic_deinit */
    {
        handle->debug_print("wm8978: iic_deinit is null.\n");                /* iic_deinit is null */
        
        return 3;                                                            /* return error */
    }
    if (handle->iic_write == NULL)                                           /* check iic_write */
    {
        handle->debug_print("wm8978: iic_write is null.\n");                 /* iic_write is null */
        
        return 3;                                                            /* return error */
    }
    if (handle->delay_ms == NULL)                                            /* check delay_ms */
    {
        handle->debug_print("wm8978: delay_ms is null.\n");                  /* delay_ms is null */
        
        return 3;                                                            /* return error */
    }
    
    if (handle->iic_init() != 0)                                             /* iic init */
    {
        handle->debug_print("wm8978: iic init failed.\n");                   /* iic init failed */
        
        return 1;                                                            /* return error */
    }
    conf = 0x0000;                                                           /* set any value */
    res = a_wm8978_iic_write(handle, WM8978_REG_SOFTWARE_RESET, conf);       /* write config */
    if (res != 0)                                                            /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");               /* write config failed */
        (void)handle->iic_deinit();                                          /* iic deinit */
        
        return 4;                                                            /* return error */
    }
    handle->delay_ms(100);                                                   /* delay 100ms */
    for (i = 0; i < 58; i++)                                                 /* set all */
    {
        handle->reg[i] = gsc_wm8978_init_reg[i];                             /* save regs */
    }
    handle->inited = 1;                                                      /* flag inited */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wm8978_deinit(wm8978_handle_t *handle)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_wm8978_iic_read(handle, WM8978_REG_POWER_MANAGE_2, &conf);        /* read config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: read config failed.\n");                 /* read config failed */
        
        return 4;                                                             /* return error */
    }
    conf &= ~(1 << 6);                                                        /* clear config */
    conf |= 1 << 6;                                                           /* set bool */
    res = a_wm8978_iic_write(handle, WM8978_REG_POWER_MANAGE_2, conf);        /* write config */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("wm8978: write config failed.\n");                /* write config failed */
        
        return 4;                                                             /* return error */
    }
    res = handle->iic_deinit();                                               /* close iic */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("wm8978: iic deinit failed.\n");                  /* iic deinit failed */
        
        return 1;                                                             /* return error */
    }
    handle->inited = 0;                                                       /* flag close */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t wm8978_set_reg(wm8978_handle_t *handle, uint8_t reg, uint16_t value)
{
    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }
    if (handle->inited != 1)                             /* check handle initialization */
    {
        return 3;                                        /* return error */
    }
    
    return a_wm8978_iic_write(handle, reg, value);       /* write reg */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a wm8978 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t wm8978_info(wm8978_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(wm8978_info_t));                         /* initialize wm8978 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC IIS", 8);                         /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
