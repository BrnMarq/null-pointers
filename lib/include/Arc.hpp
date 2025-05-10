#pragma once

template <typename From, typename To>
class Arc
{
public:
  Arc(From _from, To _to, float _weight, size_t _flow, size_t _capacity) noexcept;

private:
  From from;
  To to;
  float weight;
  size_t flow;
  size_t capacity;
};