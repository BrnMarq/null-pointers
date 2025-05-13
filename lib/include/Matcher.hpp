#include <vector>

#include "Agent.hpp"
#include "Task.hpp"
#include "Arc.hpp"

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

  MatchT create_match() noexcept;

private:
  AgentVectorT agents;
  TaskVectorT tasks;
  ATArcVectorT arcs;
};