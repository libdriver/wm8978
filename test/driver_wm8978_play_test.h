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
 * @file      driver_wm8978_play_test.h
 * @brief     driver wm8978 play test header file
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

#ifndef DRIVER_WM8978_PLAY_TEST_H
#define DRIVER_WM8978_PLAY_TEST_H

#include "wav_player_interface.h"
#include "driver_wm8978_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup wm8978_test_driver wm8978 test driver function
 * @brief    wm8978 test driver modules
 * @ingroup  wm8978_driver
 * @{
 */

/**
 * @brief     play buffer fill
 * @param[in] index buffer index
 * @return    status code
 *            - 0 success
 *            - 1 fill failed
 * @note      none
 */
uint8_t wm8978_play_buffer_fill(uint8_t index);

/**
 * @brief     play test
 * @param[in] *path pointer to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t wm8978_play_test(char *path);

/**
 * @brief  play get handle
 * @return pointer to a wav handle
 * @note   none
 */
wav_handle_t *wm8978_play_get_handle(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
