#include <iostream>
#include <raylib.h>

std::string text = "The quick brown fox jumped over the lazy dog.";
const char* font_path = "../font/JetBrains_Mono/JetBrainsMono-VariableFont_wght.ttf";

int main()
{
  InitWindow(600, 600, "sharanga");

  if (!FileExists(font_path)) 
  {
    std::cout << "ERROR: Font not found! Current working dir: " << GetWorkingDirectory() << std::endl;
  }

  Font custom_font = LoadFontEx(font_path, 20, 0, 0);
  SetTextureFilter(custom_font.texture, TEXTURE_FILTER_BILINEAR);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTextEx(custom_font, text.c_str(), Vector2{ 10, 10 }, 19, -0.5, WHITE);
    EndDrawing();
  }

  UnloadFont(custom_font);
  CloseWindow();
  return 0;
}
