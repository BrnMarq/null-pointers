#include <Task.hpp>

Task::Task(time_t _estimated_time, time_t _dead_line, std::string _department, level _difficulty, std::string _title, std::string _requirements) noexcept
    : estimated_time{_estimated_time}, dead_line{_dead_line}, department{_department}, difficulty{_difficulty}, title{_title}, requirements{_requirements} {};
