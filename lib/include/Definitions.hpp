#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

enum class level
{
  novice,
  beginner,
  competent,
  proficient,
  expert
};

struct Configs
{
  static float time_gap_multiplier;
  static float difficulty_gap_multiplier;
  static std::vector<std::string> valid_program_args;
};

struct Departments
{
  static std::vector<std::string> departments;
};

bool is_valid_argument(const std::string &arg);

bool department_exists(const std::string &deparment);

level get_level_from_string(const std::string &_level);