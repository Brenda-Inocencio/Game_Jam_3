#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

struct Texture;
struct Sprite;

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
	void Update(float dt, float now, std::vector<sf::Event>& events);
	void Jump(float dt, float now, State& newState);
	void Fall(float dt, float now, State& newState);
	/*bool DownCollide(std::vector<Block*>& blocks);
	bool SideCollide(std::vector<Block*>& blocks);
	bool UpCollide(std::vector<Block*>& blocks);
	void VoidCollide(std::vector<Block*>& blocks);*/
	//void ChangeLevel(std::vector<Block*>& blocks);
};