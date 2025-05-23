#pragma once

#include <vector>
#include <cmath>
#include <unordered_map>

#include "Agent.hpp"
#include "Arc.hpp"

class Weight
{
public:
  using Type = float;

  static constexpr Type ZERO = 0.0f;
  static constexpr Type MAX = std::numeric_limits<Type>::max();

  Type operator()(Agent agent, Task task) const noexcept
  {
    std::chrono::sys_days now{floor<std::chrono::days>(std::chrono::system_clock::now())};

    // a(Date + estimated - Dead line)+b.abs(Difficulty - Expertise): Tiempo de sobra
    float time_gap = std::chrono::duration_cast<std::chrono::hours>(task.get_dead_line() - now - task.get_estimated_time()).count();
    float difficulty_gap = std::abs(static_cast<int>(agent.get_expertise()) - static_cast<int>(task.get_difficulty()));
    return (Configs::time_gap_multiplier * time_gap) + (Configs::difficulty_gap_multiplier * difficulty_gap);
  }
};

class Capacity
{
public:
  using Type = size_t;

  static constexpr Type ZERO = 0;
  static constexpr Type MAX = std::numeric_limits<Type>::max();

  Type operator()(Agent agent, Task task) const noexcept
  {
    return task.get_estimated_time().count();
  }
};

class Matcher
{
public:
  using AgentVectorT = std::vector<Agent>;
  using TaskVectorT = std::vector<Task>;
  using ATArcVectorT = std::vector<Arc<Agent, Task, Weight, Capacity>>;
  using MatchT = std::unordered_map<Agent, TaskVectorT, Agent::Hash>;

  Matcher(AgentVectorT _agents, TaskVectorT _tasks);

  const AgentVectorT &get_agents() const noexcept;

  const TaskVectorT &get_tasks() const noexcept;

  const ATArcVectorT &get_arcs() const noexcept;

  void create_arcs() noexcept;

  bool agents_matched(std::unordered_map<Agent, size_t, Agent::Hash> agents_flow) const noexcept;

  bool tasks_matched(std::unordered_map<Task, size_t, Task::Hash> tasks_flow) const noexcept;

  void create_dot_file(std::unordered_map<Agent, size_t, Agent::Hash> source, std::unordered_map<Task, size_t, Task::Hash> sink, ATArcVectorT _arcs) noexcept;

  MatchT create_match() noexcept;

private:
  AgentVectorT agents;
  TaskVectorT tasks;
  ATArcVectorT arcs;
};