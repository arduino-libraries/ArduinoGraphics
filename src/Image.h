/*
  This file is part of the ArduinoGraphics library.
  Copyright (c) 2025 Arduino SA. All rights reserved.
*/

#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdint.h>

enum {
  ENCODING_NONE = -1,
  ENCODING_RGB,
  ENCODING_RGB24,
  ENCODING_RGB16
};

class Image {
public:
  Image();
  Image(int encoding, const uint8_t* data, int width, int height);
  Image(int encoding, const uint16_t* data, int width, int height);
  Image(int encoding, const uint32_t* data, int width, int height);
  virtual ~Image();

  int encoding() const;
  const uint8_t* data() const;
  int width() const;
  int height() const;

  virtual operator bool() const;

private:
  int _encoding;
  const uint8_t* _data;
  int _width;
  int _height;
};

#endif
