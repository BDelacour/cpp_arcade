//
// Created by bauer-a on 30/03/16.
//

#include <mutex>
#include <map>
#include <algorithm>
#include <SFML/Graphics/RenderWindow.hpp>
#include "MySFML.h"

extern "C"
{
IDisplay *create_display(void (*event_handler)(EventType), std::mutex *mtx)
{
	return (new MySFML(event_handler, mtx));
}
}

MySFML::MySFML()
{
	this->map_size_x = 0;
	this->map_size_y = 0;
}

MySFML::MySFML(void (*_event_handler)(EventType), std::mutex *mtx)
{
	this->map_size_x = 0;
	this->map_size_y = 0;
	this->event_handler = _event_handler;
	this->myMutex = mtx;
}

MySFML::~MySFML()
{
}

int         MySFML::initDisplay(unsigned int x, unsigned int y)
{
	this->map_size_x = x;
	this->map_size_y = y;
	this->endDisplay = false;
	this->window = new sf::RenderWindow(sf::VideoMode(1000, 625), "MySFML");
	return (0);
}

EventType match_keyboard(sf::Keyboard::Key key)
{
	static std::map<sf::Keyboard::Key, EventType> matching_map = {{sf::Keyboard::Num0,   EventType::NUM_0},
	                                                              {sf::Keyboard::Num1,   EventType::NUM_1},
	                                                              {sf::Keyboard::Num2,   EventType::NUM_2},
	                                                              {sf::Keyboard::Num3,   EventType::NUM_3},
	                                                              {sf::Keyboard::Num4,   EventType::NUM_4},
	                                                              {sf::Keyboard::Num5,   EventType::NUM_5},
	                                                              {sf::Keyboard::Num6,   EventType::NUM_6},
	                                                              {sf::Keyboard::Num7,   EventType::NUM_7},
	                                                              {sf::Keyboard::Num8,   EventType::NUM_8},
	                                                              {sf::Keyboard::Num9,   EventType::NUM_9},
	                                                              {sf::Keyboard::Space,  EventType::SPACE},
	                                                              {sf::Keyboard::Return, EventType::ENTER},
	                                                              {sf::Keyboard::Escape, EventType::ESCAPE},
	                                                              {sf::Keyboard::Up,     EventType::UP},
	                                                              {sf::Keyboard::Down,   EventType::DOWN},
	                                                              {sf::Keyboard::Right,  EventType::RIGHT},
	                                                              {sf::Keyboard::Left,   EventType::LEFT}};
	return (matching_map[key]);
}

void        MySFML::displayMap(std::vector<CaseType> &map)
{
	float size_case = std::min(SIZE_SCREEN_X / this->map_size_x, SIZE_SCREEN_Y / this->map_size_y);

	this->window->clear();
	sf::CircleShape circle(size_case / 2);
	sf::RectangleShape rect(sf::Vector2f(size_case, size_case));
	while (this->window->isOpen() && !this->endDisplay)
	{
		sf::Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
				this->event_handler(match_keyboard(event.key.code));
		}
		this->window->clear();
		this->myMutex->lock();
		for (unsigned int i = 0; i < map.size(); ++i)
		{
			switch (map.at(i))
			{
				case SNAKE:
					circle.setFillColor(sf::Color::Green);
					circle.setPosition((i % this->map_size_x) * size_case, ((i / this->map_size_y) * size_case));
					this->window->draw(circle);
					break;
				case WALL:
					rect.setFillColor(sf::Color::Blue);
					rect.setPosition((i % this->map_size_x) * size_case, ((i / this->map_size_y) * size_case));
					this->window->draw(rect);
					break;
				case POWERUP:
					circle.setFillColor(sf::Color::Red);
					circle.setPosition((i % this->map_size_x) * size_case, ((i / this->map_size_y) * size_case));
					this->window->draw(circle);
					break;
				default:
					rect.setFillColor(sf::Color::Black);
					rect.setPosition((i % this->map_size_x) * size_case, ((i / this->map_size_y) * size_case));
					this->window->draw(rect);
					break;
			}
		}
		this->myMutex->unlock();
		this->window->display();
	}
}

int     MySFML::delDisplay()
{
	this->endDisplay = true;
	this->window->close();
	return (0);
}
