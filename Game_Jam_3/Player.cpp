#define HITBOX

#include "Player.h"
#include "Trap.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

#define TIME_JUMP 0.5f
#define TIME_INVULNERABLE 2.f
#define PLAYER_SPEED 200.f
#define JUMP_SPEED 200.f
#define FALL_SPEED 150.f

Player::Player() : width(64.f), height(64.f), posx(200.f), posy(600.f), speed(0.f), jumpingTime(0.f),
dir(1), state(IDLE), isJump(false), isAlive(true), moveLeft(false), moveRight(false) {
	rect = sf::RectangleShape(sf::Vector2f(width, height));
	rect.setPosition(sf::Vector2f(posx, posy));
	rect.setFillColor(sf::Color::Yellow);

	tex = new sf::Texture("assets/chicken.png");
	sprite = new sf::Sprite(*tex);
	sprite->setScale(sf::Vector2f(0.65, 0.65));
	sprite->setPosition(sf::Vector2f(posx - 10, posy - 10));


}

Player::~Player() {
	if (tex) {
		delete tex;
		tex = nullptr;
	}
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
}

void Player::Render(sf::RenderWindow& window) {
	window.draw(*sprite);

#ifdef HITBOX
	// Hitbox verte
	sf::RectangleShape hitbox(sf::Vector2f(width, height));
	hitbox.setPosition(sf::Vector2f(posx, posy));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Green);
	hitbox.setOutlineThickness(2.f);
	//window.draw(hitbox);
#endif
}

Player::State Player::processEvent(std::vector<sf::Event>& events, float now) {
	State newState = state;
	for (auto& event : events) {
		switch (state) {
		case IDLE:
			if (event.is<sf::Event::KeyPressed>()) {
				if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space) {
					newState = JUMPING;
					isJump = true;
					jumpingTime = now;
				}
				else if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Q) {
					moveLeft = true;
					speed = -PLAYER_SPEED;
					dir = -1;
				}
				else if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D) {
					moveRight = true;
					speed = PLAYER_SPEED;
					dir = 1;
				}
			}
			else if (event.getIf<sf::Event::KeyReleased>()) {
				if ((event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Q)) {
					moveLeft = false;
					if (moveRight) {
					}
					else {
						speed = 0;
					}
				}
				else if ((event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::D)) {
					moveRight = false;
					if (moveLeft) {
					}
					else {
						speed = 0;
					}
				}
			}
			break;
		case Player::JUMPING:
			if (event.is<sf::Event::KeyPressed>()) {				
				if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Q) {
					moveLeft = true;
					speed = -PLAYER_SPEED;
					dir = -1;
				}
				else if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D) {
					moveRight = true;
					speed = PLAYER_SPEED;
					dir = 1;
				}
			}
			else if (event.getIf<sf::Event::KeyReleased>()) {
				if ((event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Q)) {
					moveLeft = false;
					if (moveRight) {
					}
					else {
						speed = 0;
					}
				}
				else if ((event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::D)) {
					moveRight = false;
					if (moveLeft) {
					}
					else {
						speed = 0;
					}
				}
			}
			break;
		case Player::FALLING:
			if (event.is<sf::Event::KeyPressed>()) {
				if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Q) {
					moveLeft = true;
					speed = -PLAYER_SPEED;
					dir = -1;
				}
				else if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D) {
					moveRight = true;
					speed = PLAYER_SPEED;
					dir = 1;
				}
			}
			else if (event.getIf<sf::Event::KeyReleased>()) {
				if ((event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Q)) {
					moveLeft = false;
					if (moveRight) {
					}
					else {
						speed = 0;
					}
				}
				else if ((event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::D)) {
					moveRight = false;
					if (moveLeft) {
					}
					else {
						speed = 0;
					}
				}
			}
			break;
		default:
			break;
		}
	}
	return newState;
}


