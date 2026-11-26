#ifndef __CURSOR_H
#define __CURSOR_H

#include "buffer.h"

#include <cstddef>
#include <cmath>
#include <raylib.h>

class Cursor
{
  std::size_t line_index { 0 };
  std::size_t column_index { 0 };
  std::size_t preferred_column { column_index };

public:
  void drawCursor(float x, float y);
  void moveCursorRight(const Buffer& buffer);
  void moveCursorLeft(const Buffer& buffer);
  void moveCursorUp(const Buffer& buffer);
  void moveCursorDown(const Buffer& buffer);
  void moveCursorToLineStart();

  std::size_t getLineIndex();
  std::size_t getColumnIndex();
};

#endif

