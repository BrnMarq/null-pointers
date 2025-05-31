#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

std::string get_agent_path(int i)
{
  std::filesystem::path agents_path = std::filesystem::current_path() / "resources/agent";
  return agents_path.generic_string() + std::to_string(i) + std::string(".txt");
}

std::string get_task_path(int i)
{
  std::filesystem::path tasks_path = std::filesystem::current_path() / "resources/task";
  return tasks_path.generic_string() + std::to_string(i) + std::string(".txt");
}

int main(int argc, char *argv[])
{
  std::string arg(argv[1]);

  if (arg == "test1")
  {
    for (int i = 1; i < 6; ++i)
    {
      system((std::string("./main/bin/main add_agent < ") + get_agent_path(i)).c_str());
      system((std::string("./main/bin/main add_task < ") + get_task_path(i)).c_str());
    }
  }

  else if (arg == "test2")
  {
    for (int i = 6; i < 16; ++i)
    {
      system((std::string("./main/bin/main add_agent < ") + get_agent_path(i)).c_str());
      system((std::string("./main/bin/main add_task < ") + get_task_path(i)).c_str());
    }
  }

  return EXIT_SUCCESS;
}