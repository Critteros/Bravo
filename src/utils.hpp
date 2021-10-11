#pragma once
#include "pch.hpp"

using EnvList = std::unordered_map<std::string, std::string>;

EnvList load_env(char **envp);