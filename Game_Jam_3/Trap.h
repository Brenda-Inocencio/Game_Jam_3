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
	Ground(sf::Vector2f(pos), sf::Vector2f(size), int type);
	~Ground() {};
};
