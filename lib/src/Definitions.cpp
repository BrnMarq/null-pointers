#include "Definitions.hpp"

float Configs::time_gap_multiplier{1.0f};
float Configs::difficulty_gap_multiplier{1.0f};
std::vector<std::string> Configs::valid_program_args{"np"};

std::vector<std::string> Departments::departments{};

bool is_valid_argument(const std::string &arg)
{
    return std::find(Configs::valid_program_args.begin(), Configs::valid_program_args.end(), arg) != Configs::valid_program_args.end();
}

bool department_exists(const std::string &deparment)
{
    return std::find(Departments::departments.begin(), Departments::departments.end(), deparment) != Departments::departments.end();
}

level get_level_from_string(const std::string &_level)
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