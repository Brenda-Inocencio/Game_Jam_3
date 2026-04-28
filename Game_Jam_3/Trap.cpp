#include "Trap.h"


Trap::Trap() : posx(0.f), posy(0.f), width(128.f), height(90), trapPos(0.f, 0.f), type("Trap"), isActive(false) {
	rect = sf::RectangleShape(sf::Vector2f(width, height));
	rect.setPosition(sf::Vector2f(posx, posy));
	rect.setFillColor(sf::Color::Transparent);
	rectTrap.setPosition(sf::Vector2f(trapPos));
	rectTrap.setFillColor(sf::Color::Transparent);
}

Trap::~Trap() {
}

void Trap::Render(sf::RenderWindow& window) {
	window.draw(rect);

	rectTrap.setOutlineColor(sf::Color::Red);
	rectTrap.setOutlineThickness(2.f);
	//window.draw(rectTrap);
}


Ground::Ground(sf::Vector2f(pos), sf::Vector2f(size), sf::Vector2f(_trapPos), int _type, bool _isAcvtive) {
	isActive = _isAcvtive;
	posx = pos.x;
	posy = pos.y;
	width = size.x;
	height = size.y;
	trapPos = _trapPos;
	type = "Ground";
	if (_type == 1) {
		type += "Trapped";
	}
	else {
		type += "Untrapped";
	}
	if (!isActive) {
		rect.setFillColor(sf::Color::Black);
	}
	if (isActive) { // actif = trou
		rect.setFillColor(sf::Color::Transparent);
	}
	rect.setSize(size);
	rect.setPosition(pos);
}
