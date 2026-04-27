#include "Level.h"
//#include "Background.h"
//#include "Objects.h"

Level::Level(Background* bg, int lvl) {
	levelBg = bg;
	if (lvl == 0) {
		//objs.push_back(new Door(sf::Vector2f(1700.f, 500.f), 1));
		//objs.push_back(new Computer(sf::Vector2f(1300.f, 450.f)));
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
	for (int i = 0; i < objs.size(); i++) {
		if (objs[i]) {
			delete objs[i]; objs[i] = nullptr;
		}
	}
}

//void Level::Render(sf::RenderWindow& window) {
//	window.draw(*levelBg->bg);
//	for (int i = 0; i < objs.size(); i++) {
//		objs[i]->Render(window);
//	}
//}