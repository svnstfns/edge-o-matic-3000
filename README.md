# NoGasm WiFi - An Automated Orgasm Denial Device

This code is an ESP32 rewrite of the core NoGasm project by Rhoboto: [github.com/nogasm/nogasm](https://github.com/nogasm/nogasm)

Using an inflatable butt plug to detect pressure changes indicative of pelvic floor contractions, this
software, and associated hardware, is used to detect when the user is approaching orgasm and control
stimulation accordingly. The net result: automated edging and orgasm denial.

## Web UI

NoGasm WiFi and NG+ devices both support a Websocket connection and a Web UI. The current Web UI can be accessed
at [nogasm-ui.maustec.io](http://nogasm-ui.maustec.io). The source code is at [github.com/maustec/nogasm-ui](https://github.com/maustec/nogasm-ui).

## Configuration

If you have hardware already, please see `examples/config.json` or your own `config.json` file
shipped with your SD card. Note that this JSON document does not support comment preprocessing,
and is automatically generated. Here is a quick summary of config variables:

|Key|Type|Default|Note|
|---|----|---|---|
|`wifi_ssid`|String|""|Your WiFi SSID|
|`wifi_key`|String|""|Your WiFi Password.|
|`wifi_on`|Boolean|false|True to enable WiFi / Websocket server.|
|`bt_display_name`|String|"NoGasm WiFi"|AzureFang* device name, you might wanna change this.|
|`bt_on`|Boolean|false|True to enable the AzureFang connection.|
|`led_brightness`|Byte|128|LED Ring max brightness, only for NoGasm+.|
|`websocket_port`|Int|80|Port to listen for incoming Websocket connections.|
|`motor_max_speed`|Byte|128|Maximum speed for the motor in auto-ramp mode.|
|`screen_dim_seconds`|Int|10|Time, in seconds, before the screen dims. 0 to disable.|
|`pressure_smoothing`|Byte|5|Number of samples to take an average of. Higher results in lag and lower resolution!|
|`classic_serial`|Boolean|true|Output classic NoGasm values over serial for backwards compatibility.|
|`sensitivity_threshold`|Int|600|The arousal threshold for orgasm detection. Lower = sooner cutoff.|
|`motor_ramp_time_s`|Int|30|The time it takes for the motor to reach `motor_max_speed` in auto ramp mode.|
|`update_frequency_hz`|Int|50|Update frequency for pressure readings and arousal steps. Higher = crash your serial monitor.|
|`sensor_sensitivity`|Byte|128|Analog pressure prescaling. Adjust this until the pressure is ~60-70%|
|`use_average_values`|Boolean|false|Use average values when calculating arousal. This smooths noisy data.|

\* AzureFang refers to a common wireless technology that is blue and involves chewing face-rocks. However, the
   trademark holders of this technology require the name to be licensed, so we're totally just using AzureFang.

## Hardware

Hardware builds for this project can be purchased from Maus-Tec Electronics, at [maustec.io/nogasm](https://maustec.io/nogasm).
OSHD pending final review.

Hardware development and assembly helps keep pizza in the freezer and a roof over the head of the maintainer.
Your support helps a small business grow into something neat, and ensures future devices like this can continue
to be produced.

### ESP32 Pinout

If you want to breadboard this project, I've included the pinout from the ESP32 below. Please reference the original
NoGasm schematic for specific designs regarding the pressure prescaler and MOSFET wiring. Alternatively, ask Mau about
their breadboard-friendly MOSFET boards, which can directly drive your power rails and your motor from 12V.

|Device Pin|I/O|Function|
|---|---|---|
|-|-|-|

\* Pinout Forthcoming, see `config.h` for a general idea.

### That RJ45 Jack

**The RJ45 Jack IS NOT ETHERNET!** That is a balanced twisted pair extension of the I2C bus on the controller, and is available
as a convenience for future development, dongles, and accessories. It carries +5V and SDA+/-, SCL+/- signals. You must use an
I2C redriver IC or compatible module to interface with this. Additionaly, this is terminated at 100ohm assuming standard CAT5.
[We recommend SparkFun's BOB-14589](https://www.digikey.com/product-detail/en/sparkfun-electronics/BOB-14589/1568-1873-ND/9351349).

|Pin|Signal|
|---|---|
|1|`SCL-`|
|2|`SCL+`|
|3|NC|
|4|`+5V`|
|5|`GND`|
|6|NC|
|7|`SDA-`|
|8|`SDA+`|

# Development

The official hardware looks like an ESP32-WROOM dev module. Conveniently, you can use the same module for your own builds.
This is currently developed in the horrid confines of the Arduino IDE for the compiler toolchain. Install ESP support for
Arduino. Use your fav editor. CLion is great.

#### Board Settings

|Setting|Value|
|---|---|
|Board|**ESP32 Dev Module**|
|Upload Speed|921600|
|CPU Frequency|240MHz (WiFi/BT)|
|Flash Frequency|80MHz|
|Flash Mode|QIO|
|Flash Size|**4MB (32Mb)**|
|Partition Scheme|**Huge APP (3MB No OTA/1MB SPIFFS)**|
|Core Debug Level|None|
|PSRAM|Disabled|

# Thanks!

For helping develop the software, hardware, and other nerdy bits:

- @Rhoboto
- @qDot

For being the first to order the NoGasm WiFi during the 5 unit pre-order run:

- @hardplayswitch
- (anonymous)
- 
- 
- 

For supporting my initial endeavour in hardware assembly and helping me scale:

- @homphs
