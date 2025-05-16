#include "Task.hpp"
#include "HashHelpers.hpp"

Task::Task(std::chrono::hours _estimated_time, std::chrono::sys_days _dead_line, std::string _department, level _difficulty, std::string _title, std::string _requirements) noexcept
    : estimated_time{_estimated_time}, dead_line{_dead_line}, department{_department}, difficulty{_difficulty}, title{_title}, requirements{_requirements} {};

size_t Task::Hash::operator()(const Task &t) const noexcept
{
    return hash_val(
        t.get_estimated_time().count(),
        t.get_dead_line().time_since_epoch().count(),
        t.get_department(),
        static_cast<int>(t.get_difficulty()),
        t.get_title(),
        t.get_requirements());
}

const std::chrono::hours &Task::get_estimated_time() const noexcept
{
    return estimated_time;
}

const std::chrono::sys_days &Task::get_dead_line() const noexcept
{
    return dead_line;
}

const std::string &Task::get_department() const noexcept
{
    return department;
}

const level &Task::get_difficulty() const noexcept
{
    return difficulty;
}

const std::string &Task::get_title() const noexcept
{
    return title;
}

const std::string &Task::get_requirements() const noexcept
{
    return requirements;
}

bool Task::operator==(const Task &t) const noexcept
{
    return (t.get_estimated_time() == estimated_time &&
            t.get_dead_line() == dead_line &&
            t.get_department() == department &&
            t.get_difficulty() == difficulty &&
            t.get_title() == title &&
            t.get_requirements() == requirements);
}
