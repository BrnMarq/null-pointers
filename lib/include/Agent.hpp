#pragma once

#include <string>
#include <chrono>
#include <vector>

#include "Definitions.hpp"
#include "Task.hpp"

class Agent
{
public:
  Agent(std::chrono::hours _available_time, std::string _deparment, level _expertise, std::string _name) noexcept;

  struct Hash
  {
    size_t operator()(const Agent &a) const noexcept;
  };

  const std::chrono::hours &get_available_time() const noexcept;

  const std::string &get_department() const noexcept;

  const level &get_expertise() const noexcept;

  const std::string &get_name() const noexcept;

  const std::vector<Task> &get_assigned_tasks() const noexcept;

  void assign_task(Task &_task);

  void assign_task(std::vector<Task> &tasks);

  bool is_available();

  bool operator==(const Agent &a) const noexcept;

private:
  // * Logic Info
  std::chrono::hours available_time;
  std::string department;
  level expertise;
  // * Extra info
  std::string name;
  std::vector<Task> assigned_tasks;
};