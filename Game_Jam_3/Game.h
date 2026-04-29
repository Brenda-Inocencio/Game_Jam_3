#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

class Player;
class Background;
class Level;

class Game {
	std::vector<Level*> levels;
	Background* bg;
	Player* player;
	int currentLevel;
	bool playerInterract;
public:
	Game();
	~Game();

	void InitSpawn();

	void Update(float dt, float now, std::vector<sf::Event> events);

	void Render(sf::RenderWindow& window);
};