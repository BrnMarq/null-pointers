#include <iostream>
#include <fstream>
#include <typeinfo>
#include <chrono>

#include "json.hpp"
#include <Agent.hpp>
#include <Task.hpp>
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
  if (argc > 1)
  {
    std::string arg(argv[1]);

    if (!is_valid_argument(arg))
    {
      throw InvalidCommandException(arg);
    }

    if (arg == "np")
    {
      std::filesystem::path path = "../../.np";

      if (!std::filesystem::exists(path))
      {
        std::filesystem::create_directory(path);
      }
    }
  }

  std::ifstream file_agents("../../.np/agents.json");
  std::ifstream file_task("../../.np/tasks.json");

  json agents = json::parse(file_agents);
  json tasks = json::parse(file_task);

  std::vector<Agent> agents_list;
  std::vector<Task> task_list;

  // std::string fecha = "2025-08-09";
  // auto y = string_to_date(fecha);

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

  //  std::chrono::hours estimated_time;
  // std::chrono::sys_days dead_line;
  // // TODO how to get deparment to be enum
  // std::string department;
  // level difficulty;

  // // * Extra info
  // std::string title;
  // std::string requirements;

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

  // std::cout << agents_list.size() << std::endl;
  // std::cout << task_list.size() << std::endl;
  // std::cout << Departments::departments.size() << std::endl;

  std::chrono::sys_days now{floor<std::chrono::days>(std::chrono::system_clock::now())};

  // std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};
  std::chrono::hours estimated_time{12};
  std::cout << now << std::endl;
  auto later = now + estimated_time;
  std::cout << later << std::endl;

  std::chrono::sys_days tomorrow{std::chrono::year(2025) / std::chrono::month(5) / std::chrono::day(14)};
  std::cout << tomorrow << std::endl;

  std::cout << std::chrono::duration_cast<std::chrono::hours>(tomorrow - later).count() << std::endl;

  // // ymd = ymd + std::chrono::months(4);

  // // ymd = ymd - std::chrono::years(10);
  // std::cout << "Current Year: " << static_cast<int>(ymd.year()) << ", "
  //                                                                  "Month: "
  //           << static_cast<unsigned>(ymd.month()) << ", "
  //                                                    "Day: "
  //           << static_cast<unsigned>(ymd.day()) << "\n"
  //                                                  "ymd: "
  //           << ymd << '\n';

  return EXIT_SUCCESS;
}