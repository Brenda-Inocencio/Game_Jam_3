#include "Trap.h"


Trap::Trap() : posx(0.f), posy(0.f), posCharacter(0), lineCharacter(0), width(128.f), height(90), type("Trap"), isActive(false) {
	rect = sf::RectangleShape(sf::Vector2f(width, height));
	rect.setPosition(sf::Vector2f(posx, posy));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Blue);
	rect.setOutlineThickness(2.f);
}

Trap::~Trap() {}

void Trap::Render(sf::RenderWindow& window) {
	window.draw(rect);
}

void Trap::Update(std::vector<Trap*>& traps) {
	for (auto* t : traps) {
		if (t->type == "GroundUntrapped") {
			if (!isActive) {
				rect.setFillColor(sf::Color::Black);
			}
			if (isActive) { // actif = trou
				rect.setFillColor(sf::Color::Transparent);
			}
		}
	}
}

Ground::Ground(sf::Vector2f(pos), int _type, bool _isAcvtive, int i, int ln) {
	posCharacter = i;
	lineCharacter = ln;
	isActive = _isAcvtive;
	posx = pos.x;
	posy = pos.y;
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

Egg::Egg(sf::Vector2f(pos), int i, int ln) {
	posCharacter = i;
	lineCharacter = ln;
	posx = pos.x;
	posy = pos.y;
	width = 50;
	type = "Egg";
	rect.setFillColor(sf::Color::Cyan);
	rect.setPosition(pos);
}

Pike::Pike(sf::Vector2f(pos), int _type, bool _isAcvtive, int i, int ln) {
	posCharacter = i;
	lineCharacter = ln;
	isActive = _isAcvtive;
	posx = pos.x;
	posy = pos.y;
	type = "Pike";
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(pos);
}

Tramplin::Tramplin(sf::Vector2f(pos), int _type, bool _isAcvtive, int i, int ln) {
	posCharacter = i;
	lineCharacter = ln;
	isActive = _isAcvtive;
	posx = pos.x;
	posy = pos.y;
	type = "Tramplin";
	rect.setFillColor(sf::Color::Green);
	rect.setPosition(pos);
}

Spawn::Spawn(sf::Vector2f(pos), int i, int ln) {
	posCharacter = i;
	lineCharacter = ln;
	posx = pos.x;
	posy = pos.y;
	type = "Spawn";
	rect.setPosition(pos);
}

TrapTrigger::TrapTrigger(sf::Vector2f(pos), int trap, int i, int ln) {
	posCharacter = i;
	lineCharacter = ln;
	posx = pos.x;
	posy = pos.y;
	type = "TrapTrigger"; 
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Magenta);
	rect.setOutlineThickness(2.f);
	rect.setPosition(pos);
	switch (trap) {
	case 0:
		type += "0";
		break;
	case 1:
		type += "1";
		break;
	default:
		break;
	}
}
