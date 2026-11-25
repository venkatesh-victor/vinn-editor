#include <cstddef>
#include <raylib.h>
#include <algorithm>
#include <cmath>


#include "cursor.h"
#include "config.h"
#include "buffer.h"

// TODO: Draw the rectangle directly instead of creating a rectangle object.
void Cursor::drawCursor(float x, float y)
{
  this->cursor_rect.x = x + (this->column_index * STEP_WIDTH);
  this->cursor_rect.y = y + (this->line_index * (FONT_SIZE + 2));
  DrawRectangleRec(this->cursor_rect, WHITE);
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
}

void Cursor::moveCursorUp(const Buffer& buffer)
{
  if (this->line_index == 0)
    return;

  this->line_index -= 1;
  this->column_index = std::min(column_index, buffer.lines_of_text[line_index].size());
}

void Cursor::moveCursorDown(const Buffer& buffer)
{
  if (this->line_index == buffer.lines_of_text.size() - 1)
    return;

  this->line_index += 1;
  this->column_index = std::min(column_index, buffer.lines_of_text[line_index].size());
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

float Cursor::getCursorX()
{
  return this->cursor_rect.x;
}

float Cursor::getCursorY()
{
  return this->cursor_rect.y;
}

