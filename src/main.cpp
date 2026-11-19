#include <iostream>
#include <algorithm>
#include <string>
#include <raylib.h>
#include <raymath.h>

#include "cursor.h"
#include "config.h"
#include "buffer.h"

int main(int argc, char* argv[])
{
  float x { 10 };
  float y { 10 };

  if (argc != 2)
  {
    std::cout << "USAGE: editor [file name]" << '\n';
    return 0;
  }

  const char* font_path { "../font/JetBrains_Mono/static/JetBrainsMono-Regular.ttf" };
  Buffer buffer(argv[1]);
  Cursor cursor {};

  InitWindow(SCREEN_HEIGHT, SCREEN_WIDTH, "sharanga");

  if (!FileExists(font_path)) 
  {
    std::cout << "ERROR: Font not found! Current working dir: " << GetWorkingDirectory() << std::endl;
  }

  Font custom_font = LoadFontEx(font_path, FONT_SIZE + 1, 0, 0);
  SetTextureFilter(custom_font.texture, TEXTURE_FILTER_BILINEAR);

  while (!WindowShouldClose())
  {
    // 1. Handle Keyboard events
    int key { GetCharPressed() };

    while (key > 0)
    {
      if (key >= 32 && key <= 126)
      {
        buffer.insertChar(
            cursor.getLineIndex(),
            cursor.getColumnIndex(),
            static_cast<char>(key));
        
        cursor.moveCursorRight(buffer);
      }

      key = GetCharPressed();

    }

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) 
    {
      cursor.moveCursorRight(buffer);
    }
    else if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) 
    {
      cursor.moveCursorLeft(buffer);
    }
    else if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) 
    {
      cursor.moveCursorUp(buffer);
    }
    else if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN))
    {
      cursor.moveCursorDown(buffer);
    }
    else if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
    {
      std::size_t line_index { cursor.getLineIndex() };
      std::size_t column_index { cursor.getColumnIndex() };

      if (column_index > 0)
      {
        buffer.deleteChar(line_index, column_index);
        cursor.moveCursorLeft(buffer);
      }
      else if (line_index > 0)
      {
        cursor.moveCursorLeft(buffer);
        buffer.joinLines(line_index);
      }
    }
    else if (IsKeyPressed(KEY_ENTER) || IsKeyPressedRepeat(KEY_ENTER))
    {
      buffer.insertNewline(cursor.getLineIndex(), cursor.getColumnIndex());
      cursor.moveCursorDown(buffer);
    }

    // 2. Measure Text Dimensions.
    float max_line_width { 0.0f };
    for (const auto& line : buffer.lines_of_text)
    {
      Vector2 size = MeasureTextEx(custom_font, line.c_str(), FONT_SIZE, LETTER_SPACING);
      max_line_width = std::max(size.x, max_line_width);
    }
    
    // 3. Handle scrolling and clamp effects    
    float max_scroll_x {
      std::floor(
        std::max(0.0f, max_line_width - GetScreenWidth() + 10 + (5 * STEP_WIDTH)) / STEP_WIDTH
      ) * STEP_WIDTH
    };

    float total_text_height { 
      static_cast<float>(buffer.lines_of_text.size() * (FONT_SIZE + 2)) 
    };

    float max_scroll_y {
      std::max(0.0f, total_text_height - GetScreenHeight() + 10)
    };

    Vector2 mouse_scroll { GetMouseWheelMoveV() };
    x += mouse_scroll.x * STEP_WIDTH;
    y += mouse_scroll.y * (FONT_SIZE + 2);

    x = Clamp(x, 10 - max_scroll_x, 10);
    y = Clamp(y, 10 - max_scroll_y, 10);
  
    // 4. Render
    BeginDrawing();
      ClearBackground(BLACK);

      float line_y { y };
      for (const auto& line : buffer.lines_of_text)
      {
        DrawTextEx(custom_font, line.c_str(), Vector2 { x, line_y }, FONT_SIZE, LETTER_SPACING, WHITE);
        line_y += FONT_SIZE + 2;
      }

      cursor.drawCursor();
    EndDrawing();
  }

  UnloadFont(custom_font);
  CloseWindow();
  return 0;
}

