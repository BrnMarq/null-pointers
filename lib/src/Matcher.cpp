#include "Matcher.hpp"

const Matcher::AgentVectorT &Matcher::get_agents() const noexcept
{
    return agents;
}
const Matcher::TaskVectorT &Matcher::get_tasks() const noexcept
{
    return tasks;
}
const Matcher::ATArcVectorT &Matcher::get_arcs() const noexcept
{
    return arcs;
}