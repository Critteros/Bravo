#include "application.hpp"

#include <sleepy_discord/sleepy_discord.h>

#include <fmt/core.h>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[], char **envp)
{
    BravoBot::Application app_control{argc, argv, envp};
    app_control.run();
}