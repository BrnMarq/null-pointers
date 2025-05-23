#include <algorithm>
#include <fstream>

#include "Matcher.hpp"

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
            TaskVectorT assigned_tasks = agent.get_assigned_tasks();
            bool task_found = std::find(assigned_tasks.begin(), assigned_tasks.end(), task) != assigned_tasks.end();
            size_t flow = task_found ? task.get_estimated_time().count() : 0;
            ATArcVectorT::value_type arc(agent, task, flow);
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

void Matcher::create_dot_file(std::unordered_map<Agent, size_t, Agent::Hash> source, std::unordered_map<Task, size_t, Task::Hash> sink, ATArcVectorT _arcs) noexcept
{
    std::ofstream dot_file("./resources/graph/result.dot");
    dot_file << "digraph FlowNetwork { \n\
        rankdir=\"LR\";  // Left-to-right layout \n\
        node [ fontname=Arial, fontcolor=blue, fontsize=11];\n\
        edge [ fontname=Arial, fontsize=8 ];\n\
        \n\
        // Nodes \n\
        S [label=\"s\", shape=circle, style=filled, color=lightblue];\n\
        T [label=\"t\", shape=circle, style=filled, color=lightblue];\n\
        \n\
        ";
    for (const Agent &agent : agents)
    {
        dot_file << agent.get_name()[0] << " [shape=circle];\n\ ";
        source[agent];
    }
    for (const Task &task : tasks)
    {
        dot_file << task.get_title()[0] << " [shape=circle];\n\ ";
        sink[task];
    }
    for (const ATArcVectorT::value_type &arc : _arcs)
    {
        dot_file << arc.get_from().get_name()[0] << "->" << arc.get_to().get_title()[0];
        // dot_file << "[label=\"" << arc.get_flow() << "/" << arc.get_capacity() << "\", xlabel=\"" << arc.get_weigth() << "\"];\n\ ";
        dot_file << "[label=\"" << arc.get_flow() << "/" << arc.get_capacity() << "\"];\n\ ";
    }
    for (const std::pair<Agent, size_t> source_arc : source)
    {
        dot_file << "S->" << source_arc.first.get_name()[0];
        dot_file << "[label=\"" << source_arc.second << "/" << source_arc.first.get_available_time().count() << "\"];\n\ ";
    }
    for (const std::pair<Task, size_t> sink_arc : sink)
    {
        dot_file << sink_arc.first.get_title()[0] << "->T";
        dot_file << "[label=\"" << sink_arc.second << "/" << sink_arc.first.get_estimated_time().count() << "\"];\n\ ";
    }
    dot_file << "}";
    dot_file.close();
}

Matcher::MatchT Matcher::create_match() noexcept
{
    MatchT result;
    create_arcs();
    std::unordered_map<Agent, size_t, Agent::Hash> source;
    std::unordered_map<Task, size_t, Task::Hash> sink;
    for (const Agent &agent : agents)
    {
        for (const Task &task : agent.get_assigned_tasks())
        {
            source[agent] += task.get_estimated_time().count();
            sink[task] += task.get_estimated_time().count();
        }
    }
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

    create_dot_file(source, sink, arcs);

    return result;
}
