#include "Trap.h"


Trap::Trap() : posx(0.f), posy(0.f), width(128.f), height(90), trapPos(0.f, 0.f), type("Trap"), isActive(false) {
	rect = sf::RectangleShape(sf::Vector2f(width, height));
	rect.setPosition(sf::Vector2f(posx, posy));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Blue);
	rect.setOutlineThickness(2.f);

	rectTrap = sf::RectangleShape(sf::Vector2f(width, height));
	rectTrap.setPosition(sf::Vector2f(trapPos));
	rectTrap.setFillColor(sf::Color::Transparent);
	rectTrap.setOutlineColor(sf::Color::Magenta);
	rectTrap.setOutlineThickness(2.f);
}

Trap::~Trap() {}

void Trap::Render(sf::RenderWindow& window) {
	rectTrap.setPosition(sf::Vector2f(trapPos));
	window.draw(rect);

	window.draw(rectTrap);
}


Ground::Ground(sf::Vector2f(pos), sf::Vector2f(_trapPos), int _type, bool _isAcvtive) {
	isActive = _isAcvtive;
	posx = pos.x;
	posy = pos.y;
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
	rect.setPosition(pos);
}

Egg::Egg(sf::Vector2f(pos)) {
	rectTrap.setSize(sf::Vector2f(0, 0));
	posx = pos.x;
	posy = pos.y;
	type = "Egg";
	rect.setFillColor(sf::Color::Cyan);
	rect.setPosition(pos);
}

Pike::Pike(sf::Vector2f(pos), sf::Vector2f(_trapPos), int _type, bool _isAcvtive) {
	isActive = _isAcvtive;
	posx = pos.x;
	posy = pos.y;
	trapPos = _trapPos;
	type = "Pike";
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(pos);
}

Tramplin::Tramplin(sf::Vector2f(pos), sf::Vector2f(_trapPos), int _type, bool _isAcvtive) {
	isActive = _isAcvtive;
	posx = pos.x;
	posy = pos.y;
	trapPos = _trapPos;
	type = "Tramplin";
	rect.setFillColor(sf::Color::Green);
	rect.setPosition(pos);
}

Spawn::Spawn(sf::Vector2f(pos)) {
	rectTrap.setSize(sf::Vector2f(0, 0));
	posx = pos.x;
	posy = pos.y;
	type = "Spawn";
	rect.setPosition(pos);
}

TrapTrigger::TrapTrigger(Vector2f(pos), int trap) {

}
