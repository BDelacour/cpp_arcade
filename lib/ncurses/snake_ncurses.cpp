#include <unistd.h>
#include <ncurses.h>
#include "libNcurses.h"
#include "IDisplay.h"

extern "C"
{
libNcurses *create_display(void (*f)(EventType), std::mutex *mtx)
{
    return (new libNcurses(f, mtx));
}
};

libNcurses::libNcurses(void (*f)(EventType), std::mutex *mtx)
{
    this->event_handler = f;
    this->loop = true;
    this->mtx = mtx;
}

libNcurses::~libNcurses()
{
}

void drawMap(int x, int y, std::vector<CaseType> &map)
{
    for (int i = 0; i < x * y; i++)
    {
        switch (map[i])
        {
            case CaseType::WALL:
                move(i / x, i % x);
                addch((char) 219);
                break;
            case CaseType::SNAKE:
                move(i / x, i % x);
                addch('x');
                break;
            case CaseType::POWERUP:
                move(i / x, i % x);
                addch('*');
                break;
            default:
                move(i / x, i % x);
                addch(' ');
                break;
        }
    }
}

int  libNcurses::initDisplay(int x, int y)
{
    this->width = x;
    this->height = y;
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    timeout(50);
    for (int i = 0; i < y; i++)
    {
        move(i, x);
        addch('|');
    }
    for (int i = 0; i < x; i++)
    {
        move(y, i);
        addch('-');
    }
    move(y, x);
    addch('+');
    return (0);
}

void libNcurses::getKey()
{
    int keyPressed;

    keyPressed = getch();
    switch (keyPressed)
    {
        case KEY_UP:
            this->event_handler(EventType::UP);
            break;
        case KEY_DOWN:
            this->event_handler(EventType::DOWN);
            break;
        case KEY_LEFT:
            this->event_handler(EventType::LEFT);
            break;
        case KEY_RIGHT:
            this->event_handler(EventType::RIGHT);
            break;
        case 27:
            this->event_handler(EventType::ESCAPE);
            this->loop = false;
            break;
        case (int(' ')):
            this->event_handler(EventType::SPACE);
            break;
        case KEY_ENTER:
            this->event_handler(EventType::ENTER);
            break;
        case KEY_A1:
            this->event_handler(EventType::NUM_1);
            break;
        case KEY_A3:
            this->event_handler(EventType::NUM_3);
            break;
        case KEY_B2:
            this->event_handler(EventType::NUM_5);
            break;
        case KEY_C1:
            this->event_handler(EventType::NUM_7);
            break;
        case KEY_C3:
            this->event_handler(EventType::NUM_9);
            break;
        default:
            break;
    }
}

int    libNcurses::delDisplay()
{
    this->loop = false;
    return (0);
}

void    libNcurses::displayMap(std::vector<CaseType> &map)
{
    while (this->loop)
    {
        this->getKey();
        this->mtx->lock();
        drawMap(this->width, this->height, map);
        this->mtx->unlock();
        refresh();
    }
    printw("GAME OVER");
    endwin();
}