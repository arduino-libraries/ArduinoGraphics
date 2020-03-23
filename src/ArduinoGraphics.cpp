/*
  This file is part of the ArduinoGraphics library.
  Copyright (c) 2019 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "ArduinoGraphics.h"

#define COLOR_R(color) (uint8_t(color >> 16))
#define COLOR_G(color) (uint8_t(color >> 8))
#define COLOR_B(color) (uint8_t(color >> 0))

ArduinoGraphics::ArduinoGraphics(int width, int height) :
  _width(width),
  _height(height),
  _font(NULL)
{
}

ArduinoGraphics::~ArduinoGraphics()
{
}

int ArduinoGraphics::begin()
{
  background(0, 0, 0);
  noFill();
  noStroke();

  _textScrollSpeed = 100;

  return 1;
}

void ArduinoGraphics::end()
{
}

int ArduinoGraphics::width()
{
  return _width;
}

int ArduinoGraphics::height()
{
  return _height;
}

void ArduinoGraphics::beginDraw()
{
}

void ArduinoGraphics::endDraw()
{
}

void ArduinoGraphics::background(uint8_t r, uint8_t g, uint8_t b)
{
  _backgroundR = r;
  _backgroundG = g;
  _backgroundB = b;
}

void ArduinoGraphics::background(uint32_t color)
{
  background(COLOR_R(color), COLOR_G(color), COLOR_B(color));
}

void ArduinoGraphics::clear()
{
  for (int x = 0; x < _width; x++) {
    for (int y = 0; y < _height; y++) {
      set(x, y, _backgroundR, _backgroundB, _backgroundG);
    }
  }
}

void ArduinoGraphics::fill(uint8_t r, uint8_t g, uint8_t b)
{
  _fill = true;
  _fillR = r;
  _fillG = g;
  _fillB = b;
}

void ArduinoGraphics::fill(uint32_t color)
{
  fill(COLOR_R(color), COLOR_G(color), COLOR_B(color));
}

void ArduinoGraphics::noFill()
{
  _fill = false;
}

void ArduinoGraphics::stroke(uint8_t r, uint8_t g, uint8_t b)
{
  _stroke = true;
  _strokeR = r;
  _strokeG = g;
  _strokeB = b;
}

void ArduinoGraphics::stroke(uint32_t color)
{
  stroke(COLOR_R(color), COLOR_G(color), COLOR_B(color));
}

void ArduinoGraphics::noStroke()
{
  _stroke = false;
}

void ArduinoGraphics::line(int x1, int y1, int x2, int y2)
{
  if (!_stroke) {
    return;
  }

  if (x1 == x2) {
    for (int y = y1; y <= y2; y++) {
      set(x1, y, _strokeR, _strokeG, _strokeB);
    }
  } else if (y1 == y2) {
    for (int x = x1; x <= x2; x++) {
      set(x, y1, _strokeR, _strokeG, _strokeB);
    }
  } else if (abs(y2 - y1) < abs(x2 - x1)) {
    if (x1 > x2) {
      lineLow(x2, y2, x1, y1);
    } else {
      lineLow(x1, y1, x2, y2);
    }
  } else {
    if (y1 > y2) {
      lineHigh(x2, y2, x1, y1);
    } else {
      lineHigh(x1, y1, x2, y2);
    }
  }
}

void ArduinoGraphics::point(int x, int y)
{
  if (_stroke) {
    set(x, y, _strokeR, _strokeG, _strokeB);
  }
}

void ArduinoGraphics::rect(int x, int y, int width, int height)
{
  if (!_stroke && !_fill) {
    return;
  }

  int x1 = x;
  int y1 = y;
  int x2 = x1 + width - 1;
  int y2 = y1 + height - 1;

  for (x = x1; x <= x2; x++) {
    for (y = y1; y <= y2; y++) {
      if ((x == x1 || x == x2 || y == y1 || y == y2) && _stroke) {
        // stroke
        set(x, y, _strokeR, _strokeG, _strokeB);
      } else if (_fill) {
        // fill
        set(x, y, _fillR, _fillG, _fillB);
      }
    }
  }
}

void ArduinoGraphics::ellipse(int x, int y, int width, int height)
{
    if (!_stroke && !_fill) {
      return;
    }

    int r1 = (int)(width/2);
    int r2 = (int)(height/2);

    x--;
    y--;

    for(int i = 0; i < r1; i++)
    {
        int j = ceil(sqrt(1 - ((float)(i*i)/(r1*r1))) * r2);

        int x1 = x-i;
        int x2 = x+i;
        int y1 = y-j;
        int y2 = y+j;

        if(width%2 == 0)
        {
            x2--;
        }

        if(height%2 == 0)
        {
            y2--;
        }

        if(_stroke)
        {
            set(x1, y1, _strokeR, _strokeG, _strokeB);
            set(x1, y2, _strokeR, _strokeG, _strokeB);
            set(x2, y1, _strokeR, _strokeG, _strokeB);
            set(x2, y2, _strokeR, _strokeG, _strokeB);
        }

        if(_fill)
        {
            for(int a = 0; a < j; a++)
            {
                int x1 = x-i;
                int x2 = x+i;
                int y1 = y-a;
                int y2 = y+a;

                if(width%2 == 0)
                {
                    x2--;
                }

                if(height%2 == 0)
                {
                    y2--;
                }

                set(x1, y1, _fillR, _fillG, _fillB);
                set(x1, y2, _fillR, _fillG, _fillB);
                set(x2, y1, _fillR, _fillG, _fillB);
                set(x2, y2, _fillR, _fillG, _fillB);
            }
        }
    }

    if(_stroke)
    {
        for(int j = 0; j < r2; j++)
        {
            int i = ceil(sqrt(1 - ((float)(j*j)/(r2*r2))) * r1);

            int x1 = x-i;
            int x2 = x+i;
            int y1 = y-j;
            int y2 = y+j;

            if(width%2 == 0)
            {
                x2--;
            }

            if(height%2 == 0)
            {
                y2--;
            }

            set(x1, y1, _strokeR, _strokeG, _strokeB);
            set(x1, y2, _strokeR, _strokeG, _strokeB);
            set(x2, y1, _strokeR, _strokeG, _strokeB);
            set(x2, y2, _strokeR, _strokeG, _strokeB);
        }
    }
}

void ArduinoGraphics::circle(int x, int y, int radius)
{
  ellipse(x, y, ((radius*2)-1), ((radius*2)-1));
}

void ArduinoGraphics::text(const char* str, int x, int y)
{
  if (!_font || !_stroke) {
    return;
  }

  while (*str) {
    int c = *str++;

    if (c == '\n') {
      y += _font->height;
    } else if (c == '\r') {
      x = 0;
    } else if (c == 0xc2 || c == 0xc3) {
      // drop
    } else {
      const uint8_t* b = _font->data[c];

      if (b == NULL) {
        b =  _font->data[0x20];
      }

      if (b) {
        bitmap(b, x, y, _font->width, _font->height);
      }

      x += _font->width;
    }
  }
}

void ArduinoGraphics::textFont(const Font& which)
{
  _font = &which;
}

int ArduinoGraphics::textFontWidth() const
{
  return (_font ? _font->width : 0);
}

int ArduinoGraphics::textFontHeight() const
{
  return (_font ? _font->height : 0);
}

void ArduinoGraphics::bitmap(const uint8_t* data, int x, int y, int width, int height)
{
  if (!_stroke) {
    return;
  }

  if ((data == NULL) || ((x + width) < 0) || ((y + height) < 0) || (x > _width) || (y > height)) {
    // offscreen
    return;
  }

  for (int j = 0; j < height; j++) {
    uint8_t b = data[j];

    for (int i = 0; i < width; i++) {
      if (b & (1 << (7 - i))) {
        set(x + i, y + j, _strokeR, _strokeG, _strokeB);
      } else {
        set(x + i, y + j, _backgroundR, _backgroundG, _backgroundB);
      }
    }
  }
}

void ArduinoGraphics::imageRGB(const Image& img, int x, int y, int width, int height)
{
  const uint8_t* data = img.data();

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      uint8_t r = *data++;
      uint8_t g = *data++;
      uint8_t b = *data++;

      set(x + i, y + j, r, g, b);

      data++;
    }

    data += (4 * (img.width() - width));
  }
}

void ArduinoGraphics::imageRGB24(const Image& img, int x, int y, int width, int height)
{
  const uint8_t* data = img.data();

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      uint8_t r = *data++;
      uint8_t g = *data++;
      uint8_t b = *data++;

      set(x + i, y + j, r, g, b);
    }

    data += (3 * (img.width() - width));
  }
}

void ArduinoGraphics::imageRGB16(const Image& img, int x, int y, int width, int height)
{
  const uint16_t* data = (const uint16_t*)img.data();

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      uint16_t pixel = *data++;

      set(x + i, y + j, ((pixel >> 8) & 0xf8), ((pixel >> 3) & 0xfc), (pixel << 3) & 0xf8);
    }

    data += (img.width() - width);
  }
}

void ArduinoGraphics::image(const Image& img, int x, int y)
{
  image(img, x, y, img.width(), img.height());
}

void ArduinoGraphics::image(const Image& img, int x, int y, int width, int height)
{
  if (!img || ((x + width) < 0) || ((y + height) < 0) || (x > _width) || (y > height)) {
    // offscreen
    return;
  }

  switch (img.encoding()) {
    case ENCODING_RGB:
      imageRGB(img, x, y, width, height);
      break;

    case ENCODING_RGB24:
      imageRGB24(img, x, y, width, height);
      break;

    case ENCODING_RGB16:
      imageRGB16(img, x, y, width, height);
      break;
  }
}

void ArduinoGraphics::set(int x, int y, uint32_t color)
{
  set(x, y, COLOR_R(color), COLOR_G(color), COLOR_B(color));
}

size_t ArduinoGraphics::write(uint8_t b)
{
  if (b != 0xc2 && b != 0xc3) {
    _textBuffer += (char)b;
  }

  return 1;
}

void ArduinoGraphics::flush()
{
  _textBuffer = "";
}

void ArduinoGraphics::beginText(int x, int y)
{
  _textBuffer = "";

  _textX = x;
  _textY = y;
}

void ArduinoGraphics::beginText(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
  beginText(x, y);

  _textR = r;
  _textG = g;
  _textB = b;
}

void ArduinoGraphics::beginText(int x, int y, uint32_t color)
{
  beginText(x, y, COLOR_R(color), COLOR_G(color), COLOR_B(color));
}

void ArduinoGraphics::endText(int scrollDirection)
{
  // backup the stroke color and set the color to the text color
  bool strokeOn = _stroke;
  uint8_t strokeR = _strokeR;
  uint8_t strokeG = _strokeG;
  uint8_t strokeB = _strokeB;


  stroke(_textR, _textG, _textB);

  if (scrollDirection == SCROLL_LEFT) {
    int scrollLength = _textBuffer.length() * textFontWidth() + _textX;

    for (int i = 0; i < scrollLength; i++) {
      beginDraw();
      text(_textBuffer, _textX - i, _textY);
      endDraw();

      delay(_textScrollSpeed);
    }
  } else if (scrollDirection == SCROLL_RIGHT) {
    int scrollLength = _textBuffer.length() * textFontWidth() + _textX;

    for (int i = 0; i < scrollLength; i++) {
      beginDraw();
      text(_textBuffer, _textX - (scrollLength - i - 1), _textY);
      endDraw();

      delay(_textScrollSpeed);
    }
  } else if (scrollDirection == SCROLL_UP) {
    int scrollLength = textFontHeight() + _textY;

    for (int i = 0; i < scrollLength; i++) {
      beginDraw();
      text(_textBuffer, _textX, _textY - i);
      endDraw();

      delay(_textScrollSpeed);
    }
  } else if (scrollDirection == SCROLL_DOWN) {
    int scrollLength = textFontHeight() + _textY;

    for (int i = 0; i < scrollLength; i++) {
      beginDraw();
      text(_textBuffer, _textX, _textY - (scrollLength - i - 1));
      endDraw();

      delay(_textScrollSpeed);
    }
  } else {
    beginDraw();
    text(_textBuffer, _textX, _textY);
    endDraw();
  }

  // restore the stroke color
  if (strokeOn) {
    stroke(strokeR, strokeG, strokeB);
  } else {
    noStroke();
  }

  // clear the buffer
  _textBuffer = "";
}

void ArduinoGraphics::textScrollSpeed(unsigned long speed)
{
  _textScrollSpeed = speed;
}

void ArduinoGraphics::lineLow(int x1, int y1, int x2, int y2)
{
  int dx = x2 - x1;
  int dy = y2 - y1;
  int yi = 1;

  if (dy < 0) {
    yi = -1;
    dy = -dy;
  }

  int D = 2 * dy - dx;
  int y = y1;

  for (int x = x1; x <= x2; x++) {
    set(x, y, _strokeR, _strokeG, _strokeB);

    if (D > 0) {
      y += yi;
      D -= (2 * dx);
    }

    D += (2 * dy);
  }
}

void ArduinoGraphics::lineHigh(int x1, int y1, int x2, int y2)
{
  int dx = x2 - x1;
  int dy = y2 - y1;
  int xi = 1;

  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }

  int D = 2 * dx - dy;
  int x = x1;

  for (int y = y1; y <= y2; y++) {
    set(x, y, _strokeR, _strokeG, _strokeB);

    if (D > 0) {
       x += xi;
       D -= 2 * dy;
    }

    D += 2 * dx;
  }
}
