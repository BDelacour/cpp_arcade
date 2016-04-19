#include <dlfcn.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex>
#include "Protocol.hpp"
#include "IDisplay.h"
#include "IGame.h"

IDisplay *display;
IGame *game;
std::vector<CaseType> *map;

void th_f_display()
{
    display->initDisplay(30, 30);
    display->displayMap(*map);
}

void th_f_game()
{
    if (game)
        game->Play();
}

void key_pressed(EventType key)
{
    switch (key)
    {
        case EventType::UP:
            game->applyCommand(arcade::CommandType::GO_UP);
            break;
        case EventType::DOWN:
            game->applyCommand(arcade::CommandType::GO_DOWN);
            break;
        case EventType::LEFT:
            game->applyCommand(arcade::CommandType::GO_LEFT);
            break;
        case EventType::RIGHT:
            game->applyCommand(arcade::CommandType::GO_RIGHT);
            break;
        case EventType::ESCAPE:
            game->applyCommand(arcade::CommandType::ILLEGAL);
            break;
        default:
            break;
    }
}

int main(int argc, char **argv)
{
    IDisplay *(*extern_creator)(void (*handler)(EventType), std::mutex *);
    IGame *(*extern_game_creator)(std::mutex *);
    void *dlHandler;
    void *dlGameHandler;

    if (argc != 2)
        return (1);

    if ((dlHandler = dlopen(argv[1], RTLD_LAZY)) == NULL)
    {
        std::cout << "ERROR: dlopen" << std::endl;
        std::cout << dlerror() << std::endl;
        return (1);
    }

    if ((dlGameHandler = dlopen("games/lib_arcade_snake.so", RTLD_LAZY)) == NULL)
    {
        std::cout << "ERROR: dlopen" << std::endl;
        std::cout << dlerror() << std::endl;
        return (1);
    }

    if ((extern_creator = reinterpret_cast<IDisplay *(*)(void (*test)(EventType), std::mutex *)> (dlsym(dlHandler,
                                                                                                        "create_display"))) ==
        NULL)
    {
        std::cout << "ERROR: dlsym" << std::endl;
        std::cout << dlerror() << std::endl;
        return (1);
    }

    if ((extern_game_creator = reinterpret_cast<IGame *(*)(std::mutex *)> (dlsym(dlGameHandler, "create_game"))) ==
        NULL)
    {
        std::cout << "ERROR: dlsym" << std::endl;
        std::cout << dlerror() << std::endl;
        return (1);
    }

    std::mutex mtx;

    display = extern_creator(key_pressed, &mtx);

    game = extern_game_creator(&mtx);
    game->initGame(30, 30);
    map = game->getDisplayMap();

    std::thread threadGame(th_f_game);
    std::thread threadDisplay(th_f_display);
    threadGame.join();
    display->delDisplay();
    threadDisplay.join();

    delete (display);
    delete (game);
    dlclose(dlHandler);
    return (0);
}
