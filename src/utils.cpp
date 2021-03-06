#include "utils.hpp"

EnvList load_env(char **envp)
{
    EnvList dict{};
    for (; *envp; *++envp)
    {
        const std::string el{*envp};
        const size_t sep = el.find("=");

        const std::string key = el.substr(0, sep);
        const std::string value = el.substr(sep + 1, el.size() - sep - 1);

        dict[key] = value;
    }

    //Check if file `.env` exists
    const std::string dot_file_name = ".env";
    if (!std::filesystem::exists(dot_file_name))
    {
        spdlog::warn("Env file '{}' is not found", dot_file_name);
        return dict;
    }

    spdlog::info("Env file '{}' present reading from it", dot_file_name);

    //Reading from enviroment file into buffer `data`
    std::ifstream file(dot_file_name);
    std::istream_iterator<std::string> start(file), end;
    std::vector<std::string> data(start, end);
    file.close();

    //Filtering out actual enviroment entries
    const std::regex match_regex{"^.+=.+$"};
    std::vector<std::string> filtered{};
    std::copy_if(std::make_move_iterator(data.begin()),
                 std::make_move_iterator(data.end()),
                 std::back_inserter(filtered),
                 [&filtered, &match_regex](const std::string &i)
                 {
                     return std::regex_match(i, match_regex) ? true : false;
                 });

    for (const std::string &el : filtered)
    {
        const size_t sep = el.find("=");

        const std::string key = el.substr(0, sep);
        const std::string value = el.substr(sep + 1, el.size() - sep - 1);

        dict[key] = value;
    }

    return dict;
}
