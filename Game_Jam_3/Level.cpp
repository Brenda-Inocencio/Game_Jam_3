#include "Level.h"
#include "Background.h"
#include "Trap.h"

Level::Level(Background* bg, int lvl) {
	levelBg = bg;
	if (lvl == 0) {
		traps.push_back(new Ground(sf::Vector2f(0, 900), sf::Vector2f(1920, 200), 0));
	}
	if (lvl == 1) {
		//objs.push_back(new Door(sf::Vector2f(0.f, 500.f), 0));
		//objs.push_back(new Door(sf::Vector2f(1700.f, 500.f), 1));
		//objs.push_back(new TV(sf::Vector2f(950.f, 400.f)));
	}
	if (lvl == 2) {
		//objs.push_back(new Door(sf::Vector2f(0.f, 500.f), 0));
		//objs.push_back(new Fridge(sf::Vector2f(1550.f, 300.f)));
	}
}

Level::~Level() {
	for (int i = 0; i < traps.size(); i++) {
		if (traps[i]) {
			delete traps[i]; traps[i] = nullptr;
		}
	}
}

void Level::Render(sf::RenderWindow& window) {
	levelBg->Render(window);
	for (int i = 0; i < traps.size(); i++) {
		traps[i]->Render(window);
	}
}