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
 * @file      iis.c
 * @brief     iis source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-11-11
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/11/11  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "iis.h"

/* these pll parameters are valide when the f(VCO clock) = 1Mhz */
const uint32_t gc_iis_freq[8] = {8000, 11025, 16000, 22050, 32000, 44100, 48000, 96000};
const uint32_t gc_iis_plln[8] = {256, 429, 213, 429, 426, 271, 258, 344};
const uint32_t gc_iis_pllr[8] = {5, 4, 4, 4, 4, 6, 3, 1};

/**
 * @brief iis var definition
 */
I2S_HandleTypeDef g_iis_handle;               /**< iis handle */
DMA_HandleTypeDef g_iis_tx_dma_handle;        /**< iis tx dma handle */
DMA_HandleTypeDef g_iis_rx_dma_handle;        /**< iis rx dma handle */
static uint16_t gs_buf[1024 * 16];            /**< inner buffer */

/**
 * @brief     iis bus init
 * @param[in] standard is the iis standard
 * @param[in] mode is the iis mode
 * @param[in] polarity is the iis polarity
 * @param[in] format is the iis format
 * @param[in] enable is the mclk output
 * @param[in] freq is the set freq
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      SCLK is PB13, LRCK is PB12, SDOUT is PC2, SDIN is PC3 and MCLK is PC6
 *            standard can be I2S_STANDARD_PHILIPS, I2S_STANDARD_MSB, I2S_STANDARD_LSB, I2S_STANDARD_PCM_SHORT, I2S_STANDARD_PCM_LONG
 *            mode can be I2S_MODE_SLAVE_TX, I2S_MODE_SLAVE_RX, I2S_MODE_MASTER_TX, I2S_MODE_MASTER_RX
 *            polarity can be I2S_CPOL_LOW, I2S_CPOL_HIGH
 *            format can be I2S_DATAFORMAT_16B, I2S_DATAFORMAT_16B_EXTENDED, I2S_DATAFORMAT_24B, I2S_DATAFORMAT_32B
 *            enable can be I2S_MCLKOUTPUT_ENABLE, I2S_MCLKOUTPUT_DISABLE
 */
uint8_t iis_init(uint32_t standard, uint32_t mode, uint32_t polarity, uint32_t format, uint32_t enable, uint32_t freq)
{
    g_iis_handle.Instance = SPI2;
    g_iis_handle.Init.Mode = mode;
    g_iis_handle.Init.Standard = standard;
    g_iis_handle.Init.DataFormat = format;
    g_iis_handle.Init.MCLKOutput = enable;
    g_iis_handle.Init.AudioFreq = freq;
    g_iis_handle.Init.CPOL = polarity;
    g_iis_handle.Init.ClockSource = I2S_CLOCK_PLL;
    g_iis_handle.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_ENABLE;
    
    /* iis init */
    if (HAL_I2S_Init(&g_iis_handle) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     set freq
 * @param[in] freq is the set freq
 * @return    status code
 *            - 0 success
 *            - 1 set failed
 *            - 2 can't find freq
 * @note      none
 */
uint8_t iis_set_freq(uint32_t freq)
{
    RCC_PeriphCLKInitTypeDef RCC_ExCLKInitStruct;
    uint8_t index = 0, freqindex = 0xFF;
    
    for(index = 0; index < 8; index++)
    {
        if(gc_iis_freq[index] == freq)
        {
          freqindex = index;
        }
    }
    HAL_RCCEx_GetPeriphCLKConfig(&RCC_ExCLKInitStruct); 
    if(freqindex != 0xFF)
    {
        RCC_ExCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
        RCC_ExCLKInitStruct.PLLI2S.PLLI2SN = gc_iis_plln[freqindex];
        RCC_ExCLKInitStruct.PLLI2S.PLLI2SR = gc_iis_pllr[freqindex];
        if (HAL_RCCEx_PeriphCLKConfig(&RCC_ExCLKInitStruct) != HAL_OK)
        {
            return 1;
        }
        
        return 0;
    } 
    else
    {
        return 2;
    }
}

/**
 * @brief  iis bus deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t iis_deinit(void)
{
    /* iis deinit */
    if (HAL_I2S_DeInit(&g_iis_handle) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     iis bus write
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t iis_write(uint16_t *buf, uint16_t len)
{
    if (HAL_I2S_Transmit_DMA(&g_iis_handle, buf, len) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      iis bus read
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t iis_read(uint16_t *buf, uint16_t len)
{
    if (len > 16 * 1024)
    {
        return 1;
    }
    
    if (HAL_I2SEx_TransmitReceive_DMA(&g_iis_handle, gs_buf, buf,len) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  iis bus stop
 * @return status code
 *         - 0 success
 *         - 1 stop failed
 * @note   none
 */
uint8_t iis_stop(void)
{
    if (HAL_I2S_DMAStop(&g_iis_handle) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  iis bus pause
 * @return status code
 *         - 0 success
 *         - 1 pause failed
 * @note   none
 */
uint8_t iis_pause(void)
{
    if (HAL_I2S_DMAPause(&g_iis_handle) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  iis bus resume
 * @return status code
 *         - 0 success
 *         - 1 resume failed
 * @note   none
 */
uint8_t iis_resume(void)
{
    if (HAL_I2S_DMAResume(&g_iis_handle) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  iis get handle
 * @return points to an iis handle
 * @note   none
 */
I2S_HandleTypeDef* iis_get_handle(void)
{
    return &g_iis_handle;
}

/**
 * @brief  iis get the tx dma handle
 * @return points to a tx dma handle
 * @note   none
 */
DMA_HandleTypeDef* iis_get_tx_dma_handle(void)
{
    return &g_iis_tx_dma_handle;
}

/**
 * @brief  iis get the rx dma handle
 * @return points to a rx dma handle
 * @note   none
 */
DMA_HandleTypeDef* iis_get_rx_dma_handle(void)
{
    return &g_iis_rx_dma_handle;
}
