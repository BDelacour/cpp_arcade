//
// Created by delaco_c on 29/03/16.
//

#ifndef CPP_ARCADE_IGAME_H
# define CPP_ARCADE_IGAME_H

#include <vector>
# include "IDisplay.h"
# include "Protocol.hpp"

class IGame
{
public:
    virtual ~IGame() {}
    virtual void    Play() = 0;
    virtual void    initGame(int const width, int const height) = 0;
    virtual std::vector<CaseType> *getDisplayMap() = 0;
    virtual void    *applyCommand(arcade::CommandType command) = 0;
};

#endif //CPP_ARCADE_IGAME_H
