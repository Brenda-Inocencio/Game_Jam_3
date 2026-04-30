#include "Level.h"
#include "Trap.h"

Level::Level() : Level("", false) {
}

Level::Level(std::string path1, bool last) : nextLevel(""), prevLevel(""), path(path1), isLast(last) {
    Reset();
}

Level::~Level() {
    for (int i = 0; i < traps.size(); i++) {
        if (traps[i]) {
            delete traps[i];
            traps[i] = nullptr;
        }
    }
    traps.clear();
}

void Level::Render(sf::RenderWindow& window) {
    for (int i = 0; i < traps.size(); i++) {
        traps[i]->Render(window);
    }
}

void Level::Update(float now) {
    for (int i = 0; i < traps.size(); i++) {
        traps[i]->Update(now);
    }
}

void Level::Reset() {
    for (int i = 0; i < traps.size(); i++) {
        if (traps[i]) {
            delete traps[i];
            traps[i] = nullptr;
        }
    }
    traps.clear();

    std::ifstream level(path);
    if (!level) {
        std::cerr << "Can't find the level" << std::endl;
    }
    else {
        int lineNumber = -1;
        std::string line;
        while (std::getline(level, line)) {
            if (line == "Next Level") {
                std::getline(level, line);
                std::getline(level, line);
                continue;
            }
            lineNumber += 1;
            for (int i = 0; i < (int)line.size(); i++) {
                char c = line[i];
                if (c == 'X') {
                    traps.push_back(new Ground(sf::Vector2f(i * 128.f, lineNumber * 90.f), 0, false, i, lineNumber));
                }
                else if (c == '-') {
                    continue;
                }
                else if (c == 'E') {
                    traps.push_back(new Egg(sf::Vector2f(i * 128.f, lineNumber * 90.f), i, lineNumber));
                }
                else if (c == 'G') {
                    traps.push_back(new Ground(sf::Vector2f(i * 128.f, lineNumber * 90.f), 1, false, i, lineNumber));
                }
                else if (c == 'g') {
                    traps.push_back(new Ground(sf::Vector2f(i * 128.f, lineNumber * 90.f), 1, true, i, lineNumber));
                }
                else if (c == 'V') {
                    traps.push_back(new Ground(sf::Vector2f(i * 128.f, lineNumber * 90.f), 1, true, i, lineNumber));
                }
                else if (c == 'P') {
                    traps.push_back(new Pike(sf::Vector2f(i * 128.f, lineNumber * 90.f), 1, true, i, lineNumber));
                }
                else if (c == 'T') {
                    traps.push_back(new Tramplin(sf::Vector2f(i * 128.f, lineNumber * 90.f), 1, true, i, lineNumber));
                }
                else if (c == 'S') {
                    traps.push_back(new Spawn(sf::Vector2f(i * 128.f, lineNumber * 90.f), i, lineNumber));
                }
                else if (c == 'C') {
                    traps.push_back(new TrapTrigger(sf::Vector2f(i * 128.f, lineNumber * 90.f), 0, i, lineNumber));
                }
                else if (c == '1') {
                    traps.push_back(new TrapTrigger(sf::Vector2f(i * 128.f, lineNumber * 90.f), 1, i, lineNumber));
                }
                else if (c == 'M') {
                    traps.push_back(new TrapTrigger(sf::Vector2f(i * 128.f, lineNumber * 90.f), 2, i, lineNumber));
                }
                else if (c == 'D') {
                    traps.push_back(new TrapTrigger(sf::Vector2f(i * 128.f, lineNumber * 90.f), 3, i, lineNumber));
                }
            }
        }
    }
}

bool Level::HasActiveEgg() const {
    for (int i = 0; i < traps.size(); i++) {
        if (traps[i]->GetType() == "Egg" && traps[i]->isActive) {
            return true;
        }
    }
    return false;
}