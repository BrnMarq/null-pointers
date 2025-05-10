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

private:
  AgentVectorT agents;
  TaskVectorT tasks;
  ATArcVectorT arcs;
};