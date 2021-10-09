#include "botclient.hpp"

namespace BravoBot
{
    void BotClient::onMessage(SleepyDiscord::Message message)
    {
        if (message.startsWith("whcg hello"))
            sendMessage(message.channelID, "Hello " + message.author.username);
    }
}