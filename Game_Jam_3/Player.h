#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

struct Texture;
struct Sprite;
class Trap;

class Player {
	float width;
	float height;
	float posx;
	float posy;

	int dir;
	bool moveLeft;
	bool moveRight;
	bool isJump;
	float jumpingTime;
	float speed;

	enum State {
		IDLE,
		LEFT,
		RIGHT,
		JUMPING,
		FALLING
	} state;

	State processEvent(std::vector<sf::Event>& events, float now);

public:
	sf::RectangleShape rect;
	bool isAlive;

	Player();
	~Player();

	void Render(sf::RenderWindow& window);
	void Update(float dt, float now, std::vector<sf::Event>& events, std::vector<Trap*>& traps);
	void Jump(float dt, float now, State& newState, std::vector<Trap*>& traps);
	void Fall(float dt, float now, State& newState, std::vector<Trap*>& traps);
	bool DownCollide(std::vector<Trap*>& traps);
	bool SideCollide(std::vector<Trap*>& traps);
	bool UpCollide(std::vector<Trap*>& traps);
	void VoidCollide(std::vector<Trap*>& traps);
	void ChangeLevel(std::vector<Trap*>& traps);
};