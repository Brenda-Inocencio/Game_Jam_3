#include "Game.h"
#include "Player.h"
#include "Trap.h"
#include "Background.h"
#include "Level.h"

Game::Game() : currentLevel(0) {
    bg = new Background();
    levels.push_back(new Level("levels/level0.txt"));
	levels.push_back(new Level("levels/level1.txt"));
	levels.push_back(new Level("levels/level2.txt"));
	levels.push_back(new Level("levels/level3.txt"));
    player = new Player();
	InitSpawn();
}

Game::~Game() {
    for (int i = 0; i < levels.size(); i++) {
        if (levels[i]) {
            delete levels[i]; levels[i] = nullptr;
        }
    } 
    if (bg) {
        delete bg; bg = nullptr;
    }
    if (player) {
        delete player; player = nullptr;
    }
}

void Game::InitSpawn() {
    for (auto* t : levels[currentLevel]->traps) {
        if (t->GetType() == "Spawn") {
            player->SetSpawn(t->GetPosX(), t->GetPosY());
			player->Respawn();
            break;
        }
    }
}

void Game::Update(float dt, float now, std::vector<sf::Event> events) {
    player->Update(dt, now, events, levels[currentLevel]->traps);
    levels[currentLevel]->Update();

    for (auto* t : levels[currentLevel]->traps) {
        if (t->GetType() == "Egg" && t->isActive) {
			t->isActive = false;
			currentLevel++;
            if (currentLevel >= levels.size()) {
                currentLevel = 0;
            }
			InitSpawn();
			break;
        }
        
	}
}

void Game::Render(sf::RenderWindow& window) {
    bg->Render(window);
    levels[currentLevel]->Render(window);
    player->Render(window);
}