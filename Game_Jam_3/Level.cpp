#include "Level.h"
#include "Trap.h"
#include <fstream>
#include <iostream>

Level::Level() : Level("") {
}

Level::Level(std::string path1) : nextLevel(""), prevLevel("") {
	std::ifstream level(path1);
	if (!level) {
		std::cerr << "Can't find the level" << std::endl;
	}
	else {
		int lineNumber = -1;
		std::string line;
		std::string character;
		while (std::getline(level, line)) {
			lineNumber += 1;
			for (int i = 0; i < line.size(); i++) {
				character = line[i];
				if (line == "Next Level") {
					lineNumber -= 2;
					if (std::getline(level, line)) {
						nextLevel = line;
					}
				}
				else if (line == "Previous Level") {
					lineNumber -= 2;
					if (std::getline(level, line)) {
						prevLevel = line;
					}
				}
				else if (character == "X") {
					traps.push_back(new Ground(sf::Vector2f(i * 128, lineNumber * 90), 0, false));
				}
				else if (character == "-") {
					continue; //nothing
				}
				else if (character == "E") {
					traps.push_back(new Egg(sf::Vector2f(i * 128, lineNumber * 90)));
				}
				else if (character == "G") {
					traps.push_back(new Ground(sf::Vector2f(i * 128, lineNumber * 90), 1, false)); 
				}
				else if (character == "g") {
					traps.push_back(new Ground(sf::Vector2f(i * 128, lineNumber * 90), 1, true)); 
				}
				else if (character == "V") {
					traps.push_back(new Ground(sf::Vector2f(i * 128, lineNumber * 90),  1, true));
				}
				else if (character == "P") {
					traps.push_back(new Pike(sf::Vector2f(i * 128, lineNumber * 90), 1, true));
				}
				else if (character == "T") {
					traps.push_back(new Tramplin(sf::Vector2f(i * 128, lineNumber * 90), 1, true));
				}
				else if (character == "S") {
					traps.push_back(new Spawn(sf::Vector2f(i * 128, lineNumber * 90)));
				}
				else if (character == "C") {
					traps.push_back(new TrapTrigger(sf::Vector2f(i * 128, lineNumber * 90), 0));
				}
				else if (character == "1") {
					traps.push_back(new TrapTrigger(sf::Vector2f(i * 128, lineNumber * 90), 1));
				}
			}
		}
	}
}

Level::~Level() {
	for (int i = 0; i < traps.size(); i++) {
		if (traps[i]) {
			delete traps[i]; traps[i] = nullptr;
		}
	}
	traps.clear();
}

void Level::Render(sf::RenderWindow& window) {
	for (int i = 0; i < traps.size(); i++) {
		traps[i]->Render(window);
	}
}

void Level::Update(int currentLvl, int& newLvl, float dt, float now) {
	for (int i = 0; i < traps.size(); i++) {
		if (traps[i]->GetType() == "Egg") { //Next Level
			/*if (traps[i]->isNextLevel) {
				newLvl = currentLvl + 1;
				traps[i]->isNextLevel = false;
			}*/
		}
	}
}