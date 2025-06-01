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
      int agents;
      Parser parser{};

      std::cout << "How many agents do you want to add? : ";
      std::cin >> agents;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      for (int i = 0; i < agents; ++i)
      {
        Agent agent = parser.write_agent();
        parser.add_agent(agent);
        std::cout << GREEN << "New agent added!" << RESET << std::endl;
      }
    }

    else if (arg == "tasks")
    {
      Parser parser{};
      auto tasks = parser.get_tasks();

      print_tasks(tasks);
    }

    else if (arg == "add_task")
    {
      int tasks;
      Parser parser{};

      std::cout << "How many tasks do you want to add? : ";
      std::cin >> tasks;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      for (int i = 0; i < tasks; ++i)
      {
        Task task = parser.write_task();
        parser.add_task(task);
        std::cout << GREEN << "New task added!" << RESET << std::endl;
      }
    }

    else if (arg == "match")
    {
      std::filesystem::path dot_path = pwd / ".np/unmatched.dot";
      std::filesystem::path result_path = pwd / ".np/unmatched.svg";

      std::filesystem::path dot_path2 = pwd / ".np/matched.dot";
      std::filesystem::path result_path2 = pwd / ".np/matched.svg";

      std::string command = "dot -Tsvg \"" + dot_path.generic_string() + "\" -o \"" + result_path.generic_string() + "\"";
      std::string command2 = "dot -Tsvg \"" + dot_path2.generic_string() + "\" -o \"" + result_path2.generic_string() + "\"";

      Parser parser{};
      Matcher matcher(parser.get_agents(), parser.get_tasks());
      Matcher::MatchT match = matcher.create_match();
      parser.save_match(match);
      system(command.c_str());
      system(command2.c_str());
      print_match(match);
    }
  }

  return EXIT_SUCCESS;
}