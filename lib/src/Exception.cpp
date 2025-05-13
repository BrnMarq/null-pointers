#include "Exception.hpp"

OverflowException::OverflowException(const size_t &push_flow, const size_t &current_flow, const size_t &capacity) noexcept
    : std::runtime_error{"Cannot push " + std::to_string(push_flow) + " on " + std::to_string(current_flow) + "/" + std::to_string(capacity) + " arc"}
{
}

InvalidCommandException::InvalidCommandException(const std::string &arg) noexcept
    : std::runtime_error{arg + " : command not found"}
{
}