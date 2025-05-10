#include "Agent.hpp"

Agent::Agent(time_t _available_time, std::string _deparment, level _expertise, std::string _name) noexcept
    : available_time{_available_time}, department{_deparment}, expertise{_expertise}, name{_name} {};
