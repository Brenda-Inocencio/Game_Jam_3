#define HITBOX

#include "Player.h"
#include <iostream>

#define TIME_JUMP 0.75f
#define TIME_ATTACK 0.5f
#define TIME_DODGE 0.2f
#define TIME_INVULNERABLE 2.f
#define PLAYER_SPEED 150.f
#define JUMP_SPEED 300.f
#define FALL_SPEED 300.f

Player::Player() : width(120.f), height(150.f), posx(200.f), posy(1300.f), speed(0.f), jumpingTime(0.f),
dir(1), state(IDLE), isJump(false), isAlive(true), moveLeft(false), moveRight(false) {
	rect = sf::RectangleShape(sf::Vector2f(width, height));
	rect.setPosition(sf::Vector2f(posx, posy));
	rect.setFillColor(sf::Color::Yellow);
	
}

void Player::Render(sf::RenderWindow& window) {
	rect.setPosition(sf::Vector2f(posx, posy));
	window.draw(rect);

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

void Player::Update(float dt, float now, std::vector<sf::Event>& events) {
	State newState = processEvent(events, now);

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
		/*if (!DownCollide(blocks)) {
			newState = FALLING;
		}*/
		break;
	case Player::JUMPING:
		if (isJump) {
			isJump = false;
		}
		/*if (UpCollide(blocks)) {
			newState = FALLING;
		}*/
		else {
			//Jump(dt, now, newState, blocks);
		}
		/*if (SideCollide(blocks)) {
			newState = IDLE;
		}*/
		break;
	case Player::FALLING:
		//Fall(dt, now, newState, blocks);
		/*if (SideCollide(blocks)) {
			newState = IDLE;
		}*/
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

//void Player::Jump(float dt, float now, State& newState, std::vector<Block*> blocks) {
//	if (now - jumpingTime <= TIME_JUMP) {
//		if (moveLeft && !moveRight) {
//			speed = -PLAYER_SPEED;
//		}
//		else if (moveRight && !moveLeft) {
//			speed = PLAYER_SPEED;
//		}
//		posy -= JUMP_SPEED * dt;
//		posx += speed * dt;
//	}
//	else {
//		newState = FALLING;
//	}
//}
//
//void Player::Fall(float dt, float now, State& newState, std::vector<Block*> blocks) {
//	if (!DownCollide(blocks)) {
//		posy += FALL_SPEED * dt;
//		posx += speed * dt;
//	}
//	else {
//		newState = IDLE;
//		changeLevel = now;
//	}
//}

//bool Player::DownCollide(std::vector<Block*>& blocks) {
//	for (auto* bl : blocks) {
//		if (bl->GetBlockType() == "Block") {
//			if (bl->GetPosY() >= posy && bl->GetPosY() <= posy + height) {
//				if ((posx >= bl->GetPosX() && posx <= bl->GetRightX()) ||
//					(posx + width <= bl->GetRightX() && posx + width >= bl->GetPosX())) {
//
//					posy = bl->GetPosY() - height;
//					return true;
//				}
//			}
//		}
//	}
//	return false;
//}

//bool Player::SideCollide(std::vector<Block*>& blocks) {
//	for (auto* bl : blocks) {
//		if (bl->GetBlockType() == "Block" || bl->GetBlockType() == "Item") {
//			if (speed > 0) {
//				if (posx + width >= bl->GetPosX() && posx + width <= bl->GetRightX() &&
//					bl->GetPosY() >= posy && bl->GetBottomY() <= posy + height) {
//					if (bl->GetBlockType() == "Block") {
//						posx = bl->GetPosX() - width - 2;
//						return true;
//					}
//					else if (bl->GetBlockType() == "Item") {
//						if (!bl->isUse) {
//							healPoints = 100;
//							bl->isUse = true;
//						}
//					}
//				}
//			}
//			else if (speed < 0) {
//				if (posx <= bl->GetRightX() && posx >= bl->GetPosX() &&
//					bl->GetPosY() >= posy && bl->GetBottomY() <= posy + height) {
//					if (bl->GetBlockType() == "Block") {
//						posx = bl->GetRightX() + 1;
//						return true;
//					}
//					else if (bl->GetBlockType() == "Item") {
//						if (!bl->isUse) {
//							healPoints = 100;
//							bl->isUse = true;
//						}
//					}
//				}
//			}
//		}
//		else if (posx <= 0) {
//			posx = 0;
//			return true;
//		}
//	}
//	return false;
//}

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

