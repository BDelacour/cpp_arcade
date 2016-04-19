//
// Created by berny on 29/03/16.
//

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "Snake.h"

extern "C"
{
Snake *create_game(std::mutex *mtx)
{
    return (new Snake(true, mtx));
}

void Play()
{
    Snake *game = new Snake(false, new std::mutex);

    game->initGame(20, 20);
    game->Play();
}
}

Snake::Snake(bool mode, std::mutex *mtx)
        : p_mode(mode)
{
    this->mtx = mtx;
}

Snake::~Snake()
{
}

void Snake::initGame(int const width, int const height)
{
    this->width = width;
    this->height = height;
    sizeSnake = INIT_SIZE_SNAKE;
    positionSnake = (uint16_t) MIDDLE;
    this->mtx->lock();
    generateMap();
    generateSnakeBody();
    generateFood();
    this->mtx->unlock();
    direction = arcade::CommandType::GO_RIGHT;
}

void *Snake::applyCommand(arcade::CommandType command)
{
    switch (command)
    {
        case arcade::CommandType::WHERE_AM_I:
            return (getWhereAmI());
        case arcade::CommandType::GET_MAP:
            return (getMap());
        case arcade::CommandType::GO_UP:
            if (!(map[positionSnake - SIZE_X] == CaseType::SNAKE && direction == arcade::CommandType::GO_DOWN))
            {
                if (!this->p_mode)
                    direction = command;
                else
                    commands.push_back(command);
            }
            break;
        case arcade::CommandType::GO_DOWN:
            if (!(map[positionSnake + SIZE_X] == CaseType::SNAKE && direction == arcade::CommandType::GO_UP))
            {
                if (!this->p_mode)
                    direction = command;
                else
                    commands.push_back(command);
            }
            break;
        case arcade::CommandType::GO_LEFT:
            if (!(map[positionSnake - 1] == CaseType::SNAKE && direction == arcade::CommandType::GO_RIGHT))
            {
                if (!this->p_mode)
                    direction = command;
                else
                    commands.push_back(command);
            }
            break;
        case arcade::CommandType::GO_RIGHT:
            if (!(map[positionSnake + 1] == CaseType::SNAKE && direction == arcade::CommandType::GO_LEFT))
            {
                if (!this->p_mode)
                    direction = command;
                else
                    commands.push_back(command);
            }
            break;
        case arcade::CommandType::ILLEGAL:
            isOkay = false;
            break;
        default:
            break;
    }
    return (NULL);
}

void Snake::generateMap()
{
    for (uint16_t i = 0; i < SIZE; i++)
        map.push_back(CaseType::EMPTY);
}

uint16_t             Snake::getPosY(uint16_t pos)
{
    return ((uint16_t) (pos / SIZE_X));
}

uint16_t             Snake::getPosX(uint16_t pos)
{
    return ((uint16_t) (pos % SIZE_X));
}

void *Snake::getWhereAmI()
{
    arcade::WhereAmI *stru;
    std::list<int>::iterator it;

    if ((stru = (arcade::WhereAmI *) malloc(sizeof(arcade::WhereAmI) + sizeSnake * sizeof(arcade::Position))) == NULL)
        return (NULL);
    stru->type = arcade::CommandType::WHERE_AM_I;
    stru->lenght = sizeSnake;
    it = snakeBody.begin();
    for (int i = 0; i < sizeSnake; i++)
    {
        stru->position[i].x = getPosX((uint16_t) *it);
        stru->position[i].y = getPosY((uint16_t) *it);
        it++;
    }
    write(1, stru, sizeof(arcade::WhereAmI) + sizeSnake * sizeof(arcade::Position));
    return stru;
}

void *Snake::getMap()
{
    arcade::GetMap *stru;
    int i;

    i = 0;
    if ((stru = (arcade::GetMap *) malloc(sizeof(arcade::GetMap) + sizeof(arcade::TileType) * SIZE)) == NULL)
        return (NULL);
    stru->type = arcade::CommandType::GET_MAP;
    stru->width = (uint16_t)
            SIZE_X;
    stru->height = (uint16_t)
            SIZE_Y;
    while (i < SIZE)
    {
        switch (map[i])
        {
            case CaseType::WALL:
                stru->tile[i] = arcade::TileType::BLOCK;
                break;
            case CaseType::POWERUP:
                stru->tile[i] = arcade::TileType::POWERUP;
                break;
            default:
                stru->tile[i] = arcade::TileType::EMPTY;
                break;
        }
        i++;
    }
    write(1, stru, sizeof(arcade::GetMap) + sizeof(arcade::TileType) * SIZE);
    return (stru);
}

