#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

struct Texture;
struct Sprite;
class Trap;

class Level {
	std::string prevLevel;
	std::string nextLevel;

	float spawnPosX;
	float spawnPosY;

public:
	std::vector<Trap*> traps;

	Level();
	Level(std::string path1);
	~Level();
	void Render(sf::RenderWindow& window);
	void Update();

	float GetSpawnPosX() { return spawnPosX; }
	float GetSpawnPosY() { return spawnPosY; }

	inline std::string GetPrevLevel() { return prevLevel; }
	inline std::string GetNextLevel() { return nextLevel; }
};