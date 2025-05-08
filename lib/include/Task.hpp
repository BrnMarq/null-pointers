#pragma once

#include <string>
#include <ctime>

#include "Types.hpp"

class Task
{
public:
private:
  // * Logic info
  time_t estimated_time;
  time_t dead_line;
  // TODO how to get deparment to be enum
  std::string department;
  level difficulty;

  // * Extra info
  std::string title;
  std::string requirements;
};