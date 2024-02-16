[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WM8978

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/wm8978/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

WM8978 は、マルチメディア電話、デジタル スチル カメラ、デジタル ビデオカメラなどのポータブル アプリケーション向けに設計された低電力、高品質のステレオ コーデックです。このデバイスには、ステレオ差動マイク用のプリアンプが統合されており、スピーカー、ヘッドフォン、および差動またはステレオ ライン出力用のドライバが含まれています。 個別のマイクやヘッドフォンアンプが必要ないため、外部コンポーネントの要件が軽減されます。高度なオンチップデジタル信号処理には、5バンドイコライザー、ADCを介したマイクまたはライン入力の混合信号自動レベル制御、および純粋なデジタル信号が含まれます。 録音または再生時のリミッター機能。 追加のデジタル フィルタリング オプションは、「風ノイズ低減」などのアプリケーション フィルタリングに対応するために、ADC パスで利用できます。WM8978 デジタル オーディオ インターフェイスは、マスターまたはスレーブとして動作できます。 内部 PLL は、12MHz や 13MHz などの一般的な基準クロック周波数から CODEC に必要なすべてのオーディオ クロックを生成できます。WM8978 は 2.5V ～ 3.3V のアナログ電源電圧で動作しますが、デジタル コアは 1.71V までの電圧で動作できます。 電力を節約するために。 出力電力の増加が必要な場合、スピーカー出力と OUT3/4 ライン出力は 5V 電源で動作できます。 チップの個々のセクションは、ソフトウェア制御の下でパワーダウンすることもできます。

LibDriver WM8978 は、LibDriver によって起動される WM8978 の全機能ドライバーです。オーディオ再生、オーディオ録音、その他の機能を提供します。 LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example play](#example-play)
    - [example record](#example-record)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver WM8978のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver WM8978用のプラットフォームに依存しないIIC, IISバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver WM8978ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver WM8978プログラミング例が含まれています。

/ docディレクトリには、LibDriver WM8978オフラインドキュメントが含まれています。

/ datasheetディレクトリには、WM8978データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIIC, IISバステンプレートを参照して、指定したプラットフォームのIIC, IISバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

```c
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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/wm8978/index.html](https://www.libdriver.com/docs/wm8978/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。