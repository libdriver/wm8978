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
 * @file      wav_player.c
 * @brief     wav player source file
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
 
#include "wav_player.h"

/**
 * @brief     write wav header
 * @param[in] *handle points to a wav handle structure
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_wav_write_wav_header(wav_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[44];

    buf[0] = handle->wav.chunk_id[0];                                     /* R */
    buf[1] = handle->wav.chunk_id[1];                                     /* I */
    buf[2] = handle->wav.chunk_id[2];                                     /* F */
    buf[3] = handle->wav.chunk_id[3];                                     /* F */
    buf[4] = (handle->wav.chunk_size >> 0) & 0xFF;                        /* set chunk size */
    buf[5] = (handle->wav.chunk_size >> 8) & 0xFF;                        /* set chunk size */
    buf[6] = (handle->wav.chunk_size >> 16) & 0xFF;                       /* set chunk size */
    buf[7] = (handle->wav.chunk_size >> 24) & 0xFF;                       /* set chunk size */
    buf[8] = handle->wav.format[0];                                       /* W */
    buf[9] = handle->wav.format[1];                                       /* A */
    buf[10] = handle->wav.format[2];                                      /* V */
    buf[11] = handle->wav.format[3];                                      /* E */
    buf[12] = handle->wav.sub_chunk1_id[0];                               /* f */
    buf[13] = handle->wav.sub_chunk1_id[1];                               /* m */
    buf[14] = handle->wav.sub_chunk1_id[2];                               /* t */
    buf[15] = handle->wav.sub_chunk1_id[3];                               /* 0x00 */
    buf[16] = (handle->wav.sub_chunk1_size >> 0) & 0xFF;                  /* 16 bytes */
    buf[17] = (handle->wav.sub_chunk1_size >> 8) & 0xFF;                  /* 16 bytes */
    buf[18] = (handle->wav.sub_chunk1_size >> 16) & 0xFF;                 /* 16 bytes */
    buf[19] = (handle->wav.sub_chunk1_size >> 24) & 0xFF;                 /* 16 bytes */
    buf[20] = (handle->wav.audio_format >> 0) & 0xFF;                     /* pcm */
    buf[21] = (handle->wav.audio_format >> 8) & 0xFF;                     /* pcm */
    buf[22] = (handle->wav.num_channel >> 0) & 0xFF;                      /* 1 channel */
    buf[23] = (handle->wav.num_channel >> 8) & 0xFF;                      /* 1 channel */
    buf[24] = (handle->wav.sample_rate >> 0) & 0xFF;                      /* set sample rate */
    buf[25] = (handle->wav.sample_rate >> 8) & 0xFF;                      /* set sample rate */
    buf[26] = (handle->wav.sample_rate >> 16) & 0xFF;                     /* set sample rate */
    buf[27] = (handle->wav.sample_rate >> 24) & 0xFF;                     /* set sample rate */
    buf[28] = (handle->wav.byte_rate >> 0) & 0xFF;                        /* double */
    buf[29] = (handle->wav.byte_rate >> 8) & 0xFF;                        /* double */
    buf[30] = (handle->wav.byte_rate >> 16) & 0xFF;                       /* double */
    buf[31] = (handle->wav.byte_rate >> 24) & 0xFF;                       /* double */
    buf[32] = (handle->wav.block_align >> 0) & 0xFF;                      /* 2 bytes */
    buf[33] = (handle->wav.block_align >> 8) & 0xFF;                      /* 2 bytes */
    buf[34] = (handle->wav.bit_per_sample >> 0) & 0xFF;                   /* 16 bits */
    buf[35] = (handle->wav.bit_per_sample >> 8) & 0xFF;                   /* 16 bits */
    buf[36] = handle->wav.sub_chunk2_id[0];                               /* d */
    buf[37] = handle->wav.sub_chunk2_id[1];                               /* a */
    buf[38] = handle->wav.sub_chunk2_id[2];                               /* t */
    buf[39] = handle->wav.sub_chunk2_id[3];                               /* a */
    buf[40] = (handle->wav.sub_chunk2_size >> 0) & 0xFF;                  /* init 0 */
    buf[41] = (handle->wav.sub_chunk2_size >> 8) & 0xFF;                  /* init 0 */
    buf[42] = (handle->wav.sub_chunk2_size >> 16) & 0xFF;                 /* init 0 */
    buf[43] = (handle->wav.sub_chunk2_size >> 24) & 0xFF;                 /* init 0 */
    res = handle->audio_write(0, 44, buf);                                /* write buffer */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("wav: audio write failed.\n");                /* audio write failed */

        return 1;                                                         /* return error */
    }
    handle->pos += 44;                                                    /* add 44 offset */

    return 0;                                                             /* success return 0 */
}

