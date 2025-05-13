#pragma once

#include <string>
#include <chrono>
#include <vector>

#include "Types.hpp"
#include "Task.hpp"

class Agent
{
public:
  Agent(std::chrono::hours _available_time, std::string _deparment, level _expertise, std::string _name) noexcept;

  const std::chrono::hours &get_available_time() const noexcept;

  const level &get_expertise() const noexcept;

  const std::string &get_name() const noexcept;

  const std::vector<Task> &get_assigned_tasks() const noexcept;

  void assign_task(Task &_task);

  bool is_available();

private:
  // * Logic Info
  std::chrono::hours available_time;
  // TODO how to get deparment to be enum
  std::string department;
  level expertise;
  // * Extra info
  std::string name;
  std::vector<Task> assigned_tasks;
};