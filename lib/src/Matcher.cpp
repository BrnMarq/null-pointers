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

void Matcher::create_arcs() noexcept
{
    for (const Agent &agent : agents)
    {
        for (const Task &task : tasks)
        {
            if (agent.get_department() != task.get_department() &&
                agent.get_available_time() < task.get_estimated_time())
            {
                continue;
            }
            ATArcVectorT::value_type arc(agent, task);
            arcs.push_back(arc);
        }
    }
    std::sort(
        arcs.begin(),
        arcs.end(),
        [](const ATArcVectorT::value_type &arc1, const ATArcVectorT::value_type &arc2)
        {
            return arc1.get_weigth() < arc2.get_weigth();
        });
}

Matcher::MatchT Matcher::create_match() noexcept
{
    create_arcs();
    return MatchT();
}
