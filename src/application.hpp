#pragma once

#include "utils.hpp"
#include "botclient.hpp"
#include "pch.hpp"

namespace BravoBot
{
    class Application
    {
    public:
        Application(int argc, char *argv[], char **envp);
        void run();

    private:
        int argc;
        std::vector<std::string> argv;
        EnvList enviroment;
        std::unique_ptr<BotClient> client;
    };
}