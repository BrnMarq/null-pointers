#include <iostream>
#include <format>

#include "Matcher.hpp"

std::ostream &operator<<(std::ostream &out, Agent *a);

std::ostream &operator<<(std::ostream &out, Task *t);

template <class From, class To, class Weight, class Capacity>
std::ostream &operator<<(std::ostream &out, Arc<From, To, Weight, Capacity> *a);

std::ostream &operator<<(std::ostream &out, Agent *a)
{
    out << "Name: " << a->get_name() << "\n"
        << "Available time: " << a->get_available_time().count() << "\n"
        << "Departament: " << a->get_department() << "\n"
        << "Level: " << level_to_string(a->get_expertise()) << "\n";

    return out;
}

std::ostream &operator<<(std::ostream &out, Task *t)
{
    std::chrono::year_month_day ymd{t->get_dead_line()};

    out << "Estimated time: " << t->get_estimated_time() << "\n"

        << "Dead line: "
        << static_cast<int>(ymd.year()) << "-"
        << static_cast<unsigned>(ymd.month()) << "-"
        << static_cast<unsigned>(ymd.day()) << "\n"

        << "Departament: " << t->get_department() << "\n"
        << "Difficulty: " << level_to_string(t->get_difficulty()) << "\n"
        << "Title: " << t->get_title() << "\n"
        << "Requirements: " << t->get_requirements() << "\n";

    return out;
}

template <class From, class To, class Weight, class Capacity>
std::ostream &operator<<(std::ostream &out, Arc<From, To, Weight, Capacity> *a)
{
    out << "From: " << a->get_flow() << "\n"
        << "To: " << a->get_to() << "\n"
        << "Capacity: " << a->get_capacity() << "\n"
        << "Flow: " << a->get_flow() << "\n"
        << "Weight: " << a->get_weigth() << "\n";

    return out;
}