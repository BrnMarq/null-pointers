#pragma once
#include <stddef.h>
#include <limits>

template <class From, class To>
class DefaultWeight
{
public:
  using Type = float;

  static constexpr Type ZERO = 0.0f;
  static constexpr Type MAX = std::numeric_limits<Type>::max();

  Type operator()(From from, To to) const noexcept
  {
    return ZERO;
  }
};

template <class From, class To>
class DefaultCapacity
{
public:
  using Type = size_t;

  static constexpr Type ZERO = 0;
  static constexpr Type MAX = std::numeric_limits<Type>::max();

  Type operator()(From from, To to) const noexcept
  {
    return ZERO;
  }
};

template <class From, class To, class Weight = DefaultWeight<From, To>, class Capacity = DefaultCapacity<From, To>>
class Arc
{
public:
  Arc(From _from, To _to, size_t _flow) noexcept;

  void push_flow(size_t &_flow) noexcept;

private:
  From from;
  To to;
  float weight;
  size_t flow;
  size_t capacity;
};