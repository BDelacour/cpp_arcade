#ifndef CPP_ARCADE_IDISPLAY_H_
#define CPP_ARCADE_IDISPLAY_H_

#include <iostream>
#include <vector>

#define SIZE_SCREEN_X 1000
#define SIZE_SCREEN_Y 625

enum CaseType : int32_t
{
	EMPTY = 0,
	WALL = 1,
	SNAKE = 2,
	POWERUP = 3
};

enum class EventType : int16_t
{
	SPACE = 0,
	ENTER = 1,
	ESCAPE = 2,
	UP = 3,
	DOWN = 4,
	RIGHT = 5,
	LEFT = 6,
	NUM_1 = 7,
	NUM_2 = 8,
	NUM_3 = 9,
	NUM_4 = 10,
	NUM_5 = 11,
	NUM_6 = 12,
	NUM_7 = 13,
	NUM_8 = 14,
	NUM_9 = 15,
	NUM_0 = 16
};

class IDisplay
{
protected:
	void    (*event_handler)(EventType key);

public:
	virtual ~IDisplay()
	{
		std::cout << "IDisplay deleted" << std::endl;
	}
/*
	virtual int init();
*/
	virtual int initDisplay(unsigned int x, unsigned int y) = 0;
	virtual int delDisplay() = 0;
	virtual void displayMap(std::vector<CaseType> &map) = 0;
};

#endif //CPP_ARCADE_IDISPLAY_H_
