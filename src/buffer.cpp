#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "buffer.h"

Buffer::Buffer(std::string file_name)
{
  std::ifstream file { file_name };
  std::string line;

  if (!file)
  {
    std::cerr << "Unable to open the file." << '\n';
  }

  if (file.is_open())
  {
    while (std::getline(file, line))
    {
      this->lines_of_text.push_back(line);
    }
  }
}

void Buffer::insertChar(int line_index, int position, char character)
{
  std::string line = this->lines_of_text[line_index];
  line.insert(line.begin() + position, character);
}

void Buffer::deleteChar(int line_index, int position)
{
  std::string line = this->lines_of_text[line_index];
  line.erase(line.begin() + position);
}

void Buffer::insertNewline(int line_index, int position)
{
  std::string line = this->lines_of_text[line_index];
  std::string extracted = line.substr(position + 1);
  line.erase(position + 1);
  this->lines_of_text.insert(lines_of_text.begin() + position + 1, extracted);
}

void Buffer::joinLines(int line_index)
{
  std::string prev_line = this->lines_of_text[line_index - 1];
  prev_line.append(this->lines_of_text[line_index]);
  this->lines_of_text.erase(lines_of_text.begin() + line_index);
}

