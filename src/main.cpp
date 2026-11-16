#include <iostream>
#include <fstream>
#include <string>
#include <raylib.h>

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

std::string text {"The quick brown fox jumped \n over the lazy dog." };
const char* font_path { "../font/JetBrains_Mono/JetBrainsMono-VariableFont_wght.ttf" };

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "USAGE: editor [file name]" << '\n';
    return 0;
  }

  std::string text { readFile(argv[1]) };

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

