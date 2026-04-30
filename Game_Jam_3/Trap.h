#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Trap {
public:
    Trap();
    virtual ~Trap();

    virtual void Render(sf::RenderWindow& window);
    virtual void Update(float now);

    float GetPosX() const { return posx; }
    float GetPosY() const { return posy; }
    float GetRightX() const { return posx + width; }
    float GetBottomY() const { return posy + height; }

    std::string GetType() const { return type; }

    int GetCharacterIdx() const { return posCharacter; }
    int GetLineIdx() const { return lineCharacter; }

    float posx;
    float posy;
    float width;
    float height;
    bool isActive;
    float timedStart;

    int posCharacter;
    int lineCharacter;

    std::string type;

    sf::RectangleShape rect;
    sf::Texture* tex;
    sf::Sprite* sprite;
};

class Ground : public Trap {
public:
    Ground(sf::Vector2f pos, int _type, bool _isActive, int i, int ln);
    virtual void Update(float now);
};

class Egg : public Trap {
public:
    Egg(sf::Vector2f pos, int i, int ln);
    virtual void Update(float now);
};

class Pike : public Trap {
public:
    Pike(sf::Vector2f pos, int _type, bool _isActive, int i, int ln);
    virtual void Update(float now);
};

class Tramplin : public Trap {
public:
    Tramplin(sf::Vector2f pos, int _type, bool _isActive, int i, int ln);
    virtual void Update(float now);
};

class Spawn : public Trap {
public:
    Spawn(sf::Vector2f pos, int i, int ln);
    virtual void Update(float now);
};

class TrapTrigger : public Trap {
public:
    TrapTrigger(sf::Vector2f pos, int trap, int i, int ln);
    virtual void Update(float now);
};