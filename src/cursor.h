#ifndef __CURSOR_H
#define __CURSOR_H

#include "config.h"
#include "buffer.h"

#include <cstddef>
#include <cmath>
#include <raylib.h>

class Cursor
{
  float pos_x { 10.0f };
  float pos_y { 10.0f };

  Rectangle cursor_rect { pos_x, pos_y, 2, FONT_SIZE };

  std::size_t line_index { 0 };
  std::size_t column_index { 0 };

public:
  void drawCursor(float x, float y);
  void moveCursorRight(const Buffer& buffer);
  void moveCursorLeft(const Buffer& buffer);
  void moveCursorUp(const Buffer& buffer);
  void moveCursorDown(const Buffer& buffer);
  void moveCursorToLineStart();

  std::size_t getLineIndex();
  std::size_t getColumnIndex();

  float getCursorX();
  float getCursorY();
};

#endif

