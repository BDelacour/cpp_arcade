#include <unistd.h>
#include "OpenGL.h"

extern "C"
{
libOpenGL *create_display(void (*f)(EventType), std::mutex *mtx)
{
    return (new libOpenGL(f, mtx));
}
};

libOpenGL::libOpenGL(void (*f)(EventType), std::mutex *mtx)
{
    this->mtx = mtx;
    this->event_handler = f;
    this->loop = true;
}

libOpenGL::~libOpenGL()
{
}

int libOpenGL::initDisplay(int x, int y)
{
    this->height = y;
    this->width = x;
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        return (1);
    SDL_WM_SetCaption("Arcade", NULL);
    if (SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_OPENGL) == NULL)
        return (1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(0.27, 0.51, 0.71, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    gluPerspective(70, (double) WINDOW_WIDTH / WINDOW_HEIGHT, 1, 1000);
    return (0);
}

int libOpenGL::delDisplay()
{
    this->loop = false;
    return (0);
}

void libOpenGL::gereKey(SDL_Event &event)
{
    if (event.type == SDL_QUIT)
        this->loop = false;
    if (event.type == SDL_KEYDOWN)
        switch (event.key.keysym.sym)
        {
            case SDLK_UP:
                this->event_handler(EventType::UP);
                break;
            case SDLK_DOWN:
                this->event_handler(EventType::DOWN);
                break;
            case SDLK_LEFT:
                this->event_handler(EventType::LEFT);
                break;
            case SDLK_RIGHT:
                this->event_handler(EventType::RIGHT);
                break;
            case SDLK_ESCAPE:
                this->event_handler(EventType::ESCAPE);
                this->loop = false;
                break;
            case SDLK_SPACE:
                this->event_handler(EventType::SPACE);
                break;
            case SDLK_RETURN:
                this->event_handler(EventType::ENTER);
                break;
            case SDLK_0:
                this->event_handler(EventType::NUM_0);
                break;
            case SDLK_1:
                this->event_handler(EventType::NUM_1);
                break;
            case SDLK_2:
                this->event_handler(EventType::NUM_2);
                break;
            case SDLK_3:
                this->event_handler(EventType::NUM_3);
                break;
            case SDLK_4:
                this->event_handler(EventType::NUM_4);
                break;
            case SDLK_5:
                this->event_handler(EventType::NUM_5);
                break;
            case SDLK_6:
                this->event_handler(EventType::NUM_6);
                break;
            case SDLK_7:
                this->event_handler(EventType::NUM_7);
                break;
            case SDLK_8:
                this->event_handler(EventType::NUM_8);
                break;
            case SDLK_9:
                this->event_handler(EventType::NUM_9);
                break;
            default:
                break;
        }
}

void libOpenGL::displayMap(std::vector<CaseType> &map)
{
    SDL_Event event;
    Uint32 ellapsedTime, startTime;

    while (this->loop)
    {
        startTime = SDL_GetTicks();
        while (SDL_PollEvent(&event))
            this->gereKey(event);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->mtx->lock();
        drawMap(this->width, this->height, map);
        this->mtx->unlock();
        glFlush();
        SDL_GL_SwapBuffers();
        ellapsedTime = SDL_GetTicks() - startTime;
        if (ellapsedTime < 10)
            SDL_Delay(10 - ellapsedTime);
    }
    SDL_Quit();
}
