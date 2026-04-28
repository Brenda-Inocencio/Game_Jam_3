#pragma once
#include <SFML/Graphics.hpp>

class Trap {
protected:
	float posx;
	float posy;
	float width;
	float height;
	std::string type;
	sf::RectangleShape rect;
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
	Ground(sf::Vector2f(pos), int _type, bool _isAcvtive);
	~Ground() {};
};

class Egg : public Trap {
public:
	Egg(sf::Vector2f(pos));
	~Egg() {};
};

class Pike : public Trap {
public:
	Pike(sf::Vector2f(pos), int _type, bool _isAcvtive);
	~Pike() {};
};

class Tramplin : public Trap {
public:
	Tramplin(sf::Vector2f(pos), int _type, bool _isAcvtive);
	~Tramplin() {};
};

class Spawn : public Trap {
public:
	Spawn(sf::Vector2f(pos));
	~Spawn() {};
};

class TrapTrigger : public Trap {
public:
	TrapTrigger(sf::Vector2f(pos), int trap);
	~TrapTrigger() {};
};
