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
 * @file      main.c
 * @brief     main source file
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

#include "driver_wm8978_play_test.h"
#include "driver_wm8978_record_test.h"
#include "driver_wm8978_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                        /**< uart buffer */
uint16_t volatile g_len;                   /**< uart buffer length */

/**
 * @brief     iis tx half complete callback
 * @param[in] *hi2s points to an iis handle
 * @note      none
 */
void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
    wm8978_play_buffer_fill(0);
}

/**
 * @brief     iis tx complete callback
 * @param[in] *hi2s points to an iis handle
 * @note      none
 */
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    wm8978_play_buffer_fill(1);
}

/**
 * @brief     iis ex tx half complete callback
 * @param[in] *hi2s points to an iis handle
 * @note      none
 */
void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
    wm8978_record_file_fill(0);
}

/**
 * @brief     iis ex tx complete callback
 * @param[in] *hi2s points to an iis handle
 * @note      none
 */
void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    wm8978_record_file_fill(1);
}

/**
 * @brief     wm8978 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t wm8978(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"file", required_argument, NULL, 1},
        {"volume", required_argument, NULL, 2},
        {"time", required_argument, NULL, 3},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    char path[73]= "test.wav";
    float volume = -10.0f;
    uint32_t time = 60;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* file path */
            case 1 :
            {
                uint16_t i, len;
                
                /* set the file path */
                memset(path, 0, sizeof(char) * 73);
                strncpy(path, optarg, 72);
                
                /* replace the - */
                len = (uint16_t)strlen(path);
                for (i = 0; i < len; i++)
                {
                    if (path[i] == '-')
                    {
                        path[i] = ' ';
                    }
                }
                
                break;
            }
            
            /* volume */
            case 2 :
            {
                /* convert the volume */
                volume = atof(optarg);
                
                break;
            }
            
            /* time */
            case 3 :
            {
                /* convert the time */
                time = atol(optarg);
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_play", type) == 0)
    {
        if (wm8978_play_test(path) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_record", type) == 0)
    {
        if (wm8978_record_test(path, time) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_play", type) == 0)
    {
        uint8_t res;
        wm8978_companding_t companding = WM8978_COMPANDING_LINEAR;
        wm8978_channel_t channel = WM8978_CHANNEL_STEREO;
        wm8978_word_length_t length = WM8978_WORD_LENGTH_16_BITS;
        
        /* link interface function */
        WAV_LINK_INIT(wm8978_play_get_handle(), wav_handle_t);
        WAV_LINK_AUDIO_INIT(wm8978_play_get_handle(), wav_audio_init);
        WAV_LINK_AUDIO_DEINIT(wm8978_play_get_handle(), wav_audio_deinit);
        WAV_LINK_AUDIO_READ(wm8978_play_get_handle(), wav_audio_read);
        WAV_LINK_AUDIO_WRITE(wm8978_play_get_handle(), wav_audio_write);
        WAV_LINK_IIS_INIT(wm8978_play_get_handle(), wav_iis_init);
        WAV_LINK_IIS_DEINIT(wm8978_play_get_handle(), wav_iis_deinit);
        WAV_LINK_IIS_STOP(wm8978_play_get_handle(), wav_iis_stop);
        WAV_LINK_IIS_PAUSE(wm8978_play_get_handle(), wav_iis_pause);
        WAV_LINK_IIS_RESUME(wm8978_play_get_handle(), wav_iis_resume);
        WAV_LINK_IIS_SET_FREQ(wm8978_play_get_handle(), wav_iis_set_freq);
        WAV_LINK_IIS_WRITE(wm8978_play_get_handle(), wav_iis_write);
        WAV_LINK_IIS_READ(wm8978_play_get_handle(), wav_iis_read);
        WAV_LINK_DELAY_MS(wm8978_play_get_handle(), wav_delay_ms);
        WAV_LINK_DEBUG_PRINT(wm8978_play_get_handle(), wav_debug_print);
        
        /* start play */
        wm8978_interface_debug_print("wm8978: start play.\n");
        
        /* wm8978 basic init */
        res = wm8978_basic_init(WM8978_BASIC_MODE_PLAY);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: basic init failed.\n");
            
            return 1;
        }
        
        /* wav init */
        res = wav_init(wm8978_play_get_handle());
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: wav init failed.\n");
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* wav player init */
        res = wav_player_init(wm8978_play_get_handle(), path);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: wav player init failed.\n");
            (void)wav_deinit(wm8978_play_get_handle());
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* set num channel */
        if (wm8978_play_get_handle()->wav.num_channel == 1)
        {
            channel = WM8978_CHANNEL_MONO;
        }
        else if (wm8978_play_get_handle()->wav.num_channel == 2)
        {
            channel = WM8978_CHANNEL_STEREO;
        }
        else
        {
            wm8978_interface_debug_print("wm8978: num channel is invalid.\n");
            (void)wav_deinit(wm8978_play_get_handle());
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* set bit per sample */
        if (wm8978_play_get_handle()->wav.bit_per_sample == 16)
        {
            length = WM8978_WORD_LENGTH_16_BITS;
        }
        else if (wm8978_play_get_handle()->wav.bit_per_sample == 24)
        {
            length = WM8978_WORD_LENGTH_24_BITS;
        }
        else
        {
            wm8978_interface_debug_print("wm8978: bit per sample is invalid.\n");
            (void)wav_deinit(wm8978_play_get_handle());
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* set audio format */
        if (wm8978_play_get_handle()->wav.audio_format == 1)
        {
            companding = WM8978_COMPANDING_LINEAR;
        }
        else
        {
            wm8978_interface_debug_print("wm8978: audio format is invalid.\n");
            (void)wav_deinit(wm8978_play_get_handle());
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* wm8978 config */
        if (wm8978_basic_config(companding, channel, length) != 0)
        {
            wm8978_interface_debug_print("wm8978: basic config failed.\n");
            (void)wav_deinit(wm8978_play_get_handle());
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* wav player config */
        res = wav_player_config(wm8978_play_get_handle(), I2S_STANDARD_PHILIPS, 
                                I2S_MODE_MASTER_TX, I2S_CPOL_LOW, 
                                I2S_DATAFORMAT_16B_EXTENDED, I2S_MCLKOUTPUT_ENABLE, wm8978_play_get_handle()->wav.sample_rate);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: wav player config failed.\n");
            (void)wav_deinit(wm8978_play_get_handle());
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* wav player start */
        res = wav_player_start(wm8978_play_get_handle());
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: wav player start failed.\n");
            (void)wav_deinit(wm8978_play_get_handle());
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* loop */
        while (1)
        {
            wav_status_t status;
            
            /* get status */
            res = wav_player_get_status(wm8978_play_get_handle(), &status);
            if (res != 0)
            {
                wm8978_interface_debug_print("wm8978: wav player get status failed.\n");
                (void)wav_player_stop(wm8978_play_get_handle());
                (void)wav_deinit(wm8978_play_get_handle());
                (void)wm8978_basic_deinit();
                
                return 1;
            }
            
            /* check status */
            if (status == WAV_STATUS_STOP)
            {
                break;
            }
            
            wav_delay_ms(1000);
            wav_debug_print("wav: playing %d/%d.\n", wm8978_play_get_handle()->pos, wm8978_play_get_handle()->size);
            
            /* read uart */
            g_len = uart_read(g_buf, 256);
            if (g_len != 0)
            {
                /* run shell */
                res = shell_parse((char *)g_buf, g_len);
                if (res == 0)
                {
                    /* run success */
                }
                else if (res == 1)
                {
                    uart_print("wm8978: run failed.\n");
                }
                else if (res == 2)
                {
                    uart_print("wm8978: unknown command.\n");
                }
                else if (res == 3)
                {
                    uart_print("wm8978: length is too long.\n");
                }
                else if (res == 4)
                {
                    uart_print("wm8978: pretreat failed.\n");
                }
                else if (res == 5)
                {
                    uart_print("wm8978: param is invalid.\n");
                }
                else
                {
                    uart_print("wm8978: unknown status code.\n");
                }
                uart_flush();
            }
        }
        
        /* finish play */
        wm8978_interface_debug_print("wm8978: finish play.\n");
        
        /* wav deinit */
        (void)wav_deinit(wm8978_play_get_handle());
        
        /* deinit */
        (void)wm8978_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_record", type) == 0)
    {
        uint8_t res;
        uint32_t timeout;
        wm8978_companding_t companding = WM8978_COMPANDING_LINEAR;
        wm8978_channel_t channel = WM8978_CHANNEL_STEREO;
        wm8978_word_length_t length = WM8978_WORD_LENGTH_16_BITS;
        
        /* link interface function */
        WAV_LINK_INIT(wm8978_record_get_handle(), wav_handle_t);
        WAV_LINK_AUDIO_INIT(wm8978_record_get_handle(), wav_audio_init);
        WAV_LINK_AUDIO_DEINIT(wm8978_record_get_handle(), wav_audio_deinit);
        WAV_LINK_AUDIO_READ(wm8978_record_get_handle(), wav_audio_read);
        WAV_LINK_AUDIO_WRITE(wm8978_record_get_handle(), wav_audio_write);
        WAV_LINK_IIS_INIT(wm8978_record_get_handle(), wav_iis_init);
        WAV_LINK_IIS_DEINIT(wm8978_record_get_handle(), wav_iis_deinit);
        WAV_LINK_IIS_STOP(wm8978_record_get_handle(), wav_iis_stop);
        WAV_LINK_IIS_PAUSE(wm8978_record_get_handle(), wav_iis_pause);
        WAV_LINK_IIS_RESUME(wm8978_record_get_handle(), wav_iis_resume);
        WAV_LINK_IIS_SET_FREQ(wm8978_record_get_handle(), wav_iis_set_freq);
        WAV_LINK_IIS_WRITE(wm8978_record_get_handle(), wav_iis_write);
        WAV_LINK_IIS_READ(wm8978_record_get_handle(), wav_iis_read);
        WAV_LINK_DELAY_MS(wm8978_record_get_handle(), wav_delay_ms);
        WAV_LINK_DEBUG_PRINT(wm8978_record_get_handle(), wav_debug_print);
        
        /* start record test */
        wm8978_interface_debug_print("wm8978: start record test.\n");
        
        /* wm8978 init */
        res = wm8978_basic_init(WM8978_BASIC_MODE_RECORD);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: basic init failed.\n");
            
            return 1;
        }
        
        /* wav init */
        res = wav_init(wm8978_record_get_handle());
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: wav init failed.\n");
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* config */
        res = wm8978_basic_config(companding, channel, length);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: wav config failed.\n");
            (void)wav_deinit(wm8978_record_get_handle());
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* wav player config */
        res = wav_player_config(wm8978_record_get_handle(), I2S_STANDARD_PHILIPS, 
                                I2S_MODE_MASTER_TX, I2S_CPOL_LOW, 
                                I2S_DATAFORMAT_16B, I2S_MCLKOUTPUT_ENABLE, 22050);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: wav record config failed.\n");
            (void)wav_deinit(wm8978_record_get_handle());
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* record start */
        res = wav_record_start(wm8978_record_get_handle(), 22050, path);
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: wav record start failed.\n");
            (void)wav_deinit(wm8978_record_get_handle());
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* set timeout */
        timeout = time;
        
        /* loop */
        while (timeout != 0)
        {
            wav_delay_ms(1000);
            timeout--;
            wav_debug_print("wav: record %d bytes time %d/%ds.\n", wm8978_record_get_handle()->pos, time - timeout, time);
            
            /* read uart */
            g_len = uart_read(g_buf, 256);
            if (g_len != 0)
            {
                /* run shell */
                res = shell_parse((char *)g_buf, g_len);
                if (res == 0)
                {
                    /* run success */
                }
                else if (res == 1)
                {
                    uart_print("wm8978: run failed.\n");
                }
                else if (res == 2)
                {
                    uart_print("wm8978: unknown command.\n");
                }
                else if (res == 3)
                {
                    uart_print("wm8978: length is too long.\n");
                }
                else if (res == 4)
                {
                    uart_print("wm8978: pretreat failed.\n");
                }
                else if (res == 5)
                {
                    uart_print("wm8978: param is invalid.\n");
                }
                else
                {
                    uart_print("wm8978: unknown status code.\n");
                }
                uart_flush();
            }
        }
        
        /* record stop */
        res = wav_record_stop(wm8978_record_get_handle());
        if (res != 0)
        {
            wm8978_interface_debug_print("wm8978: wav record stop failed.\n");
            (void)wav_deinit(wm8978_record_get_handle());
            (void)wm8978_basic_deinit();
            
            return 1;
        }
        
        /* finish record */
        wm8978_interface_debug_print("wm8978: finish record.\n");
        
        /* wav deinit */
        (void)wav_deinit(wm8978_record_get_handle());
        
        /* deinit */
        (void)wm8978_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_volume", type) == 0)
    {
        /* set volume */
        if (wm8978_basic_set_dac_volume(volume) != 0)
        {
            return 1;
        }
        
        /* output */
        wm8978_interface_debug_print("wm8978: set volume %0.1fdb.\n", volume);
        
        return 0;
    }
    else if (strcmp("e_microphone", type) == 0)
    {
        /* set volume */
        if (wm8978_basic_set_adc_volume(volume) != 0)
        {
            return 1;
        }
        
        /* output */
        wm8978_interface_debug_print("wm8978: set microphone %0.1fdb.\n", volume);
        
        return 0;
    }
    else if (strcmp("e_mute", type) == 0)
    {
        /* set dac mute */
        if (wm8978_basic_set_dac_mute() != 0)
        {
            return 1;
        }
        
        /* output */
        wm8978_interface_debug_print("wm8978: mute.\n");
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        wm8978_interface_debug_print("Usage:\n");
        wm8978_interface_debug_print("  wm8978 (-i | --information)\n");
        wm8978_interface_debug_print("  wm8978 (-h | --help)\n");
        wm8978_interface_debug_print("  wm8978 (-p | --port)\n");
        wm8978_interface_debug_print("  wm8978 (-t play | --test=play) [--file=<path>]\n");
        wm8978_interface_debug_print("  wm8978 (-t record | --test=record) [--file=<path>] [--time=<second>]\n");
        wm8978_interface_debug_print("  wm8978 (-e play | --example=play) [--file=<path>]\n");
        wm8978_interface_debug_print("  wm8978 (-e record | --example=record) [--file=<path>] [--time=<second>]\n");
        wm8978_interface_debug_print("  wm8978 (-e volume | --example=volume) [--volume=<vol>]\n");
        wm8978_interface_debug_print("  wm8978 (-e microphone | --example=microphone) [--volume=<vol>]\n");
        wm8978_interface_debug_print("  wm8978 (-e mute | --example=mute)\n");
        wm8978_interface_debug_print("\n");
        wm8978_interface_debug_print("Options:\n");
        wm8978_interface_debug_print("  -e <play | record | volume | microphone | mute>, --example=<play | record | volume | microphone | mute>\n");
        wm8978_interface_debug_print("                          Run the driver example.\n");
        wm8978_interface_debug_print("      --file=<path>       Set the wav file path.([default: test.wav])\n");
        wm8978_interface_debug_print("  -h, --help              Show the help.\n");
        wm8978_interface_debug_print("  -i, --information       Show the chip information.\n");
        wm8978_interface_debug_print("      --volume=<vol>      Set the volume.([default: -10.0])\n");
        wm8978_interface_debug_print("  -p, --port              Display the pin connections of the current board.\n");
        wm8978_interface_debug_print("  -t <play | record>, --test=<play | record>\n");
        wm8978_interface_debug_print("                          Run the driver test.\n");
        wm8978_interface_debug_print("      --time=<second>     Set the record time.([default: 60]).\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        wm8978_info_t info;
        
        /* print wm8978 info */
        wm8978_info(&info);
        wm8978_interface_debug_print("wm8978: chip is %s.\n", info.chip_name);
        wm8978_interface_debug_print("wm8978: manufacturer is %s.\n", info.manufacturer_name);
        wm8978_interface_debug_print("wm8978: interface is %s.\n", info.interface);
        wm8978_interface_debug_print("wm8978: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        wm8978_interface_debug_print("wm8978: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        wm8978_interface_debug_print("wm8978: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        wm8978_interface_debug_print("wm8978: max current is %0.2fmA.\n", info.max_current_ma);
        wm8978_interface_debug_print("wm8978: max temperature is %0.1fC.\n", info.temperature_max);
        wm8978_interface_debug_print("wm8978: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        wm8978_interface_debug_print("wm8978: SCK connected to GPIOB PIN13.\n");
        wm8978_interface_debug_print("wm8978: LRCK connected to GPIOB PIN12.\n");
        wm8978_interface_debug_print("wm8978: SDOUT connected to GPIOC PIN2.\n");
        wm8978_interface_debug_print("wm8978: SDIN connected to GPIOC PIN3.\n");
        wm8978_interface_debug_print("wm8978: MCLK connected to GPIOC PIN6.\n");
        wm8978_interface_debug_print("wm8978: SCL connected to GPIOB PIN8.\n");
        wm8978_interface_debug_print("wm8978: SDA connected to GPIOB PIN9.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register wm8978 function */
    shell_init();
    shell_register("wm8978", wm8978);
    uart_print("wm8978: welcome to libdriver wm8978.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("wm8978: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("wm8978: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("wm8978: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("wm8978: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("wm8978: param is invalid.\n");
            }
            else
            {
                uart_print("wm8978: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
