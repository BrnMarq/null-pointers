#include "Parser.hpp"
#include "json.hpp"

Parser::Parser() noexcept
{
}

Parser::~Parser()
{
}

std::chrono::sys_days Parser::string_to_date(const std::string &date) const noexcept
{
  std::istringstream iss(date);

  int year, month, day;
  char sep;
  iss >> year >> sep >> month >> sep >> day;

  return std::chrono::sys_days{std::chrono::year(year) / std::chrono::month(month) / std::chrono::day(day)};
};

std::string Parser::date_to_string(const std::chrono::sys_days &date) const noexcept
{
  auto ymd = std::chrono::year_month_day(date);

  std::ostringstream oss;
  oss << static_cast<int>(ymd.year()) << '-'
      << std::setw(2) << std::setfill('0') << static_cast<unsigned>(ymd.month()) << '-'
      << std::setw(2) << std::setfill('0') << static_cast<unsigned>(ymd.day());

  return oss.str();
}

std::vector<Agent> Parser::get_agents() const
{
  verify_create_np();

  std::ifstream file_agents(files_path / "agents.json");

  nlohmann::json agents = nlohmann::json::parse(file_agents);

  std::vector<Agent> agents_list;

  for (const auto &a : agents)
  {
    std::chrono::hours _available_time(a["available_time"].get<int>());
    std::string _deparment = a["department"].get<std::string>();

    if (!department_exists(_deparment))
    {
      Departments::departments.push_back(_deparment);
    }

    level _level = string_to_level(a["expertise"].get<std::string>());
    std::string _name = a["name"].get<std::string>();

    Agent agent(_available_time, _deparment, _level, _name);

    agents_list.push_back(agent);
  }

  return agents_list;
};

std::vector<Task> Parser::get_tasks() const
{
  verify_create_np();

  std::ifstream file_task(pwd / ".np/tasks.json");

  nlohmann::json tasks = nlohmann::json::parse(file_task);

  std::vector<Task> task_list;

  for (const auto &tsk : tasks)
  {
    std::chrono::hours _estimated_time(tsk["estimated_time"].get<int>());
    std::chrono::sys_days _dead_line = string_to_date(tsk["dead_line"].get<std::string>());
    std::string _deparment = tsk["department"].get<std::string>();

    level _difficulty = string_to_level(tsk["difficulty"].get<std::string>());

    std::string _title = tsk["title"].get<std::string>();

    Task task(_estimated_time, _dead_line, _deparment, _difficulty, _title, "");

    task_list.push_back(task);
  };

  return task_list;
};

void Parser::add_agent(const Agent &agent) const
{
  nlohmann::json js_agent;

  verify_create_np();

  std::filesystem::path full_path = files_path / "agents.json";
  std::ifstream file_agents(full_path);

  try
  {
    file_agents >> js_agent;
  }
  catch (const nlohmann::json::parse_error &e)
  {
    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    return;
  }

  nlohmann::json new_agent =
      {
          {"available_time", agent.get_available_time().count()},
          {"department", agent.get_department()},
          {"expertise", level_to_string(agent.get_expertise())},
          {"name", agent.get_name()}};

  js_agent.push_back(new_agent);

  std::ofstream out_file(full_path);

  if (!out_file)
  {
    std::cerr << "Error opening the file: " << "agents.json" << std::endl;
    return;
  }

  out_file << js_agent.dump(4);
}

void Parser::add_task(const Task &task) const
{
  nlohmann::json js_task;

  verify_create_np();

  std::filesystem::path full_path = files_path / "tasks.json";

  std::ifstream file_tasks(full_path);

  try
  {
    file_tasks >> js_task;
  }
  catch (const nlohmann::json::parse_error &e)
  {
    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    return;
  }

  nlohmann::json new_task =
      {
          {"estimated_time", task.get_estimated_time().count()},
          {"dead_line", date_to_string(task.get_dead_line())},
          {"department", task.get_department()},
          {"difficulty", level_to_string(task.get_difficulty())},
          {"title", task.get_title()},
          {"requirements", task.get_requirements()}};

  js_task.push_back(new_task);

  std::ofstream out_file(full_path);

  if (!out_file)
  {
    std::cerr << "Error opening the file: " << "tasks.json" << std::endl;
    return;
  }

  out_file << js_task.dump(4);
}

void Parser::verify_create_np() const
{
  if (!std::filesystem::exists(files_path))
  {
    std::filesystem::create_directory(files_path);
  }

  nlohmann::json js;

  for (int i = 0; i < 2; ++i)
  {
    std::string json_name = i == 0 ? "agents.json" : "tasks.json";

    std::filesystem::path path = files_path / json_name;
    std::ifstream file(path);

    if (!file.good())
    {
      js = nlohmann::json::array();
      std::ofstream out_file(path);

      if (out_file)
      {
        out_file << js.dump(4);
      }
      else
      {
        std::cerr << "Error creating" << json_name << "file" << std::endl;
        return;
      }
    }
  }
}