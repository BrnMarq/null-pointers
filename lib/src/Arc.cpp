#include <Arc.hpp>

template <class From, class To, class Weight, class Capacity>
Arc<From, To, Weight, Capacity>::Arc(From _from, To _to, size_t _flow) noexcept
    : from{_from}, to{_to}, flow{_flow}
{
  weight = Weight(from, to);
  capacity = Capacity(from, to);
};