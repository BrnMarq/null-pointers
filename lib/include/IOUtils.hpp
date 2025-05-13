#include <iostream>

#include "Matcher.hpp"

// * These are for test purposes, I suggest you to declare the functions in this file

// TODO
std::ostream &operator<<(std::ostream &out, Agent *a);

// TODO
std::ostream &operator<<(std::ostream &out, Task *t);

// TODO
template <class From, class To, class Weight, class Capacity>
std::ostream &operator<<(std::ostream &out, Arc<From, To, Weight, Capacity> *a);
