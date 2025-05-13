#pragma once

#include <stdexcept>
#include <string>

class OverflowException : public std::runtime_error
{
public:
  OverflowException(const size_t &push_flow, const size_t &current_flow, const size_t &capacity) noexcept;
};

class InvalidCommandException : public std::runtime_error
{
public:
  InvalidCommandException(const std::string &arg) noexcept;
};