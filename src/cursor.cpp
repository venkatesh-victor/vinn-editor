#include "cursor.h"
#include "config.h"
#include <raylib.h>


void Cursor::drawCursor()
{
  DrawRectangleRec(this->cursor_rect, WHITE);
}

void Cursor::moveCursorRight()
{
  this->cursor_rect.x += this->step_width;
}

void Cursor::moveCursorLeft()
{
  this->cursor_rect.x -= this->step_width;
}

void Cursor::moveCursorUp()
{
  this->cursor_rect.y -= FONT_SIZE + 2;
}

void Cursor::moveCursorDown()
{
  this->cursor_rect.y += FONT_SIZE + 2;
}

