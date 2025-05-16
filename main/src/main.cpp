#include <iostream>
#include <fstream>
#include <typeinfo>
#include <chrono>

#include "json.hpp"
#include <Matcher.hpp>
#include <Definitions.hpp>
#include <Exception.hpp>

using json = nlohmann::json;

std::chrono::sys_days string_to_date(const std::string &date)
{
  std::istringstream iss(date);

  int year, month, day;
  char sep;
  iss >> year >> sep >> month >> sep >> day;

  return std::chrono::sys_days{std::chrono::year(year) / std::chrono::month(month) / std::chrono::day(day)};
}

int main(int argc, char *argv[])
{
  std::filesystem::path pwd = std::filesystem::current_path();

  if (argc > 1)
  {
    std::string arg(argv[1]);

    if (!is_valid_argument(arg))
    {
      throw InvalidCommandException(arg);
    }

    if (arg == "np")
    {
      std::filesystem::path path = pwd / ".np";

      if (!std::filesystem::exists(path))
      {
        std::filesystem::create_directory(path);
      }
    }
  }

  std::ifstream file_agents(pwd / ".np/agents.json");
  std::ifstream file_task(pwd / ".np/tasks.json");

  json agents = json::parse(file_agents);
  json tasks = json::parse(file_task);

  std::vector<Agent> agents_list;
  std::vector<Task> task_list;

  for (const auto &ag : agents)
  {
    std::chrono::hours _available_time(ag["available_time"].get<int>());
    std::string _deparment = ag["department"].get<std::string>();

    if (!department_exists(_deparment))
    {
      Departments::departments.push_back(_deparment);
    }

    level _level = get_level_from_string(ag["expertise"].get<std::string>());
    std::string _name = ag["name"].get<std::string>();

    Agent agent(_available_time, _deparment, _level, _name);

    agents_list.push_back(agent);
  }

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

  Matcher matcher(agents_list, task_list);
  Matcher::MatchT match = matcher.create_match();
  matcher.print_match(match);

  return EXIT_SUCCESS;
}