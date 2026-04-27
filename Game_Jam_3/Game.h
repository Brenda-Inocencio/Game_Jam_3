#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

class Player;
class Background;
class Level;

class Game {
	std::vector<Background*> bgs;
	std::vector<Level*> levels;
	Background* bg;
	int currentLevel;
	bool playerInterract;
public:
	Game();
	~Game();

	void Update(float dt, float now, Player* player, std::vector<sf::Event> events);

	void Render(sf::RenderWindow& window, Player* player);
};