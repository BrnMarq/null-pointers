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
            if (agent.get_department() != task.get_department() || agent.get_available_time() < task.get_estimated_time())
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

bool Matcher::agents_matched(std::unordered_map<Agent, size_t, Agent::Hash> agents_flow) const noexcept
{
    if (agents.size() != agents_flow.size())
    {
        return false;
    }
    for (const std::pair<Agent, size_t> agent : agents_flow)
    {
        if (agent.second != agent.first.get_available_time().count())
        {
            return false;
        }
    }
    return true;
}

bool Matcher::tasks_matched(std::unordered_map<Task, size_t, Task::Hash> tasks_flow) const noexcept
{
    if (tasks.size() != tasks_flow.size())
    {
        return false;
    }
    for (const std::pair<Task, size_t> task : tasks_flow)
    {
        if (task.second != task.first.get_estimated_time().count())
        {
            return false;
        }
    }
    return true;
}

Matcher::MatchT Matcher::create_match() noexcept
{
    MatchT result;
    create_arcs();
    std::unordered_map<Agent, size_t, Agent::Hash> source;
    std::unordered_map<Task, size_t, Task::Hash> sink;
    for (ATArcVectorT::value_type &arc : arcs)
    {
        Agent agent = arc.get_from();
        Task task = arc.get_to();
        if (agent.get_available_time().count() - source[agent] < arc.get_remaining_capacity())
        {
            continue;
        }
        size_t max_flow_push = std::min(
            {agent.get_available_time().count() - source[agent],
             task.get_estimated_time().count() - sink[task],
             arc.get_remaining_capacity()});

        if (max_flow_push == 0)
        {
            continue;
        }
        source[agent] += max_flow_push;
        arc.push_flow(max_flow_push);
        sink[task] += max_flow_push;

        result[agent].push_back(task);
        if (agents_matched(source) || tasks_matched(sink))
        {
            break;
        }
    }

    return result;
}

void Matcher::print_match(MatchT match) const noexcept
{
    for (const std::pair<Agent, std::vector<Task>> &m : match)
    {
        std::cout << m.first << std::endl;
        std::cout << "Has been assigned the following tasks" << std::endl;
        for (const Task &task : m.second)
        {
            std::cout << task << std::endl;
        }
    }
}
