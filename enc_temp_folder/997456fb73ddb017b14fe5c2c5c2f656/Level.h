#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

struct Texture;
struct Sprite;
class Trap;

class Level {
	std::string prevLevel;
	std::string nextLevel;
	std::ifstream level;

public:
	std::vector<Trap*> traps;

	Level();
	Level(std::string path1);
	~Level();
	void Render(sf::RenderWindow& window);
	void Update();
	void Reset();

	inline std::string GetPrevLevel() { return prevLevel; }
	inline std::string GetNextLevel() { return nextLevel; }
};