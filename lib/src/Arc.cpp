#include <Arc.hpp>

template <class From, class To, class Weight, class Capacity>
Arc<From, To, Weight, Capacity>::Arc(From _from, To _to, size_t _flow) noexcept
    : from{_from}, to{_to}, flow{_flow}
{
  weight = Weight(from, to);
  capacity = Capacity(from, to);
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