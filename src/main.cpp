#include "application.hpp"
#include "pch.hpp"

int func()
{
    return 0;
}

int main(int argc, char *argv[], char **envp)
{
    BravoBot::Application app_control{argc, argv, envp};
    app_control.run();
}