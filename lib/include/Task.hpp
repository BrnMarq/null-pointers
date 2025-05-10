#pragma once

#include <string>
#include <ctime>

#include "Types.hpp"

class Task
{
public:
  Task(time_t _estimated_time, time_t _dead_line, std::string _department, level _difficulty, std::string _title, std::string _requirements) noexcept;

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