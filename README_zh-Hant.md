[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WM8978

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/wm8978/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

WM8978是一款低功耗、高品質的身歷聲轉碼器，專為多媒體電話、數位相機或數碼攝像機等可擕式應用而設計。 該設備集成了身歷聲差分麥克風的前置放大器，並包括揚聲器、耳機和差分或身歷聲線輸出的驅動器。 由於不需要單獨的麥克風或耳機放大器，囙此降低了對外部組件的要求。 先進的片上數位信號處理包括5波段等化器、用於麥克風或通過ADC輸入的線路的混合訊號自動電平控制，以及用於錄製或播放的純數位限幅器功能。 ADC路徑中提供了額外的數位濾波選項，以滿足“風噪降低”等應用濾波的需要。 WM8978數位音訊介面可以作為主設備或從設備運行。 內部PLL可以從常見的參攷時鐘頻率（如12MHz和13MHz）生成CODEC所需的所有音訊時鐘。 WM8978在2.5V至3.3V的類比電源電壓下工作，儘管數位覈心可以在1.71V以下的電壓下工作以節省電源。 如果需要新增輸出功率，揚聲器輸出和OUT3/4線輸出可以從5V電源運行。 晶片的各個部分也可以在軟件控制下斷電。

LibDriver WM8978是LibDriver推出的WM8978的全功能驅動，該驅動提供音訊播放、音訊錄製等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example play](#example-play)
    - [example record](#example-record)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver WM8978的源文件。

/interface目錄包含了LibDriver WM8978與平台無關的IIC, IIS總線模板。

/test目錄包含了LibDriver WM8978驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver WM8978編程範例。

/doc目錄包含了LibDriver WM8978離線文檔。

/datasheet目錄包含了WM8978數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC, IIS總線模板，完成指定平台的IIC, IIS總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/wm8978/index.html](https://www.libdriver.com/docs/wm8978/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。