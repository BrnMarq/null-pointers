#include "Parser.hpp"
#include "json.hpp"

Parser::Parser() noexcept
{
}

Parser::~Parser()
{
}

#pragma region Helpers

std::chrono::sys_days string_to_date(const std::string &date)
{
  std::istringstream iss(date);

  int year, month, day;
  char sep;
  iss >> year >> sep >> month >> sep >> day;

  return std::chrono::sys_days{std::chrono::year(year) / std::chrono::month(month) / std::chrono::day(day)};
};

std::string date_to_string(const std::chrono::sys_days &date)
{
  auto ymd = std::chrono::year_month_day(date);

  std::ostringstream oss;
  oss << static_cast<int>(ymd.year()) << '-'
      << std::setw(2) << std::setfill('0') << static_cast<unsigned>(ymd.month()) << '-'
      << std::setw(2) << std::setfill('0') << static_cast<unsigned>(ymd.day());

  return oss.str();
}

std::string to_lower(const std::string &str)
{
  std::string result = str;
  for (char &c : result)
  {
    c = std::tolower(c);
  }
  return result;
}

bool is_valid_date_format(const std::string &date)
{
  std::regex format("^\\d{4}-\\d{2}-\\d{2}$");
  return std::regex_match(date, format);
}

bool validate_date(int year, int month, int day)
{
  if (year < 1900 || month < 1 || month > 12 || day < 1)
  {
    return false;
  }

  const std::array<int, 12> diasPorMes = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
  {
    if (day > 29)
    {
      return false;
    }
  }
  else if (day > diasPorMes[month - 1])
  {
    return false;
  }

  return true;
}

bool is_valid_date(const std::string &date)
{
  if (!is_valid_date_format(date))
  {
    return false;
  }

  int year, month, day;
  char sep1, sep2;
  std::istringstream iss(date);

  if (!(iss >> year >> sep1 >> month >> sep2 >> day))
  {
    return false;
  }
  if (sep1 != '-' || sep2 != '-')
  {
    return false;
  }

  return validate_date(year, month, day);
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
        std::cerr << "Error creating" << json_name << " file" << std::endl;
        return;
      }
    }
  }
}

#pragma endregion

namespace nlohmann
{
  template <>
  struct adl_serializer<Agent>
  {
    static void to_json(nlohmann::json &j, const Agent &a)
    {
      j = json{
          {"available_time", a.get_available_time().count()},
          {"department", a.get_department()},
          {"expertise", level_to_string(a.get_expertise())},
          {"name", a.get_name()}};
    }

    static void from_json(const nlohmann::json &j, Agent &a)
    {
      int available_time = j.at("available_time").get<int>();
      std::string department = j.at("department").get<std::string>();
      std::string expertise = j.at("expertise").get<std::string>();
      std::string name = j.at("name").get<std::string>();

      a = Agent{std::chrono::hours(available_time), department, string_to_level(expertise), name};
    }
  };

  template <>
  struct adl_serializer<Task>
  {
    static void to_json(nlohmann::json &j, const Task &t)
    {
      j = json{
          {"estimated_time", t.get_estimated_time().count()},
          {"dead_line", date_to_string(t.get_dead_line())},
          {"department", t.get_department()},
          {"difficulty", level_to_string(t.get_difficulty())},
          {"title", t.get_title()},
          {"requirements", t.get_requirements()}};
    }

    static void from_json(const nlohmann::json &j, Task &t)
    {
      int estimated_time = j.at("estimated_time").get<int>();
      std::string dead_line = j.at("dead_line").get<std::string>();
      std::string department = j.at("department").get<std::string>();
      std::string difficulty = j.at("difficulty").get<std::string>();
      std::string title = j.at("title").get<std::string>();
      std::string requirements = j.at("requirements").get<std::string>();

      t = Task{std::chrono::hours(estimated_time), string_to_date(dead_line), department, string_to_level(difficulty), title, requirements};
    }
  };
}

