#include "config.h"

#include <cmath>
#include <raylib.h>

class Cursor
{
  float pos_x { 10.0f };
  float pos_y { 10.0f };
  float step_width {
    (static_cast<float>(FONT_SIZE) / (FONT_SIZE + 1)) * 9.0f
    + LETTER_SPACING
  };

  Rectangle cursor_rect { pos_x, pos_y, 2, FONT_SIZE };

  int line_position;
  int line_index;

public:
  void drawCursor();
  void moveCursorRight();
  void moveCursorLeft();
  void moveCursorUp();
  void moveCursorDown();
};

