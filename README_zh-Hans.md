
[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WM8978

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/wm8978/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

WM8978是一款低功耗、高质量的立体声编解码器，专为多媒体电话、数码相机或数码摄像机等便携式应用而设计。该设备集成了立体声差分麦克风的前置放大器，并包括扬声器、耳机和差分或立体声线输出的驱动器。由于不需要单独的麦克风或耳机放大器，因此降低了对外部组件的要求。先进的片上数字信号处理包括5波段均衡器、用于麦克风或通过ADC输入的线路的混合信号自动电平控制，以及用于录制或播放的纯数字限幅器功能。ADC路径中提供了额外的数字滤波选项，以满足“风噪降低”等应用滤波的需要。WM8978数字音频接口可以作为主设备或从设备运行。内部PLL可以从常见的参考时钟频率（如12MHz和13MHz）生成CODEC所需的所有音频时钟。WM8978在2.5V至3.3V的模拟电源电压下工作，尽管数字核心可以在1.71V以下的电压下工作以节省电源。如果需要增加输出功率，扬声器输出和OUT3/4线输出可以从5V电源运行。芯片的各个部分也可以在软件控制下断电。

LibDriver WM8978是LibDriver推出的WM8978的全功能驱动，该驱动提供音频播放、音频录制等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example play](#example-play)
    - [example record](#example-record)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver WM8978的源文件。

/interface目录包含了LibDriver WM8978与平台无关的IIC, IIS总线模板。

/test目录包含了LibDriver WM8978驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver WM8978编程范例。

/doc目录包含了LibDriver WM8978离线文档。

/datasheet目录包含了WM8978数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC, IIS总线模板，完成指定平台的IIC, IIS总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example play

```C
#include "driver_wm8978_basic.h"

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

...
    
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

...
    
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
    
    ...
}

...
    
/* wav deinit */
(void)wav_deinit(wm8978_play_get_handle());

/* deinit */
(void)wm8978_basic_deinit();

return 0;
```

#### example record

```C
#include "driver_wm8978_basic.h"

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

...
    
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

...
    
/* set timeout */
timeout = time;

/* loop */
while (timeout != 0)
{
    wav_delay_ms(1000);
    timeout--;
    wav_debug_print("wav: record %d bytes time %d/%ds.\n", wm8978_record_get_handle()->pos, time - timeout, time);
    
    ...
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

...

/* wav deinit */
(void)wav_deinit(wm8978_record_get_handle());

/* deinit */
(void)wm8978_basic_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/wm8978/index.html](https://www.libdriver.com/docs/wm8978/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。