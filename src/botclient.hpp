#pragma once

#include <sleepy_discord/sleepy_discord.h>

namespace BravoBot
{
    class BotClient : public SleepyDiscord::DiscordClient
    {
    public:
        using SleepyDiscord::DiscordClient::DiscordClient;
        void onMessage(SleepyDiscord::Message message) override;
    };
};