/**
 * @brief     initialize the wav
 * @param[in] *handle points to a wav handle structure
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t wav_init(wav_handle_t *handle)
{
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->debug_print == NULL)                                /* check debug_print */
    {
        return 3;                                                   /* return error */
    }
    if (handle->iis_init == NULL)                                   /* check iis_init */
    {
        handle->debug_print("wav: iis_init is null.\n");            /* iis_init is null */
        
        return 3;                                                   /* return error */
    }
    if (handle->iis_deinit == NULL)                                 /* check iis_deinit */
    {
        handle->debug_print("wav: iis_deinit is null.\n");          /* iis_deinit is null */
        
        return 3;                                                   /* return error */
    }
    if (handle->iis_stop == NULL)                                   /* check iis_stop */
    {
        handle->debug_print("wav: iis_stop is null.\n");            /* iis_stop is null */
        
        return 3;                                                   /* return error */
    }
    if (handle->iis_pause == NULL)                                  /* check iis_pause */
    {
        handle->debug_print("wav: iis_pause is null.\n");           /* iis_pause is null */
        
        return 3;                                                   /* return error */
    }
    if (handle->iis_resume == NULL)                                 /* check iis_resume */
    {
        handle->debug_print("wav: iis_resume is null.\n");          /* iis_resume is null */
        
        return 3;                                                   /* return error */
    }
    if (handle->iis_set_freq == NULL)                               /* check iis_set_freq */
    {
        handle->debug_print("wav: iis_set_freq is null.\n");        /* iis_set_freq is null */
        
        return 3;                                                   /* return error */
    }
    if (handle->iis_write == NULL)                                  /* check iis_write */
    {
        handle->debug_print("wav: iis_write is null.\n");           /* iis_write is null */
        
        return 3;                                                   /* return error */
    }
    if (handle->iis_read == NULL)                                   /* check iis_read */
    {
        handle->debug_print("wav: iis_read is null.\n");            /* iis_read is null */
        
        return 3;                                                   /* return error */
    }
    if (handle->audio_init == NULL)                                 /* check audio_init */
    {
        handle->debug_print("wav: audio_init is null.\n");          /* audio_init is null */
        
        return 3;                                                   /* return error */
    }
    if (handle->audio_deinit == NULL)                               /* check audio_deinit */
    {
        handle->debug_print("wav: audio_deinit is null.\n");        /* audio_deinit is null */
        
        return 3;                                                   /* return error */
    }
    if (handle->audio_read == NULL)                                 /* check audio_read */
    {
        handle->debug_print("wav: audio_read is null.\n");          /* audio_read is null */
        
        return 3;                                                   /* return error */
    }
    if (handle->audio_write == NULL)                                /* check audio_write */
    {
        handle->debug_print("wav: audio_write is null.\n");         /* audio_write is null */
        
        return 3;                                                   /* return error */
    }
    if (handle->delay_ms == NULL)                                   /* check delay_ms */
    {
        handle->debug_print("wav: delay_ms is null.\n");            /* delay_ms is null */
        
        return 3;                                                   /* return error */
    }
    
    handle->inited = 1;                                             /* flag inited */
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t wav_deinit(wav_handle_t *handle)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    handle->inited = 0;             /* flag closed */
    
    return 0;                       /* success return 0 */
}

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
uint8_t wav_player_init(wav_handle_t *handle, char *path)
{
    uint8_t buf[72];
    
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }
    
    handle->pos = 0;                                            /* init 0 */
    if (handle->audio_init(0, path, &handle->size) != 0)        /* audio init */
    {
        handle->debug_print("wav: player failed.\n");           /* player failed */

        return 1;                                               /* return error */
    }
    if (handle->audio_read(handle->pos, 72, buf) != 0)          /* read header */
    {
        handle->debug_print("wav: read failed.\n");             /* read failed */

        return 1;                                               /* return error */
    }
    handle->wav.chunk_id[0] = buf[0];                           /* set chunk id 0 */
    handle->wav.chunk_id[1] = buf[1];                           /* set chunk id 1 */
    handle->wav.chunk_id[2] = buf[2];                           /* set chunk id 2 */
    handle->wav.chunk_id[3] = buf[3];                           /* set chunk id 3 */
    handle->wav.chunk_size = buf[4] | 
                             ((uint32_t)(buf[5]) << 8) |
                             ((uint32_t)(buf[6]) << 16) |
                             ((uint32_t)(buf[7]) << 24);        /* set chunk size */
    handle->wav.format[0] = buf[8];                             /* set format 0 */
    handle->wav.format[1] = buf[9];                             /* set format 1 */
    handle->wav.format[2] = buf[10];                            /* set format 2 */
    handle->wav.format[3] = buf[11];                            /* set format 3 */
    handle->wav.sub_chunk1_id[0] = buf[12];                     /* set sub chunk1 id 0 */
    handle->wav.sub_chunk1_id[1] = buf[13];                     /* set sub chunk1 id 1 */
    handle->wav.sub_chunk1_id[2] = buf[14];                     /* set sub chunk1 id 2 */
    handle->wav.sub_chunk1_id[3] = buf[15];                     /* set sub chunk1 id 3 */
    handle->wav.sub_chunk1_size = buf[16] | 
                                 ((uint32_t)(buf[17]) << 8) |
                                 ((uint32_t)(buf[18]) << 16) |
                                 ((uint32_t)(buf[19]) << 24);   /* set sub chunk1 size */
    handle->wav.audio_format = buf[20] | 
                               ((uint16_t)(buf[21]) << 8);      /* set audio format */
    handle->wav.num_channel = buf[22] | 
                               ((uint16_t)(buf[23]) << 8);      /* set num channel */
    handle->wav.sample_rate = buf[24] | 
                              ((uint32_t)(buf[25]) << 8) |
                              ((uint32_t)(buf[26]) << 16) |
                              ((uint32_t)(buf[27]) << 24);      /* set sample rate */
    handle->wav.byte_rate = buf[28] | 
                              ((uint32_t)(buf[29]) << 8) |
                              ((uint32_t)(buf[30]) << 16) |
                              ((uint32_t)(buf[31]) << 24);      /* set byte rate */
    handle->wav.block_align = buf[32] | 
                              ((uint16_t)(buf[33]) << 8);       /* set block align */
    handle->wav.bit_per_sample = buf[34] | 
                                 ((uint16_t)(buf[35]) << 8);    /* set bit per sample */
    if (buf[36] != 'd')
    {
        handle->wav.sub_chunk2_id[0] = buf[38];                 /* set sub chunk2 id 0 */
        handle->wav.sub_chunk2_id[1] = buf[39];                 /* set sub chunk2 id 1 */
        handle->wav.sub_chunk2_id[2] = buf[40];                 /* set sub chunk2 id 2 */
        handle->wav.sub_chunk2_id[3] = buf[41];                 /* set sub chunk2 id 3 */
        handle->wav.sub_chunk2_size = buf[42] | 
                               ((uint32_t)(buf[43]) << 8) |
                               ((uint32_t)(buf[44]) << 16) |
                               ((uint32_t)(buf[45]) << 24);     /* set sub chunk _size */
        handle->pos += 44;                                      /* add 44 offset */
    }
    else
    {
        handle->wav.sub_chunk2_id[0] = buf[36];                 /* set sub chunk2 id 0 */
        handle->wav.sub_chunk2_id[1] = buf[37];                 /* set sub chunk2 id 1 */
        handle->wav.sub_chunk2_id[2] = buf[38];                 /* set sub chunk2 id 2 */
        handle->wav.sub_chunk2_id[3] = buf[39];                 /* set sub chunk2 id 3 */
        handle->wav.sub_chunk2_size = buf[40] | 
                               ((uint32_t)(buf[41]) << 8) |
                               ((uint32_t)(buf[42]) << 16) |
                               ((uint32_t)(buf[43]) << 24);     /* set sub chunk _size */
        handle->pos += 44;                                      /* add 44 offset */
    }
    if (handle->wav.chunk_id[0] != 'R' ||
        handle->wav.chunk_id[1] != 'I' ||
        handle->wav.chunk_id[2] != 'F' ||
        handle->wav.chunk_id[3] != 'F')                         /* check chunk id */
    {
        handle->debug_print("wav: format is invalid.\n");       /* format is invalid */

        return 4;                                               /* return error */
    }
    if (handle->wav.format[0] != 'W' ||
        handle->wav.format[1] != 'A' ||
        handle->wav.format[2] != 'V' ||
        handle->wav.format[3] != 'E')                           /* check format */
    {
        handle->debug_print("wav: format is invalid.\n");       /* format is invalid */

        return 4;                                               /* return error */
    }
    if (handle->wav.sub_chunk1_id[0] != 'f' ||
        handle->wav.sub_chunk1_id[1] != 'm' ||
        handle->wav.sub_chunk1_id[2] != 't' ||
        handle->wav.sub_chunk1_id[3] != ' ')                    /* check sub chunk1 id */
    {
        handle->debug_print("wav: format is invalid.\n");       /* format is invalid */

        return 4;                                               /* return error */
    }
    if (handle->wav.sub_chunk2_id[0] != 'd' ||
        handle->wav.sub_chunk2_id[1] != 'a' ||
        handle->wav.sub_chunk2_id[2] != 't' ||
        handle->wav.sub_chunk2_id[3] != 'a')                    /* check sub chunk2 id */
    {
        handle->debug_print("wav: format is invalid.\n");       /* format is invalid */

        return 4;                                               /* return error */
    }
    
    return 0;                                                   /* success return 0 */
}

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
                          uint32_t format, uint32_t enable, uint32_t freq)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    if (handle->iis_set_freq(freq) != 0)                                        /* set freq */
    {
        handle->debug_print("wav: set freq failed.\n");                         /* set freq failed */

        return 1;                                                               /* return error */
    }
    if (handle->iis_init(standard, mode, polarity, format, enable, freq) != 0)  /* iis init */
    {
        handle->debug_print("wav: config failed.\n");                           /* config failed */

        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t wav_player_start(wav_handle_t *handle)
{
    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->inited != 1)                                                         /* check handle initialization */
    {
        return 3;                                                                    /* return error */
    }
    if (handle->status != 0)                                                         /* check status */
    {
        handle->debug_print("wav: be playing.\n");                                   /* be playing */

        return 4;                                                                    /* return error */
    }
    
    if (handle->audio_read(handle->pos, WAV_BUFFER_SIZE, handle->buf) != 0)          /* read data */
    {
        handle->debug_print("wav: read failed\n");                                   /* read failed */

        return 1;                                                                    /* return error */
    }
    if (handle->iis_write((uint16_t *)handle->buf, WAV_BUFFER_SIZE / 2) != 0)        /* write data */
    {
        handle->debug_print("wav: iis write failed\n");                              /* iis write failed */

        return 1;                                                                    /* return error */
    }
    handle->pos += WAV_BUFFER_SIZE;                                                  /* add pos */
    handle->status = 1;                                                              /* set status */
    
    return 0;                                                                        /* success return 0 */
}

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
uint8_t wav_record_start(wav_handle_t *handle, uint32_t sample_rate, char *path)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    if (handle->status != 0)                                           /* check status */
    {
        handle->debug_print("wav: be recording.\n");                   /* be recording */

        return 4;                                                      /* return error */
    }
    
    handle->pos = 0;                                                   /* init 0 */
    if (handle->audio_init(1, path, &handle->size) != 0)               /* audio init */
    {
        handle->debug_print("wav: record failed.\n");                  /* record failed */

        return 1;                                                      /* return error */
    }
    handle->wav.chunk_id[0] = 'R';                                     /* R */
    handle->wav.chunk_id[1] = 'I';                                     /* I */
    handle->wav.chunk_id[2] = 'F';                                     /* F */
    handle->wav.chunk_id[3] = 'F';                                     /* F */
    handle->wav.chunk_size = 0x00000000;                               /* init 0 */
    handle->wav.format[0] = 'W';                                       /* W */
    handle->wav.format[1] = 'A';                                       /* A */
    handle->wav.format[2] = 'V';                                       /* V */
    handle->wav.format[3] = 'E';                                       /* E */
    handle->wav.sub_chunk1_id[0] = 'f';                                /* f */
    handle->wav.sub_chunk1_id[1] = 'm';                                /* m */
    handle->wav.sub_chunk1_id[2] = 't';                                /* t */
    handle->wav.sub_chunk1_id[3] = 0x20;                               /* 0x20 */
    handle->wav.sub_chunk1_size = 16;                                  /* 16 bytes */
    handle->wav.audio_format = 0x01;                                   /* pcm */
    handle->wav.num_channel = 2;                                       /* 2 channel */
    handle->wav.sample_rate = sample_rate;                             /* set sample rate */
    handle->wav.byte_rate = handle->wav.sample_rate * 4;               /* 4 times */
    handle->wav.block_align = 4;                                       /* 4 bytes */
    handle->wav.bit_per_sample = 16;                                   /* 16 bits */
    handle->wav.sub_chunk2_id[0] = 'd';                                /* d */
    handle->wav.sub_chunk2_id[1] = 'a';                                /* a */
    handle->wav.sub_chunk2_id[2] = 't';                                /* t */
    handle->wav.sub_chunk2_id[3] = 'a';                                /* a */
    handle->wav.sub_chunk2_size = 0x00000000;                          /* init 0 */
    if (a_wav_write_wav_header(handle) != 0)                           /* write header */
    {
        handle->debug_print("wav: write header failed.\n");            /* write header failed */

        return 1;                                                      /* return error */
    }
    if (handle->iis_read((uint16_t *)handle->buf, 
                         WAV_BUFFER_SIZE / 2) != 0)                    /* read data */
    {
        handle->debug_print("wav: iis read failed\n");                 /* iis read failed */

        return 1;                                                      /* return error */
    }
    handle->status = 1;                                                /* set status */
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t wav_record_file_fill(wav_handle_t *handle, uint8_t index)
{
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    if (handle->status != 1)                                                             /* check status */
    {
        handle->debug_print("wav: not recording.\n");                                    /* not recording */

        return 4;                                                                        /* return error */
    }
    
    if (index != 0)                                                                      /* buffer 1 */
    {
        if (handle->audio_write(handle->pos, WAV_BUFFER_SIZE / 2, 
                                handle->buf + WAV_BUFFER_SIZE / 2) != 0)                 /* write data */
        {
            handle->debug_print("wav: write failed\n");                                  /* write failed */

            return 1;                                                                    /* return error */
        }
        handle->pos += WAV_BUFFER_SIZE / 2;                                              /* add pos */
    }
    else                                                                                 /* buffer 0 */
    {
        if (handle->audio_write(handle->pos, WAV_BUFFER_SIZE / 2, handle->buf) != 0)     /* write data */
        {
            handle->debug_print("wav: write failed\n");                                  /* write failed */

            return 1;                                                                    /* return error */
        }
        handle->pos += WAV_BUFFER_SIZE / 2;                                              /* add pos */
    }
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t wav_record_stop(wav_handle_t *handle)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    if (handle->status != 1)                                       /* check status */
    {
        handle->debug_print("wav: not recording.\n");              /* not recording */

        return 4;                                                  /* return error */
    }
    
    if (handle->iis_stop() != 0)                                   /* iis stop */
    {
        handle->debug_print("wav: iis stop failed.\n");            /* iis stop failed */

        return 1;                                                  /* return error */
    }
    handle->wav.chunk_size = handle->pos - 44 + 36;                /* set chunk size */
    handle->wav.sub_chunk2_size = handle->pos - 44;                /* set sub chunk2 size */
    if (a_wav_write_wav_header(handle) != 0)                       /* write header */
    {
        handle->debug_print("wav: write header failed.\n");        /* write header failed */

        return 1;                                                  /* return error */
    }
    if (handle->iis_deinit() != 0)                                 /* iis deinit */
    {
        handle->debug_print("wav: iis deinit failed.\n");          /* iis deinit failed */

        return 1;                                                  /* return error */
    }
    if (handle->audio_deinit() != 0)                               /* audio deinit */
    {
        handle->debug_print("wav: audio deinit failed.\n");        /* audio deinit failed */

        return 1;                                                  /* return error */
    }
    handle->status = 0;                                            /* stop */
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wav_player_stop(wav_handle_t *handle)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    if (handle->status != 1)                                       /* check status */
    {
        handle->debug_print("wav: not playing.\n");                /* not playing */

        return 4;                                                  /* return error */
    }
    
    if (handle->iis_stop() != 0)                                   /* iis stop */
    {
        handle->debug_print("wav: iis stop failed.\n");            /* iis stop failed */

        return 1;                                                  /* return error */
    }
    if (handle->iis_deinit() != 0)                                 /* iis deinit */
    {
        handle->debug_print("wav: iis deinit failed.\n");          /* iis deinit failed */

        return 1;                                                  /* return error */
    }
    if (handle->audio_deinit() != 0)                               /* audio deinit */
    {
        handle->debug_print("wav: audio deinit failed.\n");        /* audio deinit failed */

        return 1;                                                  /* return error */
    }
    handle->status = 0;                                            /* stop */
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wav_player_pause(wav_handle_t *handle)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    if (handle->status != 1)                                       /* check status */
    {
        handle->debug_print("wav: not playing.\n");                /* not playing */

        return 4;                                                  /* return error */
    }
    
    if (handle->iis_pause() != 0)                                  /* iis pause */
    {
        handle->debug_print("wav: iis pause failed.\n");           /* iis pause failed */

        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wav_player_resume(wav_handle_t *handle)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    if (handle->status != 0)                                       /* check status */
    {
        handle->debug_print("wav: be playing.\n");                 /* be playing */

        return 4;                                                  /* return error */
    }
    
    if (handle->iis_pause() != 0)                                  /* iis pause */
    {
        handle->debug_print("wav: iis pause failed.\n");           /* iis pause failed */

        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t wav_player_get_status(wav_handle_t *handle, wav_status_t *status)
{
    if (handle == NULL)                              /* check handle */
    {
        return 2;                                    /* return error */
    }
    if (handle->inited != 1)                         /* check handle initialization */
    {
        return 3;                                    /* return error */
    }
    
    *status = (wav_status_t)(handle->status);        /* get status */
    
    return 0;                                        /* success return 0 */
}

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
uint8_t wav_player_buffer_fill(wav_handle_t *handle, uint8_t index)
{
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    if (handle->status != 1)                                                             /* check status */
    {
        handle->debug_print("wav: not playing.\n");                                      /* not playing */

        return 4;                                                                        /* return error */
    }
    
    if (handle->pos > handle->size)                                                      /* check pos */
    {
        if (handle->iis_stop() != 0)                                                     /* iis stop */
        {
            handle->debug_print("wav: iis stop failed.\n");                              /* iis stop failed */

            return 1;                                                                    /* return error */
        }
        if (handle->audio_deinit() != 0)                                                 /* audio deinit */
        {
            handle->debug_print("wav: audio deinit failed.\n");                          /* audio deinit failed */

            return 1;                                                                    /* return error */
        }
        handle->status = 0;                                                              /* stop */
        handle->debug_print("wav: play end.\n");                                         /* play end */
        
        return 0;                                                                        /* success return 0 */
    }
    if (index != 0)                                                                      /* buffer 1 */
    {
        if (handle->audio_read(handle->pos, WAV_BUFFER_SIZE / 2, 
                               handle->buf + WAV_BUFFER_SIZE / 2) != 0)                  /* read data */
        {
            handle->debug_print("wav: read failed\n");                                   /* read failed */

            return 1;                                                                    /* return error */
        }
        handle->pos += WAV_BUFFER_SIZE / 2;                                              /* add pos */
        if (handle->pos > handle->size)                                                  /* if oversize */
        {
            uint32_t diff = handle->pos - handle->size;                                  /* get over part */
            
            memset(handle->buf + WAV_BUFFER_SIZE - diff, 0, diff);                       /* set all 0 */
        }
    }
    else                                                                                 /* buffer 0 */
    {
        if (handle->audio_read(handle->pos, WAV_BUFFER_SIZE / 2, handle->buf) != 0)      /* read data */
        {
            handle->debug_print("wav: read failed\n");                                   /* read failed */

            return 1;                                                                    /* return error */
        }
        handle->pos += WAV_BUFFER_SIZE / 2;                                              /* add pos */
        if (handle->pos > handle->size)                                                  /* if oversize */
        {
            uint32_t diff = handle->pos - handle->size;                                  /* get over part */
            
            memset(handle->buf + WAV_BUFFER_SIZE / 2 - diff, 0, diff);                   /* set all 0 */
        }
    }
    
    return 0;                                                                            /* success return 0 */
}
