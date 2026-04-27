#include "Background.h"

Background::Background() : width(1920), height(1080) { 
	rect = sf::RectangleShape(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color::White);
}

Background::~Background() {
}

void Background::Render(sf::RenderWindow& window) {
	window.draw(rect);
}
