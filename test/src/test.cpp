#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
  std::string arg(argv[1]);

  if (arg == "test1")
  {
    system("./main/bin/main add_agent < ./resources/agents1.txt");
    system("./main/bin/main add_task < ./resources/tasks1.txt");
  }

  else if (arg == "test2")
  {
    system("./main/bin/main add_agent < ./resources/agents2.txt");
    system("./main/bin/main add_task < ./resources/tasks2.txt");
  }

  return EXIT_SUCCESS;
}