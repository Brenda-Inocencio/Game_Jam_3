#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Trap;

class Level {
public:
    Level();
    Level(std::string path1, bool last = false);
    ~Level();

    void Render(sf::RenderWindow& window);
    void Update(float now);
    void Reset();

    std::vector<Trap*>& GetTraps() { return traps; }

    bool HasActiveEgg() const;
    bool IsLast() const { return isLast; }

private:
    std::vector<Trap*> traps;
    std::string nextLevel;
    std::string prevLevel;
    std::string path;
    bool isLast;
};