#ifndef NCURSES_H_
# define NCURSES_H_

# include <mutex>
# include "IDisplay.h"

void drawMap(int, int, std::vector<CaseType> &);

class libNcurses : public IDisplay
{
public:
    libNcurses(void (*f)(EventType), std::mutex *);
    virtual    ~libNcurses();
    virtual int initDisplay(int x, int y);
    virtual int delDisplay();
    virtual void displayMap(std::vector<CaseType> &map);

private:
    void getKey();

    int width, height;
    bool loop;
    std::mutex *mtx;
};

#endif	/* !NCURSES_H_ */
