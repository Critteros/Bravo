#pragma once

#include <unordered_map>
#include <string>

using EnvList = std::unordered_map<std::string, std::string>;

EnvList load_env(char **envp);