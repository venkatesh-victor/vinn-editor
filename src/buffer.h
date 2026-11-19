#ifndef __BUFFER_H
#define __BUFFER_H

#include <vector>
#include <string>

class Buffer
{
public:
  std::vector<std::string> lines_of_text;
  Buffer(std::string file_name);
  void insertChar(int line_index, int position, char character);
  void deleteChar(int line_index, int position);
  void insertNewline(int line_index, int position);
  void joinLines(int line_index);
};

#endif

