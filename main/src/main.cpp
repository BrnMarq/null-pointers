#include <iostream>
#include <fstream>
#include <filesystem>
#include <typeinfo>
#include <chrono>

#include <Matcher.hpp>
#include <IOUtils.hpp>
#include <Parser.hpp>
#include <Definitions.hpp>
#include <Exception.hpp>

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

    else if (arg == "agents")
    {
      Parser p;
      auto agents = p.get_agents();

      print_agents(agents);
    }

    else if (arg == "tasks")
    {
      Parser p;
      auto tasks = p.get_tasks();

      print_tasks(tasks);
    }

    else if (arg == "match")
    {
      Parser parser{};
      Matcher matcher(parser.get_agents(), parser.get_tasks());
      Matcher::MatchT match = matcher.create_match();
      print_match(match);
    }
  }

  return EXIT_SUCCESS;
}