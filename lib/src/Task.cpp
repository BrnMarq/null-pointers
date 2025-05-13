#include <Task.hpp>

Task::Task(std::chrono::hours _estimated_time, std::chrono::sys_days _dead_line, std::string _department, level _difficulty, std::string _title, std::string _requirements) noexcept
    : estimated_time{_estimated_time}, dead_line{_dead_line}, department{_department}, difficulty{_difficulty}, title{_title}, requirements{_requirements} {};

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