#include "utils.hpp"

#include <spdlog/spdlog.h>

#include <filesystem>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include <regex>
#include <algorithm>
#include <cstdlib>

#include <fmt/core.h>

EnvList load_env(char **envp)
{
    EnvList dict{};
    for (; *envp; *++envp)
    {
        const std::string el{*envp};
        auto sep = el.find("=");

        const std::string key = el.substr(0, sep);
        const std::string value = el.substr(sep + 1, el.size() - sep - 1);

        dict[key] = value;
    }

    const std::string dot_file_name = ".env";
    if (!std::filesystem::exists(dot_file_name))
    {
        spdlog::warn("Env file '{}' is not found", dot_file_name);
        return dict;
    }

    spdlog::info("Env file '{}' present reading from it", dot_file_name);

    std::ifstream file(dot_file_name);
    std::istream_iterator<std::string> start(file), end;
    std::vector<std::string> data(start, end);
    file.close();

    const std::regex match_regex{"^.+=.+$"};

    std::vector<std::string> filtered{};

    std::copy_if(data.begin(),
                 data.end(),
                 std::back_inserter(filtered),
                 [&filtered, &match_regex](const std::string &i)
                 {
                     return std::regex_match(i, match_regex) ? true : false;
                 });

    for (const std::string &el : filtered)
    {
        auto sep = el.find("=");

        const std::string key = el.substr(0, sep);
        const std::string value = el.substr(sep + 1, el.size() - sep - 1);

        dict[key] = value;
    }

    return dict;
}
