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

  // std::cout << BLUE << "TEXT" << RESET << std::endl;
  // std::cout << RED << "TEXT" << RESET << std::endl;
  // std::cout << CYAN << "TEXT" << RESET << std::endl;
  // std::cout << GREEN << "TEXT" << RESET << std::endl;
  // std::cout << YELLOW << "TEXT" << RESET << std::endl;
  // std::cout << MAGENTA << "TEXT" << RESET << std::endl;

  if (argc > 1)
  {
    std::string arg(argv[1]);

    if (!is_valid_argument(arg))
    {
      throw InvalidCommandException(arg);
    }

    if (arg == "init")
    {
      Parser parser{};
      parser.verify_create_np();
    }

    else if (arg == "agents")
    {
      Parser parser{};
      auto agents = parser.get_agents();

      print_agents(agents);
    }

    else if (arg == "add_agent")
    {
      Parser parser{};
      Agent agent = parser.write_agent();
      parser.add_agent(agent);
      std::cout << GREEN << "New agent added!" << RESET << std::endl;
    }

    else if (arg == "tasks")
    {
      Parser parser{};
      auto tasks = parser.get_tasks();

      print_tasks(tasks);
    }

    else if (arg == "add_task")
    {
      Parser parser{};
      Task task = parser.write_task();
      parser.add_task(task);
      std::cout << GREEN << "New task added!" << RESET << std::endl;
    }

    else if (arg == "match")
    {
      Parser parser{};
      Matcher matcher(parser.get_agents(), parser.get_tasks());
      Matcher::MatchT match = matcher.create_match();
      parser.save_match(match);
      print_match(match);
    }
  }

  return EXIT_SUCCESS;
}