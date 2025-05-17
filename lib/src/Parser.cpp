#include "Parser.hpp"
#include "json.hpp"

Parser::Parser() noexcept
{
}

Parser::~Parser()
{
}

std::chrono::sys_days Parser::string_to_date(const std::string &date) const noexcept
{
  std::istringstream iss(date);

  int year, month, day;
  char sep;
  iss >> year >> sep >> month >> sep >> day;

  return std::chrono::sys_days{std::chrono::year(year) / std::chrono::month(month) / std::chrono::day(day)};
};

std::vector<Agent> Parser::get_agents() const
{

  std::ifstream file_agents(files_path / "agents.json");

  nlohmann::json agents = nlohmann::json::parse(file_agents);

  std::vector<Agent> agents_list;

  for (const auto &a : agents)
  {
    std::chrono::hours _available_time(a["available_time"].get<int>());
    std::string _deparment = a["department"].get<std::string>();

    if (!department_exists(_deparment))
    {
      Departments::departments.push_back(_deparment);
    }

    level _level = get_level_from_string(a["expertise"].get<std::string>());
    std::string _name = a["name"].get<std::string>();

    Agent agent(_available_time, _deparment, _level, _name);

    agents_list.push_back(agent);
  }

  return agents_list;
};

std::vector<Task> Parser::get_tasks() const
{
  std::ifstream file_task(pwd / ".np/tasks.json");

  nlohmann::json tasks = nlohmann::json::parse(file_task);

  std::vector<Task> task_list;

  for (const auto &tsk : tasks)
  {
    std::chrono::hours _estimated_time(tsk["estimated_time"].get<int>());
    std::chrono::sys_days _dead_line = string_to_date(tsk["dead_line"].get<std::string>());
    std::string _deparment = tsk["department"].get<std::string>();

    level _difficulty = get_level_from_string(tsk["difficulty"].get<std::string>());

    std::string _title = tsk["title"].get<std::string>();

    Task task(_estimated_time, _dead_line, _deparment, _difficulty, _title, "");

    task_list.push_back(task);
  };

  return task_list;
};