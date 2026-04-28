#pragma once
#include <SFML/Graphics.hpp>

class Trap {
protected:
	float posx;
	float posy;
	float width;
	float height;
	sf::Vector2f trapPos;
	std::string type;
	sf::RectangleShape rect;
	sf::RectangleShape rectTrap;
public:
	bool isActive;
public:
	Trap();
	virtual ~Trap();

	void Render(sf::RenderWindow& window);

	inline float GetPosX() { return posx; }
	inline float GetRightX() { return posx + width; }
	inline float GetPosY() { return posy; }
	inline float GetBottomY() { return posy + height; }
	inline std::string GetType() { return type; }
};

class Ground : public Trap {
public:
	Ground(sf::Vector2f(pos), sf::Vector2f(_trapPos), int _type, bool _isAcvtive);
	~Ground() {};
};

class Egg : public Trap {
public:
	Egg(sf::Vector2f(pos));
	~Egg() {};
};

class Pike : public Trap {
public:
	Pike(sf::Vector2f(pos), sf::Vector2f(_trapPos), int _type, bool _isAcvtive);
	~Pike() {};
};

class Tramplin : public Trap {
public:
	Tramplin(sf::Vector2f(pos), sf::Vector2f(_trapPos), int _type, bool _isAcvtive);
	~Tramplin() {};
};

class Spawn : public Trap {
public:
	Spawn(sf::Vector2f(pos));
	~Spawn() {};
};
