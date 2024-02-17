[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WM8978

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/wm8978/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der WM8978 ist ein hochwertiger Stereo-CODEC mit geringem Stromverbrauch, der für tragbare Anwendungen wie Multimedia-Telefone, digitale Fotokameras oder digitale Camcorder entwickelt wurde. Das Gerät integriert Vorverstärker für Stereo-Differenzialmikrofone und umfasst Treiber für Lautsprecher, Kopfhörer und Differenzial- oder Stereo-Line-Ausgang. Der Bedarf an externen Komponenten wird reduziert, da keine separaten Mikrofon- oder Kopfhörerverstärker erforderlich sind. Die fortschrittliche digitale On-Chip-Signalverarbeitung umfasst einen 5-Band-Equalizer, eine automatische Pegelregelung für gemischte Signale für den Mikrofon- oder Line-Eingang über den ADC sowie eine rein digitale Signalverarbeitung Limiter-Funktion für Aufnahme oder Wiedergabe. Zusätzliche digitale Filteroptionen stehen im ADC-Pfad zur Verfügung, um Anwendungsfilterung wie „Windgeräuschreduzierung“ zu ermöglichen. Die digitale Audioschnittstelle WM8978 kann als Master oder Slave betrieben werden. Eine interne PLL kann alle erforderlichen Audiotakte für den CODEC aus gängigen Referenztaktfrequenzen wie 12 MHz und 13 MHz erzeugen. Der WM8978 arbeitet mit analogen Versorgungsspannungen von 2,5 V bis 3,3 V, obwohl der digitale Kern mit Spannungen bis hinunter zu 1,71 V betrieben werden kann um Strom zu sparen. Die Lautsprecherausgänge und OUT3/4-Line-Ausgänge können mit einer 5-V-Versorgung betrieben werden, wenn eine höhere Ausgangsleistung erforderlich ist. Einzelne Abschnitte des Chips können auch softwaregesteuert abgeschaltet werden.

LibDriver WM8978 ist der von LibDriver gestartete Vollfunktionstreiber von WM8978. Er bietet Audiowiedergabe, Audioaufnahme und andere Funktionen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example play](#example-play)
    - [example record](#example-record)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver WM8978-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver WM8978 IIC, IIS.

/test enthält den Testcode des LibDriver WM8978-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver WM8978-Beispielcode.

/doc enthält das LibDriver WM8978-Offlinedokument.

/Datenblatt enthält WM8978-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC, IIS-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC, IIS-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/wm8978/index.html](https://www.libdriver.com/docs/wm8978/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.