#include "Agent.hpp"
#include "HashHelpers.hpp"

Agent::Agent(std::chrono::hours _available_time, std::string _deparment, level _expertise, std::string _name) noexcept
    : available_time{_available_time}, department{_deparment}, expertise{_expertise}, name{_name} {};

size_t Agent::Hash::operator()(const Agent &v) const noexcept
{
    return hash_val(v.available_time.count(), v.department, static_cast<int>(v.expertise), v.name);
}

const std::chrono::hours &Agent::get_available_time() const noexcept
{
    return available_time;
}

const level &Agent::get_expertise() const noexcept
{
    return expertise;
}

const std::string &Agent::get_name() const noexcept
{
    return name;
}

const std::vector<Task> &Agent::get_assigned_tasks() const noexcept
{
    return assigned_tasks;
}

void Agent::assign_task(Task &_task)
{
    assigned_tasks.push_back(_task);
}

bool Agent::is_available()
{
    return available_time > std::chrono::hours(0);
}
