#ifndef __BUFFER_H
#define __BUFFER_H

#include <vector>
#include <string>

class Buffer
{
public:
  std::vector<std::string> lines_of_text;
  Buffer(std::string file_name);
  void insertChar(std::size_t line_index, std::size_t position, char character);
  void deleteChar(std::size_t line_index, std::size_t position);
  void insertNewline(std::size_t line_index, std::size_t position);
  void joinLines(std::size_t line_index);
};

#endif

