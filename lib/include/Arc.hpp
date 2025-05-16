#pragma once

#include <stddef.h>
#include <limits>

#include "Exception.hpp"

template <class From, class To>
class DefaultWeight
{
public:
  using Type = float;

  static constexpr Type ZERO = 0.0f;
  static constexpr Type MAX = std::numeric_limits<Type>::max();

  Type operator()() const noexcept
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

  Type operator()() const noexcept
  {
    return ZERO;
  }
};

template <class From, class To, class Weight = DefaultWeight<From, To>, class Capacity = DefaultCapacity<From, To>>
class Arc
{
public:
  Arc(From _from, To _to, size_t _flow) noexcept;
  Arc(From _from, To _to) noexcept;

  const From &get_from() const noexcept;

  const To &get_to() const noexcept;

  const float &get_weigth() const noexcept;

  const size_t &get_capacity() const noexcept;

  const size_t &get_flow() const noexcept;

  const size_t get_remaining_capacity() const noexcept;

  void push_flow(size_t &_flow) noexcept;

private:
  From from;
  To to;
  float weight;
  size_t flow;
  size_t capacity;
};

template <class From, class To, class Weight, class Capacity>
Arc<From, To, Weight, Capacity>::Arc(From _from, To _to, size_t _flow) noexcept
    : from{_from}, to{_to}, flow{_flow}
{
  weight = Weight()(_from, _to);
  capacity = Capacity()(_from, _to);
}
template <class From, class To, class Weight, class Capacity>
Arc<From, To, Weight, Capacity>::Arc(From _from, To _to) noexcept
    : from{_from}, to{_to}, flow{0}
{
  weight = Weight()(_from, _to);
  capacity = Capacity()(_from, _to);
};

template <class From, class To, class Weight, class Capacity>
const From &Arc<From, To, Weight, Capacity>::get_from() const noexcept
{
  return from;
}

template <class From, class To, class Weight, class Capacity>
const To &Arc<From, To, Weight, Capacity>::get_to() const noexcept
{
  return to;
}

template <class From, class To, class Weight, class Capacity>
const float &Arc<From, To, Weight, Capacity>::get_weigth() const noexcept
{
  return weight;
}

template <class From, class To, class Weight, class Capacity>
const size_t &Arc<From, To, Weight, Capacity>::get_capacity() const noexcept
{
  return capacity;
}

template <class From, class To, class Weight, class Capacity>
const size_t &Arc<From, To, Weight, Capacity>::get_flow() const noexcept
{
  return flow;
}

template <class From, class To, class Weight, class Capacity>
inline const size_t Arc<From, To, Weight, Capacity>::get_remaining_capacity() const noexcept
{
  return capacity - flow;
}

template <class From, class To, class Weight, class Capacity>
void Arc<From, To, Weight, Capacity>::push_flow(size_t &_flow) noexcept
{
  if (_flow > (capacity - flow))
  {
    throw OverflowException(_flow, flow, capacity);
  }
  flow += _flow;
}
