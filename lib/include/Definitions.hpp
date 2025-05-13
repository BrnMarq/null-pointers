#pragma once

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