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
 * @file      stm32f407_wav_player_interface.c
 * @brief     stm32f407 wav player interface source file
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
 
#include "wav_player_interface.h"
#include "ff.h"
#include "delay.h"
#include "uart.h"
#include <stdarg.h>

/**
 * @brief fs var definition
 */
FATFS g_fs;        /**< fatfs handle */
FIL g_file;        /**< fs handle */

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
uint8_t wav_audio_init(uint8_t type, char *name, uint32_t *size)
{
    FRESULT res;
    
    res = f_mount(&g_fs, "0:", 1);
    if (res != FR_OK)
    {
        return 1;
    }
    if (type == 0)
    {
        res = f_open(&g_file, name, FA_READ);
        if (res != FR_OK)
        {
            return 1;
        }
    }
    else
    {
        res = f_open(&g_file, name, FA_WRITE | FA_CREATE_ALWAYS);
        if (res != FR_OK)
        {
            return 1;
        }
    }
    *size = f_size(&g_file);
    
    return 0;
}

/**
 * @brief  interface audio deinit
 * @return status code
 *         - 0 success
 *         - 1 audio deinit failed
 * @note   none
 */
uint8_t wav_audio_deinit(void)
{
    FRESULT res;
    
    res = f_close(&g_file);
    if (res != FR_OK)
    {
        return 1;
    }
    res = f_unmount("0:");
    if (res != FR_OK)
    {
        return 1;
    }
    
    return 0;
}

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
uint8_t wav_audio_read(uint32_t addr, uint16_t size, uint8_t *buffer)
{
    FRESULT res;
    UINT bw;
    
    res = f_lseek(&g_file, addr);
    if (res != FR_OK)
    {
        return 1;
    }
    res = f_read(&g_file, buffer, size, &bw);
    if (res != FR_OK)
    {
        return 1;
    }
    
    return 0;
}

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
uint8_t wav_audio_write(uint32_t addr, uint16_t size, uint8_t *buffer)
{
    FRESULT res;
    UINT bw;
    
    res = f_lseek(&g_file, addr);
    if (res != FR_OK)
    {
        return 1;
    }
    res = f_write(&g_file, buffer, size, &bw);
    if (res != FR_OK)
    {
        return 1;
    }
    
    return 0;
}

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
 * @note      SCLK is PB13, LRCK is PB12, SDOUT is PC2, SDIN is PC3 and MCLK is PC6
 *            standard can be I2S_STANDARD_PHILIPS, I2S_STANDARD_MSB, I2S_STANDARD_LSB, I2S_STANDARD_PCM_SHORT, I2S_STANDARD_PCM_LONG
 *            mode can be I2S_MODE_SLAVE_TX, I2S_MODE_SLAVE_RX, I2S_MODE_MASTER_TX, I2S_MODE_MASTER_RX
 *            polarity can be I2S_CPOL_LOW, I2S_CPOL_HIGH
 *            format can be I2S_DATAFORMAT_16B, I2S_DATAFORMAT_16B_EXTENDED, I2S_DATAFORMAT_24B, I2S_DATAFORMAT_32B
 *            enable can be I2S_MCLKOUTPUT_ENABLE, I2S_MCLKOUTPUT_DISABLE
 */
uint8_t wav_iis_init(uint32_t standard, uint32_t mode, uint32_t polarity, uint32_t format, uint32_t enable, uint32_t freq)
{
    return iis_init(standard, mode, polarity, format, enable, freq);
}

/**
 * @brief  interface iis bus deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t wav_iis_deinit(void)
{
    return iis_deinit();
}

/**
 * @brief  interface iis bus stop
 * @return status code
 *         - 0 success
 *         - 1 stop failed
 * @note   none
 */
uint8_t wav_iis_stop(void)
{
    return iis_stop();
}

/**
 * @brief  interface iis bus pause
 * @return status code
 *         - 0 success
 *         - 1 pause failed
 * @note   none
 */
uint8_t wav_iis_pause(void)
{
    return iis_pause();
}

/**
 * @brief  interface iis bus resume
 * @return status code
 *         - 0 success
 *         - 1 resume failed
 * @note   none
 */
uint8_t wav_iis_resume(void)
{
    return iis_resume();
}

/**
 * @brief     interface freq
 * @param[in] freq is the set freq
 * @return    status code
 *            - 0 success
 *            - 1 set failed
 *            - 2 can't find freq
 * @note      none
 */
uint8_t wav_iis_set_freq(uint32_t freq)
{
    return iis_set_freq(freq);
}

/**
 * @brief     interface iis bus write
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t wav_iis_write(uint16_t *buf, uint16_t len)
{
    return iis_write(buf, len);
}

/**
 * @brief      interface iis bus read
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t wav_iis_read(uint16_t *buf, uint16_t len)
{
    return iis_read(buf, len);
}

/**
 * @brief     interface delay ms
 * @param[in] ms
 * @note      none
 */
void wav_delay_ms(uint32_t ms)
{
    delay_ms(ms);
}

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @note      none
 */
void wav_debug_print(const char *const fmt, ...)
{
    char str[256];
    uint16_t len;
    va_list args;
    
    memset((char *)str, 0, sizeof(char) * 256); 
    va_start(args, fmt);
    vsnprintf((char *)str, 255, (char const *)fmt, args);
    va_end(args);
    
    len = strlen((char *)str);
    (void)uart_write((uint8_t *)str, len);
}
