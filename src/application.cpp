#include "application.hpp"

#include <spdlog/spdlog.h>
#include <sleepy_discord/sleepy_discord.h>

#include <stdexcept>

namespace BravoBot
{
    Application::Application(int argc, char *argv[], char **envp)
        : argc{argc}, argv(argv, argv + argc)
    {
        enviroment = load_env(envp);

        if (enviroment.find("DISCORD_TOKEN") == enviroment.end())
        {
            spdlog::critical("No DISCORD_TOKEN env var exists!");
            throw std::runtime_error{"No DISCORD_TOKEN was provided!"};
        }

        const std::string &token = enviroment["DISCORD_TOKEN"];
        client = std::make_unique<BotClient>(token, SleepyDiscord::USER_CONTROLED_THREADS);
        client->setIntents(SleepyDiscord::Intent::SERVER_MESSAGES);
    }

    void Application::run()
    {
        client->run();
    }

}