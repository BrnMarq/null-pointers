#pragma once

#include <string>
#include <ctime>

#include "Types.hpp"

class Agent
{
public:
private:
  // * Logic Info
  time_t available_time;
  // TODO how to get deparment to be enum
  std::string department;
  level expertise;
  // * Extra info
  std::string name;
};