#include <sleepy_discord/sleepy_discord.h>

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

int main()
{
    MyClientClass client("test", SleepyDiscord::USER_CONTROLED_THREADS);
    client.run();
}