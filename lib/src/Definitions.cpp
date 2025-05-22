#include "Definitions.hpp"

float Configs::time_gap_multiplier{1.0f};
float Configs::difficulty_gap_multiplier{1.0f};
std::vector<std::string> Configs::valid_program_args{"init", "add_agent", "add_task", "agents", "tasks", "match"};
std::vector<std::string> Configs::valid_levels{"novice", "beginner", "competent", "proficient", "expert"};

std::vector<std::string> Departments::departments{};

bool is_valid_argument(const std::string &arg)
{
    return std::find(Configs::valid_program_args.begin(), Configs::valid_program_args.end(), arg) != Configs::valid_program_args.end();
}

bool department_exists(const std::string &deparment)
{
    return std::find(Departments::departments.begin(), Departments::departments.end(), deparment) != Departments::departments.end();
}

level string_to_level(const std::string &_level)
{
    std::unordered_map<std::string, level> level_map =
        {
            {"novice", level::novice},
            {"beginner", level::beginner},
            {"competent", level::competent},
            {"proficient", level::proficient},
            {"expert", level::expert}};

    return level_map.at(_level);
}

std::string level_to_string(const level &_level)
{
    std::unordered_map<level, std::string> level_map =
        {
            {level::novice, "novice"},
            {level::beginner, "beginner"},
            {level::competent, "competent"},
            {level::proficient, "proficient"},
            {level::expert, "expert"}};

    return level_map.at(_level);
}

bool is_valid_level(const std::string &level)
{
    return std::find(Configs::valid_levels.begin(), Configs::valid_levels.end(), level) != Configs::valid_levels.end();
}
