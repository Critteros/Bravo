#include "utils.hpp"

#include <sleepy_discord/sleepy_discord.h>

#include <fmt/core.h>
#include <spdlog/spdlog.h>

#define SLEEPY_USE_HARD_CODED_GATEWAY

class MyClientClass : public SleepyDiscord::DiscordClient
{
public:
    using SleepyDiscord::DiscordClient::DiscordClient;
    void onMessage(SleepyDiscord::Message message) override
    {
        if (message.startsWith("whcg hello"))
            sendMessage(message.channelID, "Hello " + message.author.username);
    }
};

int main(int argc, char *argv[], char **envp)
{
    EnvList env_vars = load_env(envp);
    for (const auto &[key, value] : env_vars)
    {
        spdlog::debug("key: {}  value: {}\n", key, value);
    }

    MyClientClass client(env_vars["DISCORD_TOKEN"], SleepyDiscord::USER_CONTROLED_THREADS);
    client.setIntents(SleepyDiscord::Intent::SERVER_MESSAGES);
    client.run();
}