#include "Matcher.hpp"
#include "IOUtils.hpp"

Matcher::Matcher(AgentVectorT _agents, TaskVectorT _tasks) : agents{_agents}, tasks{_tasks}
{
}

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

Matcher::MatchT Matcher::create_match() noexcept
{
    MatchT match;
    ATArcVectorT arcs;
    for (const Agent &agent : agents)
    {
        for (const Task &task : tasks)
        {
            ATArcVectorT::value_type arc(agent, task);
            arcs.push_back(arc);
            std::cout << arc << std::endl;
            match[agent].push_back(task);
        }
    }
    return MatchT();
}
