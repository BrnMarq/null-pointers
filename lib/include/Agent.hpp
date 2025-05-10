#pragma once

#include <string>
#include <ctime>
#include <vector>

#include "Types.hpp"
#include "Task.hpp"

class Agent
{
public:
  Agent(time_t _available_time, std::string _deparment, level _expertise, std::string _name) noexcept;

private:
  // * Logic Info
  time_t available_time;
  // TODO how to get deparment to be enum
  std::string department;
  level expertise;
  // * Extra info
  std::string name;
  std::vector<Task> assigned_tasks;
};