#pragma region Agents

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

    if (a.contains("assigned_tasks"))
    {
      for (const auto &t : a["assigned_tasks"])
      {
        std::chrono::hours _estimated_time(t["estimated_time"].get<int>());
        std::chrono::sys_days _dead_line = string_to_date(t["dead_line"].get<std::string>());
        std::string _deparment = t["department"].get<std::string>();

        level _difficulty = string_to_level(t["difficulty"].get<std::string>());

        std::string _title = t["title"].get<std::string>();

        Task task(_estimated_time, _dead_line, _deparment, _difficulty, _title, "");
        agent.assign_task(task);
      }
    }

    agents_list.push_back(agent);
  }

  return agents_list;
}

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

  nlohmann::json new_agent = agent;

  js_agent.push_back(new_agent);

  std::ofstream out_file(full_path);

  if (!out_file)
  {
    std::cerr << "Error opening the file: " << "agents.json" << std::endl;
    return;
  }

  out_file << js_agent.dump(4);
}

Agent Parser::write_agent() const
{
  std::string name;
  int available_time;
  std::string department;
  std::string expertise;

  std::cout << "Enter name: ";
  std::getline(std::cin, name);

  std::cout << "Enter available time: ";

  while (!(std::cin >> available_time) || available_time < 0)
  {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Enter a number greater than 0. Try again: ";
  }

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "Enter department: ";
  std::getline(std::cin, department);

  department = to_lower(department);

  std::cout << "Enter expertise (novice, beginner, competent, proficient, expert): ";
  std::cin >> expertise;

  expertise = to_lower(expertise);

  if (name.empty() || department.empty() || !is_valid_level(expertise))
  {
    throw std::invalid_argument("Some of the data you provided is wrong. Try again");
  }

  Agent agent{std::chrono::hours(available_time), department, string_to_level(expertise), name};

  return agent;
}

#pragma endregion

#pragma region Tasks

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
    std::string _requirements = tsk["requirements"].get<std::string>();

    Task task(_estimated_time, _dead_line, _deparment, _difficulty, _title, _requirements);

    task_list.push_back(task);
  };

  return task_list;
};

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

  nlohmann::json new_task = task;

  js_task.push_back(new_task);

  std::ofstream out_file(full_path);

  if (!out_file)
  {
    std::cerr << "Error opening the file: " << "tasks.json" << std::endl;
    return;
  }

  out_file << js_task.dump(4);
}

Task Parser::write_task() const
{
  int estimated_time;
  std::string department;
  std::string difficulty;
  std::string title;
  std::string dead_line;
  std::string requirements;

  std::cout << "Enter title: ";
  std::getline(std::cin, title);

  std::cout << "Enter dead line (format yyyy-mm-dd. Ex: 2025-01-01): ";
  std::cin >> dead_line;

  std::cout << "Enter estimated time: ";

  while (!(std::cin >> estimated_time) || estimated_time < 0)
  {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Enter a number greater than 0. Try again: ";
  }

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "Enter department: ";
  std::getline(std::cin, department);

  department = to_lower(department);

  std::cout << "Enter difficulty (novice, beginner, competent, proficient, expert): ";
  std::cin >> difficulty;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "Enter requirements (optional): ";
  std::getline(std::cin, requirements);

  if (title.empty() || !is_valid_date(dead_line) || department.empty() || !is_valid_level(difficulty))
  {
    throw std::invalid_argument("Some of the data you provided is wrong. Try again");
  }

  Task task{std::chrono::hours(estimated_time), string_to_date(dead_line), department, string_to_level(difficulty), title, requirements};

  return task;
}

#pragma endregion

void Parser::save_match(const Matcher::MatchT &match) const
{
  if (!match.empty())
  {
    std::ifstream file_agents(pwd / ".np/agents.json");
    nlohmann::json agents = nlohmann::json::parse(file_agents);

    auto age = get_agents();

    for (const std::pair<Agent, std::vector<Task>> &m : match)
    {
      for (auto &a : agents)
      {
        if (a["name"] == m.first.get_name())
        {
          for (const Task &task : m.second)
          {
            a["assigned_tasks"].push_back(task);
          }
        }
      }
    }

    std::ofstream archivo_salida(pwd / ".np/agents.json");
    archivo_salida << agents.dump(2);
  }
}