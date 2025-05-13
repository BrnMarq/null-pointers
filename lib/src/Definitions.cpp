#include "Definitions.hpp"

float Configs::time_gap_multiplier{1.0f};
float Configs::difficulty_gap_multiplier{1.0f};

bool is_valid_argument(const std::string &arg)
{
    return std::find(valid_program_args.begin(), valid_program_args.end(), arg) != valid_program_args.end();
}