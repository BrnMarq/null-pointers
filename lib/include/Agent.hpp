#include <string>
#include <ctime>

#include "Types.hpp"

class Agent
{
public:
private:
  std::string name;
  time_t available_time;
  // TODO how to get deparment to be enum
  std::string department;
  level expertise;
};