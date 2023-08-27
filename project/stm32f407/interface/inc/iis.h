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
 * @file      iis.h
 * @brief     iis header file
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

#ifndef IIS_H
#define IIS_H

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @defgroup iis iis function
 * @brief    iis function modules
 * @{
 */

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
uint8_t iis_init(uint32_t standard, uint32_t mode, uint32_t polarity, uint32_t format, uint32_t enable, uint32_t freq);

/**
 * @brief  iis bus deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t iis_deinit(void);

/**
 * @brief  iis bus stop
 * @return status code
 *         - 0 success
 *         - 1 stop failed
 * @note   none
 */
uint8_t iis_stop(void);

/**
 * @brief  iis bus pause
 * @return status code
 *         - 0 success
 *         - 1 pause failed
 * @note   none
 */
uint8_t iis_pause(void);

/**
 * @brief  iis bus resume
 * @return status code
 *         - 0 success
 *         - 1 resume failed
 * @note   none
 */
uint8_t iis_resume(void);

/**
 * @brief     set freq
 * @param[in] freq is the set freq
 * @return    status code
 *            - 0 success
 *            - 1 set failed
 *            - 2 can't find freq
 * @note      none
 */
uint8_t iis_set_freq(uint32_t freq);

/**
 * @brief     iis bus write
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t iis_write(uint16_t *buf, uint16_t len);

/**
 * @brief      iis bus read
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t iis_read(uint16_t *buf, uint16_t len);

/**
 * @brief  iis get handle
 * @return points to an iis handle
 * @note   none
 */
I2S_HandleTypeDef* iis_get_handle(void);

/**
 * @brief  iis get the tx dma handle
 * @return points to a tx dma handle
 * @note   none
 */
DMA_HandleTypeDef* iis_get_tx_dma_handle(void);

/**
 * @brief  iis get the rx dma handle
 * @return points to a rx dma handle
 * @note   none
 */
DMA_HandleTypeDef* iis_get_rx_dma_handle(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
