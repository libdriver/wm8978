### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIS Pin: SCLK/LRCK/SDOUT/SDIN/MCLK PB13/PB12/PC2/PC3/PC6.

IIC Pin: SCL/SDA PB8/PB9.

SDIO Pin: D0/D1/D2/D3/SCK/CMD PC8/PC9/PC10/PC11/PC12/PD2.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. WM8978

#### 3.1 Command Instruction

1. Show wm8978 chip and driver information.

   ```shell
   wm8978 (-i | --information)
   ```

2. Show wm8978 help.

   ```shell
   wm8978 (-h | --help)
   ```

3. Show wm8978 pin connections of the current board.

   ```shell
   wm8978 (-p | --port)
   ```

4. Run wm8978 play test, path is the wav music file path.

   ```shell
   wm8978 (-t play | --test=play) [--file=<path>]
   ```

5. Run wm8978 record test, path is the wav music file path, second is the set second.

   ```shell
   wm8978 (-t record | --test=record) [--file=<path>] [--time=<second>]
   ```

6. Run wm8978 play function, path is the wav music file path.

   ```shell
   wm8978 (-e play | --example=play) [--file=<path>]
   ```

7. Run wm8978 record function, path is the wav music file path, second is the set second.

   ```shell
   wm8978 (-e record | --example=record) [--file=<path>] [--time=<second>]
   ```

8. Run wm8978 set volume function, vol is set the volume.

   ```shell
   wm8978 (-e volume | --example=volume) [--volume=<vol>]
   ```

9. Run wm8978 set microphone function, vol is set the volume.

   ```shell
   wm8978 (-e microphone | --example=microphone) [--volume=<vol>]
   ```

10. Run wm8978 mute function.
    
    ```shell
    wm8978 (-e mute | --example=mute)
    ```

#### 3.2 Command Example

```shell
wm8978 -i

wm8978: chip is Cirrus Logic WM8978.
wm8978: manufacturer is Cirrus Logic.
wm8978: interface is IIC IIS.
wm8978: driver version is 1.0.
wm8978: min supply voltage is 2.5V.
wm8978: max supply voltage is 5.5V.
wm8978: max current is 18.00mA.
wm8978: max temperature is 100.0C.
wm8978: min temperature is -40.0C.
```

```shell
wm8978 -p

wm8978: SCK connected to GPIOB PIN13.
wm8978: LRCK connected to GPIOB PIN12.
wm8978: SDOUT connected to GPIOC PIN2.
wm8978: SDIN connected to GPIOC PIN3.
wm8978: MCLK connected to GPIOC PIN6.
wm8978: SCL connected to GPIOB PIN8.
wm8978: SDA connected to GPIOB PIN9.
```

```shell
wm8978 -t play --file=0:we-are-the-world.wav

wm8978: chip is Cirrus Logic WM8978.
wm8978: manufacturer is Cirrus Logic.
wm8978: interface is IIC IIS.
wm8978: driver version is 1.0.
wm8978: min supply voltage is 2.5V.
wm8978: max supply voltage is 5.5V.
wm8978: max current is 18.00mA.
wm8978: max temperature is 100.0C.
wm8978: min temperature is -40.0C.
wm8978: start play test.
wav: playing 196654/67880494.
wav: playing 376878/67880494.
wav: playing 557102/67880494.

...

wav: play end.
wav: playing 67895342/67880494.
wm8978: finish play test.
```

```shell
wm8978 -t record --file=0:record_test.wav --time=60

wm8978: chip is Cirrus Logic WM8978.
wm8978: manufacturer is Cirrus Logic.
wm8978: interface is IIC IIS.
wm8978: driver version is 1.0.
wm8978: min supply voltage is 2.5V.
wm8978: max supply voltage is 5.5V.
wm8978: max current is 18.00mA.
wm8978: max temperature is 100.0C.
wm8978: min temperature is -40.0C.
wm8978: start record test.
wav: record 49196 bytes time 1/60s.
wav: record 114732 bytes time 2/60s.
wav: record 180268 bytes time 3/60s.

...

wav: record 3719212 bytes time 58/60s.
wav: record 3784748 bytes time 59/60s.
wav: record 3850284 bytes time 60/60s.
wm8978: finish record test.
```

```shell
wm8978 -e play --file=0:we-are-the-world.wav

wm8978: start play.
wav: playing 196654/67880494.
wav: playing 376878/67880494.
wav: playing 557102/67880494.

...

wav: playing 67469358/67880494.
wav: playing 67649582/67880494.
wav: playing 67829806/67880494.
wav: play end.
wm8978: finish play.
```

```shell
wm8978 -e record --file=0:record.wav --time=60

wm8978: start record test.
wav: record 81964 bytes time 1/60s.
wav: record 163884 bytes time 2/60s.
wav: record 262188 bytes time 3/60s.

...

wav: record 5144620 bytes time 58/60s.
wav: record 5242924 bytes time 59/60s.
wav: record 5324844 bytes time 60/60s.
wm8978: finish record.
```

```shell
wm8978 -e volume --volume=-10.0

wm8978: set volume -10.0db.
```

```shell
wm8978 -e microphone --volume=-10.0

wm8978: set microphone -10.0db.
```

```shell
wm8978 -e mute

wm8978: mute.
```

```shell
wm8978 -h

Usage:
  wm8978 (-i | --information)
  wm8978 (-h | --help)
  wm8978 (-p | --port)
  wm8978 (-t play | --test=play) [--file=<path>]
  wm8978 (-t record | --test=record) [--file=<path>] [--time=<second>]
  wm8978 (-e play | --example=play) [--file=<path>]
  wm8978 (-e record | --example=record) [--file=<path>] [--time=<second>]
  wm8978 (-e volume | --example=volume) [--volume=<vol>]
  wm8978 (-e microphone | --example=microphone) [--volume=<vol>]
  wm8978 (-e mute | --example=mute)

Options:
  -e <play | record | volume | microphone | mute>, --example=<play | record | volume | microphone | mute>
                          Run the driver example.
      --file=<path>       Set the wav file path.([default: test.wav])
  -h, --help              Show the help.
  -i, --information       Show the chip information.
      --volume=<vol>      Set the volume.([default: -10.0])
  -p, --port              Display the pin connections of the current board.
  -t <play | record>, --test=<play | record>
                          Run the driver test.
      --time=<second>     Set the record time.([default: 60]).
```