void Player::Update(float dt, float now, std::vector<sf::Event>& events, std::vector<Trap*>& traps) {
	rect.setPosition(sf::Vector2f(posx, posy));
	sprite->setPosition(sf::Vector2f(posx - 10, posy - 10));
	State newState = processEvent(events, now);
	SideCollide(traps);
	if (moveLeft && !moveRight) {
		speed = -PLAYER_SPEED;
		posx += speed * dt;

	}
	else if (moveRight && !moveLeft) {
		speed = PLAYER_SPEED;
		posx += speed * dt;
	}

	switch (state) {
	case Player::IDLE:
		isJump = false;
		if (!DownCollide(traps)) {
			newState = FALLING;
		}
		break;
	case Player::JUMPING:
		if (isJump) {
			isJump = false;
		}
		/*if (UpCollide(traps)) {
			newState = FALLING;
		}*/
		else {
			Jump(dt, now, newState, traps);
		}
		break;
	case Player::FALLING:
		Fall(dt, now, newState, traps);
		break;
	default:
		break;
	}

	//VoidCollide(blocks);

	/*if (now - vulnerableTime >= TIME_INVULNERABLE) {
		isVulnerable = true;
	}*/

	state = newState;
}

void Player::Jump(float dt, float now, State& newState, std::vector<Trap*>& traps) {
	if (now - jumpingTime <= TIME_JUMP) {
		if (moveLeft && !moveRight) {
			speed = -PLAYER_SPEED;
		}
		else if (moveRight && !moveLeft) {
			speed = PLAYER_SPEED;
		}
		posy -= JUMP_SPEED * dt;
		posx += speed * dt;
	}
	else {
		newState = FALLING;
	}
}

void Player::Fall(float dt, float now, State& newState, std::vector<Trap*>& traps) {
	if (!DownCollide(traps)) {
		posy += FALL_SPEED * dt;
		posx += speed * dt;
	}
	else {
		newState = IDLE;
	}
}

bool Player::DownCollide(std::vector<Trap*>& traps) {
	for (auto* t : traps) {
		if (t->GetType() == "GroundUntrapped" || (t->GetType() == "GroundTrapped" && !t->isActive)) {
			if (t->GetPosY() >= posy && t->GetPosY() <= posy + height) {
				if ((posx >= t->GetPosX() && posx <= t->GetRightX()) ||
					(posx + width <= t->GetRightX() && posx + width >= t->GetPosX())) {

					posy = t->GetPosY() - height;
					return true;
				}
			}
		}
	}
	return false;
}

void Player::SideCollide(std::vector<Trap*>& traps) {
	for (auto* t : traps) {
		if (t->GetType() == "GroundUntrapped" || (t->GetType() == "GroundTrapped" && !t->isActive)) {
			if (speed > 0) {
				if (posx + width >= t->GetPosX() && posx + width <= t->GetRightX() &&
					t->GetPosY() >= posy && t->GetBottomY() <= posy + height) {

					posx = t->GetPosX() - width - 2;
					
				}
			}
			else if (speed < 0) {
				if (posx <= t->GetRightX() && posx >= t->GetPosX() &&
					t->GetPosY() >= posy && t->GetBottomY() <= posy + height) {

					posx = t->GetRightX() + 1;
					
				}
			}
		}
	}
	if (posx <= 0) {
		posx = 0;
	}
	else if (posx + width >= 1920) {
		posx = 1920 - width;
	}
}

//bool Player::UpCollide(std::vector<Block*>& blocks) {
//	for (auto* bl : blocks) {
//		if (bl->GetBlockType() == "Block") {
//			if ((bl->GetBottomY() >= posy && bl->GetPosY() <= posy)) {
//				if ((bl->GetPosX() >= posx && bl->GetPosX() <= posx + width)) {
//					return true;
//				}
//			}
//		}
//	}
//	return false;
//}

//void Player::VoidCollide(std::vector<Block*>& blocks) {
//	for (auto* bl : blocks) {
//		if (bl->GetBlockType() == "DeathBlock") {
//			if (bl->GetBottomY() >= posy && bl->GetPosY() <= posy) {
//				isAlive = false;
//			}
//		}
//	}
//}

