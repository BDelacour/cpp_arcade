//
// Created by berny on 29/03/16.
//

#ifndef CPP_ARCADE_ACTION_H
#define CPP_ARCADE_ACTION_H

#include <iterator>
#include <vector>
#include <list>
#include <mutex>
#include "IGame.h"
#include "IDisplay.h"

#define SIZE_X this->width
#define SIZE_Y this->height
#define INIT_SIZE_SNAKE 4
#define SIZE (this->width * this->height)
#define MIDDLE ((this->height / 2) * this->width + (this->width / 2))

class Snake : public IGame
{
    arcade::CommandType direction;
    int width;
    int height;
    uint16_t positionSnake;
    uint16_t sizeSnake;
    std::vector<CaseType> map;
    std::list<int> snakeBody;
    std::list<arcade::CommandType> commands;
    bool isOkay;
    bool p_mode;
    std::mutex *mtx;
public:
    Snake(bool, std::mutex *);

    virtual ~Snake();

    virtual void Play();

    virtual void initGame(int const width, int const height);

    virtual void *applyCommand(arcade::CommandType command);

    virtual std::vector<CaseType> *getDisplayMap();

    void generateMap();

    uint16_t getPosY(uint16_t pos);

    uint16_t getPosX(uint16_t pos);

    void *getWhereAmI();

    void *getMap();

    void generateSnakeBody();

    bool execDir();

    bool isFood();

    void generateFood();

    void addTheSnakeOnMap();
};


#endif //CPP_ARCADE_ACTION_H
