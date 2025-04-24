/*
  This file is part of the ArduinoGraphics library.
  Copyright (c) 2025 Arduino SA. All rights reserved.
*/

#include <stddef.h>

#include "Image.h"

Image::Image() :
  Image(ENCODING_NONE, (const uint8_t*)NULL, 0, 0)
{
}

Image::Image(int encoding, const uint8_t* data, int width, int height) :
  _encoding(encoding),
  _data(data),
  _width(width),
  _height(height)
{
}

Image::Image(int encoding, const uint16_t* data, int width, int height) :
  Image(encoding, (const uint8_t*)data, width, height)
{
}

Image::Image(int encoding, const uint32_t* data, int width, int height) :
  Image(encoding, (const uint8_t*)data, width, height)
{
}

Image::~Image()
{
}

int Image::encoding() const
{
  return _encoding;
}

const uint8_t* Image::data() const
{
  return _data;
}

int Image::width() const
{
  return _width;
}

int Image::height() const
{
  return _height;
}

Image::operator bool() const
{
  return (_encoding != ENCODING_NONE && _data != NULL && _width > 0 && _height > 0);
}
