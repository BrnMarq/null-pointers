#include <vector>

#include "Agent.hpp"
#include "Task.hpp"
#include "Arc.hpp"

class Matcher
{
public:
  using AgentVector = std::vector<Agent>;
  using TaskVector = std::vector<Task>;
  using ATArcVector = std::vector<Arc<Agent, Task>>;

private:
  AgentVector agents;
  TaskVector tasks;
  ATArcVector arcs;
};