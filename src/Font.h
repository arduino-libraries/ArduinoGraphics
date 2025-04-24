/*
  This file is part of the ArduinoGraphics library.
  Copyright (c) 2025 Arduino SA. All rights reserved.
*/

#ifndef _FONT_H
#define _FONT_H

#include <stddef.h>
#include <stdint.h>

struct Font {
  const int width;
  const int height;
  const uint8_t** data;
};

#endif
