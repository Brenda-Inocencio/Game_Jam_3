#include "Trap.h"


Trap::Trap() : posx(0.f), posy(0.f), width(48.f), height(72), type("Trap"), isActive(false) {
	rect = sf::RectangleShape(sf::Vector2f(width, height));
	rect.setPosition(sf::Vector2f(posx, posy));
	rect.setFillColor(sf::Color::Transparent);
}

Trap::~Trap() {
}

void Trap::Render(sf::RenderWindow& window) {
	window.draw(rect);

	sf::RectangleShape hitbox(sf::Vector2f(width, height));
	hitbox.setPosition(sf::Vector2f(posx, posy));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2.f);
	//window.draw(hitbox);
}


Ground::Ground(sf::Vector2f(pos), sf::Vector2f(size), int _type) {
	posx = pos.x;
	posy = pos.y;
	width = size.x;
	height = size.y;
	type = "Ground";
	if (_type == 1) {
		type += "Trapped";
	}
	else {
		type += "Untrapped";
	}
	rect.setFillColor(sf::Color::Black);
	rect.setSize(size);
	rect.setPosition(pos);
}
