#include <Arc.hpp>

template <class From, class To, class Weight, class Capacity>
Arc<From, To, Weight, Capacity>::Arc(From _from, To _to, size_t _flow) noexcept
    : from{_from}, to{_to}, flow{_flow}
{
  weight = Weight(from, to);
  capacity = Capacity(from, to);
};

const From &Arc::get_from() const noexcept
{
  return from;
}

const To &Arc::get_to() const noexcept
{
  return to;
}

const float &Arc::get_weigth() const noexcept
{
  return weight;
}

const size_t &Arc::get_capacity() const noexcept
{
  return capacity;
}

const size_t &Arc::get_flow() const noexcept
{
  return flow;
}