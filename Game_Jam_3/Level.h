#pragma once
#include <SFML/Graphics.hpp>

class Background;
class Objects;

class Level {
	Background* levelBg;
public:
	std::vector<Objects*> objs;

	Level(Background* bg, int lvl);
	~Level();

	void Render(sf::RenderWindow& window);
};