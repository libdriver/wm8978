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
 * @file      wav_player_interface.h
 * @brief     wav player interface header file
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

#ifndef WAV_PLAYER_INTERFACE_H
#define WAV_PLAYER_INTERFACE_H

#include "wav_player.h"
#include "iis.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief     interface audio init
 * @param[in] type is the open type, 0 is read and 1 is write.
 * @param[in] *name points to a name buffer
 * @param[in] *size points to a file size buffer
 * @return    status code
 *            - 0 success
 *            - 1 audio init failed
 * @note      none
 */
uint8_t wav_audio_init(uint8_t type, char *name, uint32_t *size);

/**
 * @brief  interface audio deinit
 * @return status code
 *         - 0 success
 *         - 1 audio deinit failed
 * @note   none
 */
uint8_t wav_audio_deinit(void);

/**
 * @brief      interface audio read
 * @param[in]  addr is the mp3 file address
 * @param[in]  size is the read size
 * @param[out] *buffer points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 audio read failed
 * @note       none
 */
uint8_t wav_audio_read(uint32_t addr, uint16_t size, uint8_t *buffer);

/**
 * @brief     interface audio write
 * @param[in] addr is the mp3 file address
 * @param[in] size is the write size
 * @param[in] *buffer points to a data buffer
 * @return    status code
 *            - 0 success
 *            - 1 audio write failed
 * @note      none
 */
uint8_t wav_audio_write(uint32_t addr, uint16_t size, uint8_t *buffer);

/**
 * @brief     interface iis bus init
 * @param[in] standard is the iis standard
 * @param[in] mode is the iis mode
 * @param[in] polarity is the iis polarity
 * @param[in] format is the iis format
 * @param[in] enable is the mclk output
 * @param[in] freq is the set freq
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t wav_iis_init(uint32_t standard, uint32_t mode, uint32_t polarity, uint32_t format, uint32_t enable, uint32_t freq);

/**
 * @brief  interface iis bus deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t wav_iis_deinit(void);

/**
 * @brief  interface iis bus stop
 * @return status code
 *         - 0 success
 *         - 1 stop failed
 * @note   none
 */
uint8_t wav_iis_stop(void);

/**
 * @brief  interface iis bus pause
 * @return status code
 *         - 0 success
 *         - 1 pause failed
 * @note   none
 */
uint8_t wav_iis_pause(void);

/**
 * @brief  interface iis bus resume
 * @return status code
 *         - 0 success
 *         - 1 resume failed
 * @note   none
 */
uint8_t wav_iis_resume(void);

/**
 * @brief     interface freq
 * @param[in] freq is the set freq
 * @return    status code
 *            - 0 success
 *            - 1 set failed
 *            - 2 can't find freq
 * @note      none
 */
uint8_t wav_iis_set_freq(uint32_t freq);

/**
 * @brief     interface iis bus write
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t wav_iis_write(uint16_t *buf, uint16_t len);

/**
 * @brief      interface iis bus read
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t wav_iis_read(uint16_t *buf, uint16_t len);

/**
 * @brief     interface delay ms
 * @param[in] ms
 * @note      none
 */
void wav_delay_ms(uint32_t ms);

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @note      none
 */
void wav_debug_print(const char *const fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
