# Arduino Graphics Library

This is a library that allows you to draw and write on screens with graphical primitives; it requires a specific hardware interface library to drive the screen you are using, therefore every screen type should have its own hardware specific library.

To use this library

```
#include <ArduinoGraphics.h>
```

To let you easily understand the usage of the graphics primitives, we are using a dummy screen object named YourScreen that should be substituted with the real one, Eg. MATRIX, OLED, TFT and so on. Refer to the hardware interfacing library of your screen to get more details.

The style and syntax of this library is inspired by [Processing 3](https://processing.org/) and we believe that learning Processing is very helpful to develop complex applications that combine the versatility of Arduino driven hardware with the power of a pc based graphical interface.

## How-to generate bitmaps from the fonts

```bash
cd extras
./generate_font.py 5x7.bdf Font_5x7.c Font_5x7
```