#define HITBOX

#include "Player.h"
#include "Trap.h"
#include "Level.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <cstdlib>

#define TIME_JUMP 0.38f
#define PLAYER_SPEED 320.f
#define JUMP_SPEED 500.f
#define FALL_SPEED 500.f

Player::Player() : width(64.f), height(64.f), posx(150.f), posy(800.f), speed(0.f), jumpingTime(0.f),
dir(1), state(IDLE), isJump(false), isAlive(true), moveLeft(false), moveRight(false), deathCount(0), isGravityFlipped(false), gravityFlipTime(0.f) {
    rect = sf::RectangleShape(sf::Vector2f(width, height));
    rect.setPosition(sf::Vector2f(posx, posy));
    rect.setFillColor(sf::Color::Yellow);

    tex = new sf::Texture("assets/chicken.png");
    sprite = new sf::Sprite(*tex);
    sprite->setScale(sf::Vector2f(0.65f, 0.65f));
    sprite->setPosition(sf::Vector2f(posx - 10, posy - 10));

    spawnPosX = posx;
    spawnPosY = posy;
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
    sf::RectangleShape hitbox(sf::Vector2f(width, height));
    hitbox.setPosition(sf::Vector2f(posx, posy));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Green);
    hitbox.setOutlineThickness(2.f);
    window.draw(hitbox);
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
                    if (!moveRight) {
                        speed = 0;
                    }
                }
                else if ((event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::D)) {
                    moveRight = false;
                    if (!moveLeft) {
                        speed = 0;
                    }
                }
            }
            break;
        case JUMPING:
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
                    if (!moveRight) {
                        speed = 0;
                    }
                }
                else if ((event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::D)) {
                    moveRight = false;
                    if (!moveLeft) {
                        speed = 0;
                    }
                }
            }
            break;
        case FALLING:
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
                    if (!moveRight) {
                        speed = 0;
                    }
                }
                else if ((event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::D)) {
                    moveRight = false;
                    if (!moveLeft) {
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

void Player::Update(float dt, float now, std::vector<sf::Event> events, std::vector<Trap*>& traps, Level* lvl){
    rect.setPosition(sf::Vector2f(posx, posy));
    if (dir == -1) {
        sprite->setScale(sf::Vector2f(-0.65f, 0.65f));
        sprite->setPosition(sf::Vector2f(posx + width - 10, posy - 10));
    }
    else {
        sprite->setScale(sf::Vector2f(0.65f, 0.65f));
        sprite->setPosition(sf::Vector2f(posx - 10, posy - 10));
    }

    State newState = processEvent(events, now);

    if (moveLeft && !moveRight) { speed = -PLAYER_SPEED; }
    else if (moveRight && !moveLeft) { speed = PLAYER_SPEED; }
    posx += speed * dt;

    SideCollide(traps, now);

    switch (state) {
    case IDLE:
        isJump = false;
        if (!DownCollide(traps, now)) {
            newState = FALLING;
        }
        break;
    case JUMPING:
        if (isJump) {
            isJump = false;
        }
        if (UpCollide(traps, now)) {
            newState = FALLING;
        }
        else {
            Jump(dt, now, newState, traps);
        }
        break;
    case FALLING:
        Fall(dt, now, newState, traps);
        break;
    default:
        break;
    }

    VoidCollide(traps);
    PikeCollide(traps);
    EggCollide(traps, lvl);

    if (!isAlive) {
        Respawn(lvl);
    }

    state = newState;
}

void Player::Jump(float dt, float now, State& newState, std::vector<Trap*>& traps) {
    if (now - jumpingTime <= TIME_JUMP) {
        posy -= JUMP_SPEED * dt;
    }
    else {
        newState = FALLING;
    }
}

void Player::Fall(float dt, float now, State& newState, std::vector<Trap*>& traps) {
    if (!DownCollide(traps, now)) {
        posy += FALL_SPEED * dt;
    }
    else {
        newState = IDLE;
        isJump = false;
    }
}

bool Player::DownCollide(std::vector<Trap*> traps, float now) {
    for (auto* t : traps) {
        if (t->GetType() == "GroundUntrapped" ||
            (t->GetType() == "GroundTrapped" && !t->isActive) ||
            t->GetType() == "TrapTrigger0" ||
            t->GetType() == "TrapTrigger1" ||
            t->GetType() == "TrapTrigger2" ||
            t->GetType() == "TrapTrigger3") {

            bool bottomInOrPastTile = (posy + height >= t->GetPosY()) && (posy < t->GetBottomY());
            bool horizontalOverlap = (posx < t->GetRightX()) && (posx + width > t->GetPosX());
            if (bottomInOrPastTile && horizontalOverlap) {
                if (t->GetType().find("TrapTrigger") == 0) {
                    TrapCollide(traps, t, now);
                }
                else {
                    posy = t->GetPosY() - height;
                    return true;
                }
            }
        }
    }
    return false;
}

void Player::SideCollide(std::vector<Trap*> traps, float now) {
    for (auto* t : traps) {
        if (t->GetType() == "GroundUntrapped" ||
            (t->GetType() == "GroundTrapped" && !t->isActive) ||
            t->GetType() == "TrapTrigger0" ||
            t->GetType() == "TrapTrigger1" ||
            t->GetType() == "TrapTrigger2" ||
            t->GetType() == "TrapTrigger3") {

            bool verticalOverlap = (posy + height > t->GetPosY() + 4.f) && (posy < t->GetBottomY());
            if (speed > 0) {
                if (verticalOverlap && posx + width >= t->GetPosX() && posx < t->GetPosX()) {
                    if (t->GetType().find("TrapTrigger") == 0) {
                        TrapCollide(traps, t, now);
                    }
                    else {
                        posx = t->GetPosX() - width - 1;
                    }
                }
            }
            else if (speed < 0) {
                if (verticalOverlap && posx <= t->GetRightX() && posx + width > t->GetRightX()) {
                    if (t->GetType().find("TrapTrigger") == 0) {
                        TrapCollide(traps, t, now);
                    }
                    else {
                        posx = t->GetRightX() + 1;
                    }
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

bool Player::UpCollide(std::vector<Trap*> traps, float now) {
    for (auto* t : traps) {
        if (t->GetType() == "GroundUntrapped" ||
            t->GetType() == "TrapTrigger0" ||
            t->GetType() == "TrapTrigger1" ||
            t->GetType() == "TrapTrigger2" ||
            t->GetType() == "TrapTrigger3") {

            if ((t->GetBottomY() >= posy && t->GetPosY() <= posy)) {
                if ((t->GetPosX() >= posx && t->GetPosX() <= posx + width)) {
                    if (t->GetType().find("TrapTrigger") == 0) {
                        TrapCollide(traps, t, now);
                    }
                    else {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Player::VoidCollide(std::vector<Trap*> traps) {
    if (posy >= 1080) {
        isAlive = false;
    }
}

void Player::PikeCollide(std::vector<Trap*> traps) {
    for (auto* t : traps) {
        if (t->GetType() == "Pike") {
            if (posx + width > t->GetPosX() && posx < t->GetRightX() &&
                posy + height > t->GetPosY() && posy < t->GetBottomY()) {
                isAlive = false;
                return;
            }
        }
    }
}

void Player::EggCollide(std::vector<Trap*> traps, Level* lvl) {
    for (auto* t : traps) {
        if (t->GetType() == "Egg") {
            if (posx + width >= t->GetPosX() && posx <= t->GetRightX() &&
                posy + height >= t->GetPosY() && posy <= t->GetBottomY()) {
                t->isActive = true;

                if (lvl && lvl->IsLast()) {
                    std::exit(0);
                }

                return;
            }
        }
    }   
}

void Player::TrapCollide(std::vector<Trap*> traps, Trap* t, float now) {
    if (t->isActive) return;

    int triggerCol = t->GetCharacterIdx();
    int targetCol = triggerCol + 1;

    bool pikeFound = false;

    for (auto* t1 : traps) {
        if (t1->GetCharacterIdx() != targetCol) continue;

        if (t->GetType() == "TrapTrigger0" || t->GetType() == "TrapTrigger3") {
            if (t1->GetType() == "Pike") {
                t1->posx += 64.f;
                t1->rect.setPosition(sf::Vector2f(t1->posx, t1->posy));
                t1->sprite->setPosition(sf::Vector2f(t1->posx - 50.f, t1->posy - 45.f));
                pikeFound = true;
            }
        }
    }

    if (!pikeFound) {
        for (auto* t1 : traps) {
            if (t1->GetCharacterIdx() != targetCol) continue;
            if (t1->GetType() != "GroundTrapped") continue;

            if (t->GetType() == "TrapTrigger0") {
                t1->isActive = !t1->isActive;
            }
            else if (t->GetType() == "TrapTrigger1") {
                t1->isActive = true;
            }
            else if (t->GetType() == "TrapTrigger2") {
                t1->isActive = false;
                t1->timedStart = now;
            }
        }
    }

    t->isActive = true;
}

void Player::SetSpawn(float x, float y) {
    spawnPosX = x;
    spawnPosY = y;
}

void Player::Respawn(Level* lvl) {
    posx = spawnPosX;
    posy = spawnPosY;
    speed = 0.f;
    moveLeft = false;
    moveRight = false;
    isJump = false;
    state = IDLE;
    isAlive = true;
    lvl->Reset();
    rect.setPosition(sf::Vector2f(posx, posy));
    if (sprite) {
        sprite->setPosition(sf::Vector2f(posx - 10, posy - 10));
    }
}