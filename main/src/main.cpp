#include <iostream>
#include <fstream>
#include <filesystem>
#include <typeinfo>
#include <chrono>

#include <Matcher.hpp>
#include <Definitions.hpp>
#include <Exception.hpp>
#include "Parser.hpp"

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

  Parser parser{};
  Matcher matcher(parser.get_agents(), parser.get_tasks());
  Matcher::MatchT match = matcher.create_match();
  matcher.print_match(match);

  return EXIT_SUCCESS;
}