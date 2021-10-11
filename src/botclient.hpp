#pragma once
#include "pch.hpp"

namespace BravoBot
{
    class BotClient : public SleepyDiscord::DiscordClient
    {
    public:
        using SleepyDiscord::DiscordClient::DiscordClient;
        void onMessage(SleepyDiscord::Message message) override;
    };
};