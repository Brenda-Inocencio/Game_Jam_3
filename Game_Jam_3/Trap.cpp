#include "Trap.h"


Trap::Trap() : posx(0.f), posy(0.f), width(128.f), height(90), type("Trap"), isActive(false) {
	rect = sf::RectangleShape(sf::Vector2f(width, height));
	rect.setPosition(sf::Vector2f(posx, posy));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Blue);
	rect.setOutlineThickness(2.f);

	tex = new sf::Texture("assets/pick.png");
	sprite = new sf::Sprite(*tex);
	sprite->setScale(sf::Vector2f(0.65, 0.65));
	sprite->setPosition(sf::Vector2f( - 1000, - 1000));

}

Trap::~Trap() {}

void Trap::Render(sf::RenderWindow& window) {
	window.draw(rect);
	window.draw(*sprite);
}

void Trap::Update() {
	if (type == "GroundTrapped") {
		if (!isActive) {
			rect.setFillColor(sf::Color::Black);
		}
		if (isActive) { // active = void
			rect.setFillColor(sf::Color::Transparent);
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
	width = 72;
	height = 162;
	type = "Egg";
	rect.setSize(sf::Vector2f(width - 22, height));
	rect.setFillColor(sf::Color::Transparent);
	rect.setPosition(pos);
	tex = new sf::Texture("assets/egg.png");
	sprite = new sf::Sprite(*tex);
	sprite->setScale(sf::Vector2f(0.70, 0.70));
	sprite->setPosition(sf::Vector2f(posx, posy));
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
	sprite->setPosition(sf::Vector2f(posx - 10, posy - 10));
	sprite->setScale(sf::Vector2f(0.65, 0.65));
	sprite->setPosition(sf::Vector2f(posx, posy));

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
	rect.setFillColor(sf::Color::Transparent);
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
