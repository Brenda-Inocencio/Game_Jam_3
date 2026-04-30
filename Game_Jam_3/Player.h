#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Trap;
class Level;

class Player {
public:
    enum State {
        IDLE,
        JUMPING,
        FALLING
    };

    Player();
    ~Player();

    void Render(sf::RenderWindow& window);
    void Update(float dt, float now, std::vector<sf::Event> events, std::vector<Trap*>& traps, Level* lvl);

    void SetSpawn(float x, float y);
    void Respawn(Level* lvl);

private:
    float width;
    float height;
    float posx;
    float posy;
    float speed;
    float jumpingTime;
    int dir;
    State state;
    bool isJump;
    bool isAlive;
    bool moveLeft;
    bool moveRight;
    int deathCount;
    bool isGravityFlipped;
    float gravityFlipTime;

    float spawnPosX;
    float spawnPosY;

    sf::RectangleShape rect;
    sf::Texture* tex;
    sf::Sprite* sprite;

    State processEvent(std::vector<sf::Event>& events, float now);

    void Jump(float dt, float now, State& newState, std::vector<Trap*>& traps);
    void Fall(float dt, float now, State& newState, std::vector<Trap*>& traps);

    bool DownCollide(std::vector<Trap*> traps, float now);
    void SideCollide(std::vector<Trap*> traps, float now);
    bool UpCollide(std::vector<Trap*> traps, float now);

    void VoidCollide(std::vector<Trap*> traps);
    void PikeCollide(std::vector<Trap*> traps);
    void EggCollide(std::vector<Trap*> traps, Level* lvl);
    void TrapCollide(std::vector<Trap*> traps, Trap* t, float now);
};