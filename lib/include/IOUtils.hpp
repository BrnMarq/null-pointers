#pragma once

#include <iostream>
#include <format>

#include "Matcher.hpp"

std::ostream &operator<<(std::ostream &out, const Agent &a)
{
    out << "Name: " << a.get_name() << "\n"
        << "Available time: " << a.get_available_time().count() << "h" << "\n"
        << "Departament: " << a.get_department() << "\n"
        << "Level: " << level_to_string(a.get_expertise());

    return out;
}

std::ostream &operator<<(std::ostream &out, const Task &t)
{
    std::chrono::year_month_day ymd{t.get_dead_line()};

    out << "Estimated time: " << t.get_estimated_time() << "\n"

        << "Dead line: "
        << static_cast<int>(ymd.year()) << "-"
        << static_cast<unsigned>(ymd.month()) << "-"
        << static_cast<unsigned>(ymd.day()) << "\n"

        << "Departament: " << t.get_department() << "\n"
        << "Difficulty: " << level_to_string(t.get_difficulty()) << "\n"
        << "Title: " << t.get_title() << "\n"
        << "Requirements: " << t.get_requirements() << "\n";

    return out;
}

template <class From, class To, class Weight, class Capacity>
std::ostream &operator<<(std::ostream &out, const Arc<From, To, Weight, Capacity> &a)
{
    out << "From: " << "\n"
        << a.get_from() << "\n"
        << "To: " << "\n"
        << a.get_to() << "\n"
        << "Capacity: " << a.get_capacity() << "\n"
        << "Flow: " << a.get_flow() << "\n"
        << "Weight: " << a.get_weigth() << "\n";

    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v)
{
    print_container(v, '[', ']', out);
    return out;
}

template <typename C>
void print_container(const C &c, char ldelim, char rdelim, std::ostream &out)
{
    out << ldelim;
    auto it = c.begin();

    if (it != c.end())
    {
        out << *it;
        ++it;
    }

    for (; it != c.end(); ++it)
    {
        out << ", " << *it;
    }

    out << rdelim;
}

void print_match(Matcher::MatchT match)
{
    if (match.size() == 0)
    {
        std::cout << "There's no match to do!" << std::endl;
        return;
    }

    for (const std::pair<Agent, std::vector<Task>> &m : match)
    {
        std::cout << m.first << std::endl;
        std::cout << "\nHas been assigned the following tasks\n"
                  << std::endl;
        for (const Task &task : m.second)
        {
            std::cout << task << std::endl;
        }
    }
}

void print_agents(std::vector<Agent> agents)
{
    if (agents.empty())
    {
        std::cout << "No agents to show!" << std::endl;
        std::cout << "Add some using 'add_agent' command" << std::endl;
        return;
    }

    for (auto &a : agents)
    {
        std::cout << a << std::endl;
        std::cout << "Assigned tasks: ";
        print_container(a.get_assigned_tasks(), '[', ']', std::cout);
        std::cout << '\n'
                  << std::endl;
    }
}

void print_tasks(std::vector<Task> tasks)
{
    if (tasks.empty())
    {
        std::cout << "No tasks to show!" << std::endl;
        std::cout << "Add some using 'add_task' command" << std::endl;
        return;
    }

    for (auto &t : tasks)
    {
        std::cout << t << std::endl;
    }
}