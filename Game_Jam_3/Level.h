#pragma once
#include <SFML/Graphics.hpp>

class Background;
class Trap;

class Level {
	Background* levelBg;
public:
	std::vector<Trap*> traps;
public:
	Level(Background* bg, int lvl);
	~Level();

	void Render(sf::RenderWindow& window);
};