#include <iostream>
#include <fstream>
#include <typeinfo>

#include "json.hpp"
#include <Agent.hpp>
#include <Task.hpp>
#include <Definitions.hpp>
#include <Exception.hpp>

using json = nlohmann::json;

level get_level_from_string(const std::string &_level)
{
  std::unordered_map<std::string, level> level_map =
      {
          {"novice", level::novice},
          {"beginner", level::beginner},
          {"competent", level::competent},
          {"proficient", level::proficient},
          {"expert", level::expert}};

  return level_map.at(_level);
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
  }
  // std::ifstream file("../../.np/agents.json");
  // json agents = json::parse(file);

  // std::vector<Agent> agents_list;

  // for (const auto &item : agents)
  // {
  //   std::chrono::hours _available_time(item["available_time"].get<int>());
  //   std::string _deparment = item["department"].get<std::string>();
  //   level _level = get_level_from_string(item["expertise"].get<std::string>());
  //   std::string _name = item["name"].get<std::string>();

  //   Agent agent(_available_time, _deparment, _level, _name);

  //   agents_list.push_back(agent);
  // }

  // std::cout << agents_list.size() << std::endl;

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