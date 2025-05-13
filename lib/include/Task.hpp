#pragma once

#include <string>
#include <ctime>

#include "Types.hpp"

class Task
{
public:
  Task(time_t _estimated_time, time_t _dead_line, std::string _department, level _difficulty, std::string _title, std::string _requirements) noexcept;

  const time_t &get_estimated_time() const noexcept;

  const time_t &get_dead_line() const noexcept;

  const std::string &get_department() const noexcept;

  const level &get_difficulty() const noexcept;

  const std::string &get_title() const noexcept;

  const std::string &get_requirements() const noexcept;

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