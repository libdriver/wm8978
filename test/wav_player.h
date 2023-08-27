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
 * @file      wav_player.h
 * @brief     wav player header file
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

#ifndef WAV_PLAYER_H
#define WAV_PLAYER_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup wav_simple_player wav simple player function
 * @brief    wav simple player modules
 * @ingroup  wm8978_driver
 * @{
 */

/**
 * @brief wav buffer size definition
 */
#ifndef WAV_BUFFER_SIZE
    #define WAV_BUFFER_SIZE  (1024 * 32)
#endif

/**
 * @brief wav status enumeration definition
 */
typedef enum
{
    WAV_STATUS_STOP = 0x00,        /**< stop status */
    WAV_STATUS_PLAY = 0x01,        /**< play status */
} wav_status_t;

/**
 * @brief wav header structure definition
 */
typedef struct wav_header_s
{
    char chunk_id[4];                /**< chunk id */
    uint32_t chunk_size;             /**< chunk size */
    char format[4];                  /**< format */
    char sub_chunk1_id[4];           /**< sub chunk1 id */
    uint32_t sub_chunk1_size;        /**< sub chunk1 size */
    uint16_t audio_format;           /**< audio format */
    uint16_t num_channel;            /**< num channel */
    uint32_t sample_rate;            /**< sample rate */
    uint32_t byte_rate;              /**< byte rate */
    uint16_t block_align;            /**< block align */
    uint16_t bit_per_sample;         /**< bit per sample */
    char sub_chunk2_id[4];           /**< sub chunk2 id */
    uint32_t sub_chunk2_size;        /**< sub chunk2 size */
} wav_header_t;

/**
 * @brief wav handle structure definition
 */
typedef struct wav_handle_s
{
    uint8_t (*iis_init)(uint32_t standard, uint32_t mode, uint32_t polarity, 
                        uint32_t format, uint32_t enable, uint32_t freq);            /**< point to an iis_init function address */
    uint8_t (*iis_deinit)(void);                                                     /**< point to an iis_deinit function address */
    uint8_t (*iis_stop)(void);                                                       /**< point to an iis_stop function address */
    uint8_t (*iis_pause)(void);                                                      /**< point to an iis_pause function address */
    uint8_t (*iis_resume)(void);                                                     /**< point to an iis_resume function address */
    uint8_t (*iis_set_freq)(uint32_t freq);                                          /**< point to an iis_set_freq function address */
    uint8_t (*iis_write)(uint16_t *buf, uint16_t len);                               /**< point to an iis_write function address */
    uint8_t (*iis_read)(uint16_t *buf, uint16_t len);                                /**< point to an iis_read function address */
    uint8_t (*audio_init)(uint8_t type, char *name, uint32_t *size);                 /**< point to an audio_init function address */
    uint8_t (*audio_deinit)(void);                                                   /**< point to an audio_deinit function address */
    uint8_t (*audio_read)(uint32_t addr, uint16_t size, uint8_t *buffer);            /**< point to an audio_read function address */
    uint8_t (*audio_write)(uint32_t addr, uint16_t size, uint8_t *buffer);           /**< point to an audio_write function address */
    void (*delay_ms)(uint32_t ms);                                                   /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                 /**< point to a debug_print function address */ 
    uint8_t inited;                                                                  /**< inited flag */
    uint8_t status;                                                                  /**< status */
    wav_header_t wav;                                                                /**< wav header */
    uint32_t size;                                                                   /**< audio size */
    uint32_t pos;                                                                    /**< buffer pos */
    uint8_t buf[WAV_BUFFER_SIZE];                                                    /**< buffer size */
} wav_handle_t;

/**
 * @brief     initialize wav_handle_t structure
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] STRUCTURE is wav_handle_t
 * @note      none
 */
#define WAV_LINK_INIT(HANDLE, STRUCTURE)      memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link audio_init function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to an audio_init function address
 * @note      none
 */
#define WAV_LINK_AUDIO_INIT(HANDLE, FUC)     (HANDLE)->audio_init = FUC

/**
 * @brief     link audio_deinit function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to an audio_deinit function address
 * @note      none
 */
#define WAV_LINK_AUDIO_DEINIT(HANDLE, FUC)   (HANDLE)->audio_deinit = FUC

/**
 * @brief     link audio_read function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to an audio_read function address
 * @note      none
 */
#define WAV_LINK_AUDIO_READ(HANDLE, FUC)     (HANDLE)->audio_read = FUC

/**
 * @brief     link audio_write function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to an audio_write function address
 * @note      none
 */
#define WAV_LINK_AUDIO_WRITE(HANDLE, FUC)    (HANDLE)->audio_write = FUC

/**
 * @brief     link iis_init function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to an iis_init function address
 * @note      none
 */
#define WAV_LINK_IIS_INIT(HANDLE, FUC)       (HANDLE)->iis_init = FUC

/**
 * @brief     link iis_deinit function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to an iis_deinit function address
 * @note      none
 */
#define WAV_LINK_IIS_DEINIT(HANDLE, FUC)     (HANDLE)->iis_deinit = FUC

/**
 * @brief     link iis_stop function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to an iis_stop function address
 * @note      none
 */
#define WAV_LINK_IIS_STOP(HANDLE, FUC)       (HANDLE)->iis_stop = FUC

/**
 * @brief     link iis_pause function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to an iis_pause function address
 * @note      none
 */
#define WAV_LINK_IIS_PAUSE(HANDLE, FUC)      (HANDLE)->iis_pause = FUC

/**
 * @brief     link iis_resume function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to an iis_resume function address
 * @note      none
 */
#define WAV_LINK_IIS_RESUME(HANDLE, FUC)     (HANDLE)->iis_resume = FUC

/**
 * @brief     link iis_set_freq function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to an iis_set_freq function address
 * @note      none
 */
#define WAV_LINK_IIS_SET_FREQ(HANDLE, FUC)   (HANDLE)->iis_set_freq = FUC

/**
 * @brief     link iis_write function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to an iis_write function address
 * @note      none
 */
#define WAV_LINK_IIS_WRITE(HANDLE, FUC)      (HANDLE)->iis_write = FUC

/**
 * @brief     link iis_read function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to an iis_write function address
 * @note      none
 */
#define WAV_LINK_IIS_READ(HANDLE, FUC)       (HANDLE)->iis_read = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define WAV_LINK_DELAY_MS(HANDLE, FUC)       (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a wav handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define WAV_LINK_DEBUG_PRINT(HANDLE, FUC)    (HANDLE)->debug_print = FUC

/**
 * @brief     initialize the wav
 * @param[in] *handle points to a wav handle structure
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t wav_init(wav_handle_t *handle);

/**
 * @brief     wav deinit
 * @param[in] *handle points to a wav handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wav_deinit(wav_handle_t *handle);

/**
 * @brief     initialize the wav player
 * @param[in] *handle points to a wav handle structure
 * @param[in] *path points to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 play failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 format is invalid
 * @note      none
 */
uint8_t wav_player_init(wav_handle_t *handle, char *path);

/**
 * @brief     wav player buffer fill
 * @param[in] *handle points to a wav handle structure
 * @param[in] index is the fill index
 * @return    status code
 *            - 0 success
 *            - 1 fill failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 not playing
 * @note      none
 */
uint8_t wav_player_buffer_fill(wav_handle_t *handle, uint8_t index);

/**
 * @brief     wav record file fill
 * @param[in] *handle points to a wav handle structure
 * @param[in] index is the fill index
 * @return    status code
 *            - 0 success
 *            - 1 fill failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 not recording
 * @note      none
 */
uint8_t wav_record_file_fill(wav_handle_t *handle, uint8_t index);

/**
 * @brief      wav get status
 * @param[in]  *handle points to a wav handle structure
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wav_player_get_status(wav_handle_t *handle, wav_status_t *status);

/**
 * @brief     wav player config
 * @param[in] *handle points to a wav handle structure
 * @param[in] standard is the iis standard
 * @param[in] mode is the iis mode
 * @param[in] polarity is the iis polarity
 * @param[in] format is the iis format
 * @param[in] enable is the mclk output
 * @param[in] freq is the set freq
 * @return    status code
 *            - 0 success
 *            - 1 config failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wav_player_config(wav_handle_t *handle, uint32_t standard, 
                          uint32_t mode, uint32_t polarity, 
                          uint32_t format, uint32_t enable, uint32_t freq);

/**
 * @brief     wav record start
 * @param[in] *handle points to a wav handle structure
 * @param[in] sample_rate is the sample rate
 * @param[in] *path points to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 start failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 be recording
 * @note      none
 */
uint8_t wav_record_start(wav_handle_t *handle, uint32_t sample_rate, char *path);

/**
 * @brief     wav record stop
 * @param[in] *handle points to a wav handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 not recording
 * @note      none
 */
uint8_t wav_record_stop(wav_handle_t *handle);

/**
 * @brief     wav player start
 * @param[in] *handle points to a wav handle structure
 * @return    status code
 *            - 0 success
 *            - 1 start failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 be playing
 * @note      none
 */
uint8_t wav_player_start(wav_handle_t *handle);

/**
 * @brief     wav player stop
 * @param[in] *handle points to a wav handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 not playing
 * @note      none
 */
uint8_t wav_player_stop(wav_handle_t *handle);

/**
 * @brief     wav player pause
 * @param[in] *handle points to a wav handle structure
 * @return    status code
 *            - 0 success
 *            - 1 pause failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 not playing
 * @note      none
 */
uint8_t wav_player_pause(wav_handle_t *handle);

/**
 * @brief     wav player resume
 * @param[in] *handle points to a wav handle structure
 * @return    status code
 *            - 0 success
 *            - 1 resume failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 be playing
 * @note      none
 */
uint8_t wav_player_resume(wav_handle_t *handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
