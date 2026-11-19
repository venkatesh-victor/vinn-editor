#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>

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

  if (this->lines_of_text.empty())
  {
    lines_of_text.emplace_back("");
  }
}

void Buffer::insertChar(std::size_t line_index, std::size_t position, char character)
{
  std::string& line = this->lines_of_text[line_index];
  line.insert(line.begin() + position, character);
}

void Buffer::deleteChar(std::size_t line_index, std::size_t position)
{
  std::string& line = this->lines_of_text[line_index];

  if (position == 0 || position > line.size())
    return;

  line.erase(line.begin() + position - 1);
}

void Buffer::insertNewline(std::size_t line_index, std::size_t position)
{
  std::string& line = this->lines_of_text[line_index];
  std::string extracted = line.substr(position);
  line.erase(position);
  this->lines_of_text.insert(lines_of_text.begin() +  line_index + 1, extracted);
}

void Buffer::joinLines(std::size_t line_index)
{
  std::string& prev_line = this->lines_of_text[line_index - 1];
  prev_line.append(this->lines_of_text[line_index]);
  this->lines_of_text.erase(lines_of_text.begin() + line_index);
}

