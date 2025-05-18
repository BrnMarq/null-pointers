#include <fstream>
#include <filesystem>
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

  std::string date_to_string(const std::chrono::sys_days &date) const noexcept;

  std::vector<Agent> get_agents() const;

  std::vector<Task> get_tasks() const;

  void add_agent(const Agent &agent) const;

  void add_task(const Task &task) const;

  void verify_create_np() const;
};
