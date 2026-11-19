#include <raylib.h>
#include <algorithm>
#include <cmath>


#include "cursor.h"
#include "config.h"
#include "buffer.h"

void Cursor::drawCursor()
{
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

    this->cursor_rect.x = 10.0f;
    this->cursor_rect.y += FONT_SIZE + 2;
    return;
  }

  this->cursor_rect.x += STEP_WIDTH;
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

    this->cursor_rect.x = 10.0f + (this->column_index * STEP_WIDTH);
    this->cursor_rect.y -= FONT_SIZE + 2;
    return;
  }

  this->cursor_rect.x -= STEP_WIDTH;
  this->column_index -= 1;
}

void Cursor::moveCursorUp(const Buffer& buffer)
{
  if (this->line_index == 0)
    return;

  this->line_index -= 1;
  this->column_index = std::min(column_index, buffer.lines_of_text[line_index].size());

  this->cursor_rect.x = 10.0f + (this->column_index * STEP_WIDTH);
  this->cursor_rect.y -= FONT_SIZE + 2;
}

void Cursor::moveCursorDown(const Buffer& buffer)
{
  if (this->line_index == buffer.lines_of_text.size() - 1)
    return;

  this->line_index += 1;
  this->column_index = std::min(column_index, buffer.lines_of_text[line_index].size());
  
  this->cursor_rect.x = 10.0f + (this->column_index * STEP_WIDTH);
  this->cursor_rect.y += FONT_SIZE + 2;
}

