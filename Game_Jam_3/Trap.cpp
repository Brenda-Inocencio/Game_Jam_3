#include "Trap.h"

Trap::Trap() : posx(0.f), posy(0.f), width(128.f), height(90.f), isActive(false), timedStart(-1.f),
posCharacter(0), lineCharacter(0), type("Trap") {
    rect = sf::RectangleShape(sf::Vector2f(width, height));
    rect.setPosition(sf::Vector2f(posx, posy));
    rect.setFillColor(sf::Color::Transparent);
   /* rect.setOutlineColor(sf::Color::Blue);
    rect.setOutlineThickness(2.f);*/

    tex = new sf::Texture("assets/pick.png");
    sprite = new sf::Sprite(*tex);
    sprite->setScale(sf::Vector2f(0.65f, 0.65f));
    sprite->setPosition(sf::Vector2f(-1000.f, -1000.f));
}

Trap::~Trap() {
    if (tex) {
        delete tex;
        tex = nullptr;
    }
    if (sprite) {
        delete sprite;
        sprite = nullptr;
    }
}

void Trap::Render(sf::RenderWindow& window) {
    window.draw(rect);
    window.draw(*sprite);
}

void Trap::Update(float now) {
    if (type == "GroundTrapped") {
        if (!isActive) {
            rect.setFillColor(sf::Color::Black);
        }
        if (isActive) {
            rect.setFillColor(sf::Color::Transparent);
        }
    }
}

Ground::Ground(sf::Vector2f pos, int _type, bool _isActive, int i, int ln) {
    posCharacter = i;
    lineCharacter = ln;
    isActive = _isActive;
    timedStart = -1.f;
    posx = pos.x;
    posy = pos.y;
    width = 128.f;
    height = 90.f;
    rect.setSize(sf::Vector2f(width, height));
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
    if (isActive) {
        rect.setFillColor(sf::Color::Transparent);
    }
    rect.setPosition(pos);
}

void Ground::Update(float now) {
    if (type == "GroundTrapped") {
        if (timedStart >= 0.f) {
            if (now - timedStart >= 2.f) {
                isActive = true;
                timedStart = -1.f;
            }
        }
        if (!isActive) {
            rect.setFillColor(sf::Color::Black);
        }
        else {
            rect.setFillColor(sf::Color::Transparent);
        }
    }
}

Egg::Egg(sf::Vector2f pos, int i, int ln) {
    posCharacter = i;
    lineCharacter = ln;
    posx = pos.x;
    posy = pos.y;
    width = 72.f;
    height = 162.f;
    isActive = false;
    timedStart = -1.f;
    type = "Egg";
    rect.setSize(sf::Vector2f(width - 22.f, height));
    rect.setFillColor(sf::Color::Transparent);
    rect.setPosition(pos);
    tex = new sf::Texture("assets/egg.png");
    sprite = new sf::Sprite(*tex);
    sprite->setScale(sf::Vector2f(0.70f, 0.70f));
    sprite->setPosition(sf::Vector2f(posx, posy));
}

void Egg::Update(float now) {
}

Pike::Pike(sf::Vector2f pos, int _type, bool _isActive, int i, int ln) {
    posCharacter = i;
    lineCharacter = ln;
    isActive = _isActive;
    timedStart = -1.f;
    posx = pos.x + 50.f;
    posy = pos.y + 45.f;
    width = 50.f;
    height = 45.f;
    type = "Pike";
    rect.setSize(sf::Vector2f(width, height));
    rect.setPosition(sf::Vector2f(posx, posy));
    sprite->setScale(sf::Vector2f(0.65f, 0.65f));
    sprite->setPosition(sf::Vector2f(posx, posy));
}

void Pike::Update(float now) {
}

Tramplin::Tramplin(sf::Vector2f pos, int _type, bool _isActive, int i, int ln) {
    posCharacter = i;
    lineCharacter = ln;
    isActive = _isActive;
    timedStart = -1.f;
    posx = pos.x;
    posy = pos.y;
    width = 128.f;
    height = 90.f;
    type = "Tramplin";
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(pos);
}

void Tramplin::Update(float now) {
}

Spawn::Spawn(sf::Vector2f pos, int i, int ln) {
    posCharacter = i;
    lineCharacter = ln;
    isActive = true;
    timedStart = -1.f;
    posx = pos.x;
    posy = pos.y;
    width = 128.f;
    height = 90.f;
    type = "Spawn";
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(sf::Color::Transparent);
    rect.setPosition(pos);
}

void Spawn::Update(float now) {
}

TrapTrigger::TrapTrigger(sf::Vector2f pos, int trap, int i, int ln) {
    posCharacter = i;
    lineCharacter = ln;
    isActive = false;
    timedStart = -1.f;
    posx = pos.x;
    posy = pos.y;
    width = 128.f;
    height = 90.f;
    type = "TrapTrigger";
    rect.setSize(sf::Vector2f(width, height));
    //rect.setOutlineColor(sf::Color::Magenta);
    //rect.setOutlineThickness(2.f);
    rect.setPosition(pos);
    switch (trap) {
    case 0:
        type += "0";
        break;
    case 1:
        type += "1";
        break;
    case 2:
        type += "2";
        break;
    case 3:
        type += "3";
        break;
    default:
        break;
    }
}

void TrapTrigger::Update(float now) {
}