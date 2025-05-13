#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

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
};

const std::vector<std::string> valid_program_args = {"np"};

bool is_valid_argument(const std::string &arg);