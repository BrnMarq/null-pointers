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
  static std::vector<std::string> valid_levels;
};

struct Departments
{
  static std::vector<std::string> departments;
};

bool is_valid_argument(const std::string &arg);

bool is_valid_level(const std::string &level);

bool department_exists(const std::string &deparment);

level string_to_level(const std::string &_level);

std::string level_to_string(const level &_level);