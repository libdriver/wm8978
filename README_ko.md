[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WM8978

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/wm8978/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

WM8978은 멀티미디어 전화, 디지털 스틸 카메라 또는 디지털 캠코더와 같은 휴대용 애플리케이션용으로 설계된 저전력 고품질 스테레오 코덱입니다. 이 장치에는 스테레오 차동 마이크용 프리앰프가 통합되어 있으며 스피커, 헤드폰 및 차동 또는 스테레오 라인 출력용 드라이버가 포함되어 있습니다. 별도의 마이크 또는 헤드폰 증폭기가 필요하지 않으므로 외부 구성 요소 요구 사항이 줄어듭니다. 고급 온칩 디지털 신호 처리에는 5밴드 이퀄라이저, ADC를 통한 마이크 또는 라인 입력을 위한 혼합 신호 자동 레벨 제어 및 순수 디지털 신호가 포함됩니다. 녹음이나 재생을 위한 리미터 기능. '바람 소음 감소'와 같은 애플리케이션 필터링을 제공하기 위해 ADC 경로에서 추가 디지털 필터링 옵션을 사용할 수 있습니다. WM8978 디지털 오디오 인터페이스는 마스터 또는 슬레이브로 작동할 수 있습니다. 내부 PLL은 12MHz 및 13MHz와 같은 공통 기준 클록 주파수에서 CODEC에 필요한 모든 오디오 클록을 생성할 수 있습니다. WM8978은 2.5~3.3V의 아날로그 공급 전압에서 작동하지만 디지털 코어는 최저 1.71V의 전압에서 작동할 수 있습니다. 전력을 절약하기 위해. 증가된 출력 전력이 필요한 경우 스피커 출력 및 OUT3/4 라인 출력은 5V 공급 장치에서 실행될 수 있습니다. 칩의 개별 섹션은 소프트웨어 제어에 따라 전원을 끌 수도 있습니다.

LibDriver WM8978은 LibDriver가 출시한 WM8978의 전체 기능 드라이버입니다. 오디오 재생, 오디오 녹음 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example play](#example-play)
    - [example record](#example-record)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver WM8978의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver WM8978용 플랫폼 독립적인 IIC, IIS버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver WM8978드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver WM8978프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver WM8978오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 WM8978데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인IIC, IIS버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC, IIS버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/wm8978/index.html](https://www.libdriver.com/docs/wm8978/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.