#include <fstream>
#include <filesystem>
#include <cctype>
#include <regex>

#include "Agent.hpp"
#include "Matcher.hpp"

class Parser
{
private:
  const std::filesystem::path pwd = std::filesystem::current_path();
  const std::filesystem::path files_path = pwd / ".np";

public:
  Parser() noexcept;
  ~Parser();

  std::vector<Agent> get_agents() const;

  std::vector<Task> get_tasks() const;

  void add_agent(const Agent &agent) const;

  Agent write_agent() const;

  Task write_task() const;

  void add_task(const Task &task) const;

  void save_match(const Matcher::MatchT &match) const;

  void verify_create_np() const;
};
