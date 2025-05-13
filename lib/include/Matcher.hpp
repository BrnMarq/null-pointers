#pragma once

#include <vector>

#include "Agent.hpp"
#include "Task.hpp"
#include "Arc.hpp"

class Weight
{
public:
  using Type = float;

  static constexpr Type ZERO = 0.0f;
  static constexpr Type MAX = std::numeric_limits<Type>::max();

  Type operator()(Agent agent, Task task) const noexcept
  {
    // std::chrono::time_point now{std::chrono::system_clock::now()};
    // std::chrono::year_month_day now_date{std::chrono::floor<std::chrono::days>(now)};
    // // a(Date + estimated - Dead line)+b.abs(Difficulty - Expertise): Tiempo de sobra
    // std::chrono::year_month_day time_gap = (now_date - task.get_dead_line());
    return ZERO;
  }
};

class Matcher
{
public:
  using AgentVectorT = std::vector<Agent>;
  using TaskVectorT = std::vector<Task>;
  using ATArcVectorT = std::vector<Arc<Agent, Task>>;
  using MatchT = std::unordered_map<Agent, TaskVectorT>;

  const AgentVectorT &get_agents() const noexcept;

  const TaskVectorT &get_tasks() const noexcept;

  const ATArcVectorT &get_arcs() const noexcept;

  // Todo
  MatchT create_match() noexcept;

  void print_match(MatchT match) const noexcept;

private:
  AgentVectorT agents;
  TaskVectorT tasks;
  ATArcVectorT arcs;
};