/**************************************************************************************
Example sketch that illustrates the driving of a 1.8 inch SPI ST7735 TFT Display 128 x 160 Pixel.
In scope is also the programmatic activation and deactivation of the TFT backlight.

Inspired by https://github.com/olikraus/ucglib/wiki/connectst7735
I'm using the following display: https://www.az-delivery.de/products/1-8-zoll-spi-tft-display

********************************************

Copyright © 2021 Anja Kuchenbecker

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************************/
// Includes
#include "Ucglib.h" 

// TFT pin definitions
// Note: SCK/SCL pin (D52) and SDA/MOSI pin (D51) on arduino mega must be not extra defined here when using hardware spi constructor (see below)
#define TFT_CD_PIN 16 // A0 on display
#define TFT_CS_PIN 18 // CS on display
#define TFT_RESET_PIN 17 // RESET on display
#define TFT_BACKLIGHT_CONTROL_PIN 8 // "LED" pin on display: add a 39 Ohm resistor to reduce from 5v to 3.3v (100 Ohm is also OK, bigger resistor -> darker display)

// TFT Constructor (hardware SPI usage --> HWSPI)
Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ TFT_CD_PIN, /*cs=*/ TFT_CS_PIN, /*reset=*/ TFT_RESET_PIN);

void setup() {
  
  // Set pin mode for pin that controls the backlight of the TFT display
  pinMode(TFT_BACKLIGHT_CONTROL_PIN, OUTPUT);

  // Setup display: set font mode, clear, rotate
  ucg.begin(UCG_FONT_MODE_SOLID);
  ucg.clearScreen();
  ucg.setRotate90();
  
  // Print some stuff on the display
  // Note: printing within loop is very slow print static content only once in setup() and update dynamic content within loop() only when necessary
  ucg.setFont(ucg_font_6x12_mf);
  ucg.setColor(0,255, 0, 0);
  ucg.setPrintPos(10,30);
  ucg.print("Hello World ;-)");
  
}

void loop() {

  // Turn backlight off
  digitalWrite(TFT_BACKLIGHT_CONTROL_PIN,HIGH);

  // Wait some time to see the backlight switch
  delay(2000);
  
  // Turn backlight on
  digitalWrite(TFT_BACKLIGHT_CONTROL_PIN,LOW);

  // Wait some time to see the backlight switch
  delay(2000);

}
