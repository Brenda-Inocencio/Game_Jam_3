#pragma once
#include <SFML/Graphics.hpp>
struct Texture;
struct Sprite;

class Trap {
protected:
	float posx;
	float posy;
	int posCharacter;
	int lineCharacter;
	float width;
	float height;
	std::string type;
	sf::RectangleShape rect;

	sf::Texture* tex;
	sf::Sprite* sprite;
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
	inline int GetCharacterIdx() { return posCharacter; }
	inline int GetCharacterLine() { return lineCharacter; }
	inline std::string GetType() { return type; }
};

class Ground : public Trap {
public:
	Ground(sf::Vector2f(pos), int _type, bool _isAcvtive, int i, int ln);
	~Ground() {};
};

class Egg : public Trap {
public:
	Egg(sf::Vector2f(pos), int i, int ln);
	~Egg() {};
};

class Pike : public Trap {
public:
	Pike(sf::Vector2f(pos), int _type, bool _isAcvtive, int i, int ln);
	~Pike() {};
};

class Tramplin : public Trap {
public:
	Tramplin(sf::Vector2f(pos), int _type, bool _isAcvtive, int i, int ln);
	~Tramplin() {};
};

class Spawn : public Trap {
public:
	Spawn(sf::Vector2f(pos), int i, int ln);
	~Spawn() {};
};

class TrapTrigger : public Trap {
public:
	TrapTrigger(sf::Vector2f(pos), int trap, int i, int ln);
	~TrapTrigger() {};
};
