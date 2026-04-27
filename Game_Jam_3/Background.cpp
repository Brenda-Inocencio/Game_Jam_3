#include "Background.h"

Background::Background() : width(1920), height(1080) { 
	bg = sf::RectangleShape(sf::Vector2f(width, height));
	bg.setFillColor(sf::Color(150, 150, 150, 255));
}

Background::~Background() {
}

void Background::Render(sf::RenderWindow& window) {
	window.draw(bg);
}
