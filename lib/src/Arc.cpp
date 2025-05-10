#include <Arc.hpp>

template <typename From, typename To>
Arc<From, To>::Arc(From _from, To _to, float _weight, size_t _flow, size_t _capacity) noexcept
    : from{_from}, to{_to}, weight{_weight}, flow{_flow}, capacity{_capacity} {};