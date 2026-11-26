#include <cstddef>
#include <raylib.h>
#include <algorithm>
#include <cmath>


#include "cursor.h"
#include "config.h"
#include "buffer.h"

void Cursor::drawCursor(float x, float y)
{  
  float cursor_x { x + this->column_index * STEP_WIDTH };
  float cursor_y { y + this->line_index * (FONT_SIZE + 2) };
  DrawRectangle(cursor_x, cursor_y, 2, FONT_SIZE, WHITE);
}

void Cursor::moveCursorRight(const Buffer& buffer)
{
  if (this->line_index == buffer.lines_of_text.size() - 1 &&
      this->column_index == buffer.lines_of_text[line_index].size())
    return;

  if (this->column_index == buffer.lines_of_text[line_index].size())
  {
    this->line_index += 1;
    this->column_index = 0;
    return;
  }

  this->column_index += 1;
  this->preferred_column += 1;
}

void Cursor::moveCursorLeft(const Buffer& buffer)
{
  if (this->line_index == 0 && this->column_index == 0)
    return;

  if (this->column_index == 0)
  {
    this->line_index -= 1;
    this->column_index = buffer.lines_of_text[line_index].size();
    return;
  }

  this->column_index -= 1;
  this->preferred_column -= 1;
}

void Cursor::moveCursorUp(const Buffer& buffer)
{
  if (this->line_index == 0)
    return;

  this->line_index -= 1;
  this->column_index = std::min(this->preferred_column, buffer.lines_of_text[line_index].size());
}

void Cursor::moveCursorDown(const Buffer& buffer)
{
  if (this->line_index == buffer.lines_of_text.size() - 1)
    return;

  this->line_index += 1;
  this->column_index = std::min(this->preferred_column, buffer.lines_of_text[line_index].size());
}

void Cursor::moveCursorToLineStart()
{
  this->column_index = 0;
}

std::size_t Cursor::getLineIndex()
{
  return this->line_index;
}

std::size_t Cursor::getColumnIndex()
{
  return this->column_index;
}

