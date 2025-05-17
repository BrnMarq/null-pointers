#include <fstream>
#include "Agent.hpp"

class Parser
{
private:
  const std::filesystem::path pwd = std::filesystem::current_path();
  const std::filesystem::path files_path = pwd / ".np";

public:
  Parser() noexcept;
  ~Parser();

  std::chrono::sys_days string_to_date(const std::string &date) const noexcept;

  std::vector<Agent> get_agents() const;

  std::vector<Task> get_tasks() const;

  // TODO
  void add_agent(const Agent &agent) const;

  // TODO
  void add_task(const Task &task) const;
};
