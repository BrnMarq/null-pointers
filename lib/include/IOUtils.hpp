#pragma once

#include <iostream>
#include <format>

#include "Matcher.hpp"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"
#define BOLD_CYAN "\033[1;36m"
#define BOLD_MAGENTA "\033[1;35m"

std::ostream &operator<<(std::ostream &out, const Agent &a)
{
    out << BOLD_CYAN << "Name: " << RESET << a.get_name() << "\n"
        << BOLD_CYAN << "Available time: " << RESET << a.get_available_time().count() << "h" << "\n"
        << BOLD_CYAN << "Departament: " << RESET << a.get_department() << "\n"
        << BOLD_CYAN << "Level: " << RESET << level_to_string(a.get_expertise());

    return out;
}

std::ostream &operator<<(std::ostream &out, const Task &t)
{
    std::chrono::year_month_day ymd{t.get_dead_line()};

    out << BOLD_CYAN << "Estimated time: " << RESET << t.get_estimated_time() << "\n"

        << BOLD_CYAN << "Dead line: " << RESET
        << static_cast<int>(ymd.year()) << "-"
        << static_cast<unsigned>(ymd.month()) << "-"
        << static_cast<unsigned>(ymd.day()) << "\n"

        << BOLD_CYAN << "Departament: " << RESET << t.get_department() << "\n"
        << BOLD_CYAN << "Difficulty: " << RESET << level_to_string(t.get_difficulty()) << "\n"
        << BOLD_CYAN << "Title: " << RESET << t.get_title() << "\n"
        << BOLD_CYAN << "Requirements: " << RESET << t.get_requirements() << "\n";

    return out;
}

template <class From, class To, class Weight, class Capacity>
std::ostream &operator<<(std::ostream &out, const Arc<From, To, Weight, Capacity> &a)
{
    out << BOLD_CYAN << "From: " << RESET << "\n"
        << a.get_from() << "\n"
        << BOLD_CYAN << "To: " << RESET << "\n"
        << a.get_to() << "\n"
        << BOLD_CYAN << "Capacity: " << RESET << a.get_capacity() << "\n"
        << BOLD_CYAN << "Flow: " << RESET << a.get_flow() << "\n"
        << BOLD_CYAN << "Weight: " << RESET << a.get_weigth() << "\n";

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
    if (match.empty())
    {
        std::cout << YELLOW << "There's no match to make!" << RESET << std::endl;
        return;
    }

    for (const std::pair<Agent, std::vector<Task>> &m : match)
    {
        std::cout << "------------------------------------------------------------\n"
                  << std::endl;
        std::cout << m.first << std::endl;
        std::cout << CYAN << "\nHas been assigned the following tasks\n"
                  << RESET << std::endl;
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
        std::cout << YELLOW << "No agents to show!" << RESET << std::endl;
        std::cout << "Add some using 'add_agent' command" << std::endl;
        return;
    }

    for (auto &a : agents)
    {
        std::cout << a << std::endl;
        std::cout << BOLD_CYAN << "Assigned tasks: " << RESET;
        print_container(a.get_assigned_tasks(), '[', ']', std::cout);
        std::cout << '\n'
                  << std::endl;
    }
}

void print_tasks(std::vector<Task> tasks)
{
    if (tasks.empty())
    {
        std::cout << YELLOW << "No tasks to show!" << RESET << std::endl;
        std::cout << "Add some using 'add_task' command" << std::endl;
        return;
    }

    for (auto &t : tasks)
    {
        std::cout << t << std::endl;
    }
}