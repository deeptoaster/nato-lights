# nato-lights

An extensible plug-and-play Arduino library for controlling multiple Neopixel
LED strips

https://fishbotwilleatyou.com/bin/images/showcase_lights.gif

![](https://fishbotwilleatyou.com/bin/images/showcase_lights.gif)

## About

nato-lights is an aggressively efficient library designed to help you beautify
a space with thoughtful, interactive light shows displayed on long chains of
LED strips that you can hang around, say, the walls of your room.

It owes its entire inspiration to [Hell
Lighting](https://github.com/maxwells-daemons/Hell-Lighting), but was rewritten
from scratch so that we could support over 17 meters (55 feet) of lights using
only a single Arduino Uno.

### Concepts

- **Patterns**

  nato-lights maintains from its predecessor the core concept of **patterns**,
  which are modular and intuitively-written light show designs. One pattern is
  active at a time, and you can switch between patterns using the "next
  pattern" button. During each frame of the execution loop, the active pattern
  is responsible for updating the global `leds` variable with the sequence of
  colors to output to the LED strips.

- **Chains**

  The LED strips to controlled can be divided among up to three **chains**.
  These chains are connected in parallel to the Arduino, while the strips
  within each chain are connected in series. This is primarily to address
  dissipation issues when sending signals down a very long series of LED
  strips&mdash;three chains of 180 LEDs will perform a lot more reliably than a
  single chain of 540 LEDs.

  Patterns don't need to worry about how the LED strips are organized into
  chains and need only treat `leds` as a single long array of colors. The
  library will automatically direct output to the correcte chains as long as
  [_config.h_ is set up properly](#basic-configuration).

## Installation

### Hardware

This project is designed to work with a variety of hardware arrangements,
depending on the dimensions of the space to be decorated and the availability
of components used.

Out of the box&mdash;that is, with only changes to _config.h_ as described in
[Configuration](#configuration)&mdash;it supports one button for toggling
between patterns, up to two potentiometers for interactivity in patterns, up to
three chains of light strips with as many lights as memory will allow, and as
many patterns as memory will allow.

My reference design consists of the following components:

- [individually addressable ws2812b WS2812 RGB 5050 LED Strip Smart Full color
  Pixel IC Ditigal waterproof tape light DC5V 1m/4m/5m (1m 30led ip30, white
  PCB)](https://www.aliexpress.us/item/2251832609237715.html) &times; 20
- [12 GAUGE WIRE RED & BLACK POWER GROUND 100 FT EACH PRIMARY STRANDED COPPER
  CLAD](https://www.amazon.com/gp/product/B01C7O82LU/) &times; 1
- [ALITOVE 5V 60A 300W Power Supply Transformer Adapter Converter AC110V/220V
  to DC 5V 60amp LED Driver for WS2812B WS2811 WS2801 APA102 LED Strip Pixel
  Light CCTV Camera Security
  System](https://www.amazon.com/gp/product/B06XK3X3PW/) &times; 1
- [Proto Advantage Solder Breadboard (10 row 5
  column)](http://www.proto-advantage.com/store/product_info.php?products_id=200004)
  &times; 1
- [SparkFun Electronics Tactile
  Button](https://www.sparkfun.com/products/10302) &times; 1
- [TT Electronics P160KNP Panel
  Pot](https://www.ttelectronics.com/products/passive-components/potentiometers/p160knp/)
  &times; 1
- Arduino Uno &times; 1

I used one potentiometer even though the library supports two out of the box.

| Diagram                                                                                         | Front                                                                                        | Back                                                                                        |
| ----------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| ![](https://raw.githubusercontent.com/deeptoaster/nato-lights/master/images/nato-lights_bb.png) | ![](https://raw.githubusercontent.com/deeptoaster/nato-lights/master/images/board_front.png) | ![](https://raw.githubusercontent.com/deeptoaster/nato-lights/master/images/board_back.png) |

In addition, I 3D-printed a wall-mounted encasement for the complete control
box. The SolidWorks assembly and STL files are available in the _encasement_
directory.

| Front                                                                                             | Side                                                                                             |
| ------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------ |
| ![](https://raw.githubusercontent.com/deeptoaster/nato-lights/master/images/encasement_front.png) | ![](https://raw.githubusercontent.com/deeptoaster/nato-lights/master/images/encasement_side.png) |

### Software

1.  Install the [Arduino IDE](https://docs.arduino.cc/software/ide/).
2.  Open _nato-lights.ino_ in the Arduino IDE.
3.  [Install](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library/)
    the [FastLED](https://www.arduino.cc/reference/en/libraries/fastled/)
    library.
4.  Connect your Arduino Uno by USB and ensure that the board is selected.
5.  Click **Sketch > Upload** to [compile and
    upload](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-uploading-a-sketch/#uploading-a-sketch)
    the project.

If you're on Linux, you may need to [add yourself to the `dialout`
group](https://support.arduino.cc/hc/en-us/articles/360016495679-Fix-port-access-on-Linux#dialout)
in order to avoid a permissions error while uploading.

## Configuration

### Basic Configuration

If your hardware setup is reasonably similar to [mine](#hardware), you'll only
need to modify _config.h_.

- **`BUTTON_DEBOUNCE`**

  Milliseconds within which to [ignore button
  signals](https://en.wikipedia.org/wiki/Switch#Contact_bounce).

  You only need to modify this if the "next pattern" button is having trouble
  detecing single presses.

- **`LED_DUPLICATION`**

  Number of times to repeat each color in each frame of a pattern. For example,
  if a pattern outputs a frame with colors `[A, B, C, D, E, ...]`, the physical
  LED strip will display `[A, B, C, D, E, ...]` with `LED_DUPLICATION = 1`,
  `[A, A, B, B, C, ...]` with `LED_DUPLICATION = 2`, `[A, A, A, B, B, ...]`
  with `LED_DUPLICATION = 3`, etc.

  Increase this value to visually stretch out the displayed patterns and to
  decrease memory usage. Decrease this value to make the displayed patterns
  appear more compact.

- **`LED_PIN_1`, `LED_PIN_2`, `LED_PIN_3`**

  The [PWM-capable digital
  pins](https://www.circuito.io/blog/arduino-uno-pinout/) to which the [LED
  strip chains](#concepts) are connected.

- **`LED_COUNT_1`, `LED_COUNT_2`, `LED_COUNT_3`**

  The number of colors to output to each [LED strip chain](#concepts). The
  physical number of active LEDs in each chain will then be its count
  multiplied by `LED_DUPLICATION`.

- **`LED_TYPE`**

  The [LED chipset](https://github.com/FastLED/FastLED/wiki/Chipset-reference)
  as recognized by FastLED.

- **`NEXT_BUTTON_PIN`**

  The [digital pin](https://www.circuito.io/blog/arduino-uno-pinout/) to which
  the "next pattern" button is connected.

- **`POT_1_MAX`, `POT_2_MAX`**

  The maximum output value of the potentiometers.

- **`POT_1_PIN`, `POT_2_PIN`**

  The [analog pins](https://www.circuito.io/blog/arduino-uno-pinout/) to which
  the potentiometers are connected.

### Adding or Modifying Patterns

Adding a [new pattern](#concepts) is easy! Take a look at how the existing
patterns are defined in the _patterns_ directory.

1.  Create _patterns/pattern_name.h_ and _patterns/pattern_name.cpp_ extending
    `Pattern`. The `init` and `step` methods are responsible for initializing
    the global `leds` variable and updating it for each subsequent frame,
    respectively.
2.  Add the line `#include "src/patterns/pattern_name.h"` to _nato-lights.ino_.

### Removing Patterns

Simply remove the line `#include "src/patterns/pattern_name.h"` from
_nato-lights.ino_.

## Contributing

Feedback and contributions are always welcome! If you have any bug reports,
feature requests, or questions, please open a GitHub
[issue](https://github.com/deeptoaster/nato-lights/issues).

To contribute, follow the instructions below to set up local development and
submit a GitHub [pull
request](https://github.com/deeptoaster/nato-lights/pulls). You will need to
have [Git](https://git-scm.com/doc) installed.

1.  [Create a fork of deeptoaster/nato-lights to your own account and clone
    it.](https://help.github.com/en/articles/fork-a-repo)
2.  Follow the [installation instructions](#installation) above to set up and
    compile the project in the Arduino IDE using your cloned project directory.
3.  After making your changes, [commit
    them](https://git-scm.com/docs/gittutorial#_making_changes), push them to
    your fork on GitHub, and [create a pull
    request](https://help.github.com/en/articles/creating-a-pull-request-from-a-fork)
    to deeptoaster/nato-lights.
