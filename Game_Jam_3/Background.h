#pragma once
#include <SFML/Graphics.hpp>

class Background {
	sf::RectangleShape rect;
	float width;
	float height;
public:
	Background();
	~Background();
	void Render(sf::RenderWindow& window);
	void Update();
};

