#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <raylib.h>
#include <raymath.h>

#include "cursor.h"
#include "config.h"

constexpr float STEP_WIDTH {
  (static_cast<float>(FONT_SIZE) / (FONT_SIZE + 1) * 9.0f + LETTER_SPACING)
};

std::string readFile(std::string file_name);

std::string readFile(std::string file_name)
{
  std::ifstream in_reader { file_name };
  if (!in_reader)
  {
    std::cerr << "Unable to open the file." << '\n';
    return "";
  }

  std::string text((std::istreambuf_iterator<char>(in_reader)),
      std::istreambuf_iterator<char>());


  return text;
}

int main(int argc, char* argv[])
{
  float x { 10 };
  float y { 10 };

  Cursor cursor {};

  if (argc != 2)
  {
    std::cout << "USAGE: editor [file name]" << '\n';
    return 0;
  }

  const char* font_path { "../font/JetBrains_Mono/static/JetBrainsMono-Regular.ttf" };
  std::string text { readFile(argv[1]) };

  InitWindow(SCREEN_HEIGHT, SCREEN_WIDTH, "sharanga");

  if (!FileExists(font_path)) 
  {
    std::cout << "ERROR: Font not found! Current working dir: " << GetWorkingDirectory() << std::endl;
  }

  Font custom_font = LoadFontEx(font_path, FONT_SIZE + 1, 0, 0);
  SetTextureFilter(custom_font.texture, TEXTURE_FILTER_BILINEAR);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT))
      cursor.moveCursorRight();
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT))
      cursor.moveCursorLeft();
    if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP))
      cursor.moveCursorUp();
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN))
      cursor.moveCursorDown();
    
    Vector2 text_size { MeasureTextEx(custom_font, text.c_str(), FONT_SIZE, LETTER_SPACING) };

    // std::cout << "Text size " << text_size.x << " " << text_size.y << '\n';
    
    float max_scroll_x { 
      std::floor(
        std::max(0.0f, (text_size.x - GetScreenWidth() + 10 + (5 * STEP_WIDTH)) / STEP_WIDTH) * STEP_WIDTH)
    };
    
    float max_scroll_y {
      std::max(0.0f, text_size.y -  2 * FONT_SIZE)
    };

    
    Vector2 mouse_scroll { GetMouseWheelMoveV() };
    x += mouse_scroll.x * STEP_WIDTH;
    y += mouse_scroll.y * (FONT_SIZE + 2);

    x = Clamp(x, 10 - max_scroll_x, 10);
    y = Clamp(y, 10 - max_scroll_y, 10);

    DrawTextEx(custom_font, text.c_str(), Vector2{ x, y }, FONT_SIZE, LETTER_SPACING, WHITE);
    cursor.drawCursor();
    EndDrawing();
  }

  UnloadFont(custom_font);
  CloseWindow();
  return 0;
}

