#pragma once

#include <string>
#include <chrono>

#include "Types.hpp"

class Task
{
public:
  Task(std::chrono::hours _estimated_time, std::chrono::sys_days _dead_line, std::string _department, level _difficulty, std::string _title, std::string _requirements) noexcept;

  const std::chrono::hours &get_estimated_time() const noexcept;

  const std::chrono::sys_days &get_dead_line() const noexcept;

  const std::string &get_department() const noexcept;

  const level &get_difficulty() const noexcept;

  const std::string &get_title() const noexcept;

  const std::string &get_requirements() const noexcept;

private:
  // * Logic info
  std::chrono::hours estimated_time;
  std::chrono::sys_days dead_line;
  // TODO how to get deparment to be enum
  std::string department;
  level difficulty;

  // * Extra info
  std::string title;
  std::string requirements;
};