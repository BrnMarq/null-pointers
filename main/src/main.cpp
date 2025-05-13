#include <iostream>
#include <fstream>
#include <typeinfo>

#include "json.hpp"
#include <Agent.hpp>
#include <Task.hpp>

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

int main()
{
  std::ifstream file("../../.np/agents.json");
  json agents = json::parse(file);

  std::vector<Agent> agents_list;

  for (const auto &item : agents)
  {
    std::chrono::hours _available_time(item["available_time"].get<int>());
    std::string _deparment = item["department"].get<std::string>();
    level _level = get_level_from_string(item["expertise"].get<std::string>());
    std::string _name = item["name"].get<std::string>();

    Agent agent(_available_time, _deparment, _level, _name);

    agents_list.push_back(agent);
  }

  std::cout << agents_list.size() << std::endl;

  return EXIT_SUCCESS;
}