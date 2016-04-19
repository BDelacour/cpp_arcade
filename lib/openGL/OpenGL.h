#ifndef OPENGL_OPENGL_H
# define OPENGL_OPENGL_H
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# include "IDisplay.h"
# include <SDL/SDL.h>
# include <GL/gl.h>
# include <GL/glu.h>
# include <mutex>

void drawMap(int, int, std::vector<CaseType> &);

class libOpenGL: public IDisplay
{
public:
    libOpenGL(void (*f)(EventType), std::mutex *);
    virtual ~libOpenGL();
    virtual int initDisplay(int x, int y);
    virtual int delDisplay();
    virtual void displayMap(std::vector<CaseType> &map);

private:
    void    gereKey(SDL_Event &);
    int     width, height;
    bool    loop;
    std::mutex  *mtx;
};

#endif //OPENGL_OPENGL_H
