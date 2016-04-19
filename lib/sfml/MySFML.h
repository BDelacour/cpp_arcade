//
// Created by bauer-a on 30/03/16.
//

#ifndef SFML_SFML_H
#define SFML_SFML_H

#include "SFML/Graphics.hpp"
#include "IDisplay.h"

class MySFML : public IDisplay
{
protected:
	unsigned int        map_size_x;
	unsigned int        map_size_y;
	sf::RenderWindow    *window;
	bool                endDisplay;
	std::mutex          *myMutex;

public:
	MySFML();
	MySFML(void (*_event_handler)(EventType), std::mutex *mtx);
	~MySFML();
	int     initDisplay(unsigned int x, unsigned int y);
	int     delDisplay();
	void    displayMap(std::vector<CaseType> &map);
};

#endif //SFML_SFML_H