void Snake::generateSnakeBody()
{
    int i;
    int pos;

    pos = positionSnake;
    i = 1;
    if ((INIT_SIZE_SNAKE * 2) >= SIZE_X)
    {
        std::cout << "FATAL ERROR SIZE X MUST BE" <<
        "< TO INIT_SIZE_SNAKE * 2 GO CHECK Snake.h" << std::endl;
        exit(-1);
    }
    snakeBody.push_back(positionSnake);
    map[positionSnake] = CaseType::SNAKE;
    pos--;
    while (i < INIT_SIZE_SNAKE)
    {
        snakeBody.push_back(pos);
        map[pos] = CaseType::SNAKE;
        i++;
        pos--;
    }
}

bool Snake::execDir()
{
    bool didFoodEnteredStomach = false;

    switch (direction)
    {
        case arcade::CommandType::GO_UP:
            if (positionSnake - SIZE_X < 0 || map[positionSnake - SIZE_X] == CaseType::SNAKE)
                return (false);
            if (map[positionSnake - SIZE_X] == CaseType::POWERUP)
                didFoodEnteredStomach = true;
            positionSnake -= SIZE_X;
            break;
        case arcade::CommandType::GO_DOWN:
            if (positionSnake + SIZE_X > SIZE || map[positionSnake + SIZE_X] == CaseType::SNAKE)
                return (false);
            if (map[positionSnake + SIZE_X] == CaseType::POWERUP)
                didFoodEnteredStomach = true;
            positionSnake += SIZE_X;
            break;
        case arcade::CommandType::GO_LEFT:
            if (getPosY((uint16_t) (positionSnake - 1)) < getPosY((uint16_t) positionSnake) ||
                map[positionSnake - 1] == CaseType::SNAKE)
                return (false);
            if (map[positionSnake - 1] == CaseType::POWERUP)
                didFoodEnteredStomach = true;
            positionSnake -= 1;
            break;
        case arcade::CommandType::GO_RIGHT:
            if (getPosY((uint16_t) (positionSnake + 1)) > getPosY((uint16_t) positionSnake) ||
                map[positionSnake + 1] == CaseType::SNAKE)
                return (false);
            if (map[positionSnake + 1] == CaseType::POWERUP)
                didFoodEnteredStomach = true;
            positionSnake += 1;
            break;
        default:
            break;
    }
    if (didFoodEnteredStomach)
    {
        snakeBody.push_front(positionSnake);
        sizeSnake++;
    }
    else
    {
        snakeBody.push_front(positionSnake);
        map[snakeBody.back()] = CaseType::EMPTY;
        snakeBody.pop_back();
    }
    return (true);
}

void Snake::generateFood()
{
    int foodPos;

    foodPos = rand() % SIZE;
    while (map[foodPos] != CaseType::EMPTY)
        foodPos = rand() % SIZE;
    map[foodPos] = CaseType::POWERUP;
}

bool Snake::isFood()
{
    std::vector<CaseType>::iterator it;

    it = map.begin();
    while (it != map.end())
    {
        if (*it == CaseType::POWERUP)
            return true;
        it++;
    }
    return false;
}

void Snake::addTheSnakeOnMap()
{
    std::list<int>::iterator it;

    it = snakeBody.begin();
    while (it != snakeBody.end())
    {
        map[*it] = CaseType::SNAKE;
        it++;
    }
}

void Snake::Play()
{
    arcade::CommandType cmd;

    isOkay = true;
    addTheSnakeOnMap();
    while (isOkay)
    {
        if (!this->p_mode)
        {
            std::cin.read((char *) &cmd, sizeof(cmd));
            this->applyCommand(cmd);
        }
        if (this->p_mode || cmd == arcade::CommandType::PLAY)
        {
            this->mtx->lock();
            isOkay = execDir();
            addTheSnakeOnMap();
            if (!isFood())
                generateFood();
            this->mtx->unlock();
            if (this->p_mode)
            {
                usleep(100000);
                if (!commands.empty())
                {
                    direction = commands.front();
                    commands.pop_front();
                }
            }
        }
    }
}

std::vector<CaseType> *Snake::getDisplayMap()
{
    return (&this->map);
}
