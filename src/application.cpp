#include "application.hpp"

namespace BravoBot
{
    Application::Application(int argc, char *argv[], char **envp)
        : argc{argc}, argv(argv, argv + argc)
    {
        enviroment = load_env(envp);

        if (enviroment.find("DISCORD_TOKEN") == enviroment.end())
        {
            spdlog::critical("No DISCORD_TOKEN env var exists!");
            exit(-1);
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