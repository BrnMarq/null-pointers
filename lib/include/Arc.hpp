#pragma once

#include "Agent.hpp"
#include "Task.hpp"

template <typename From, typename To>
class Arc
{
public:
private:
  From from;
  To to;
  size_t weight;
  size_t flow;
  size_t capacity;
};