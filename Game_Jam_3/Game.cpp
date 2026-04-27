#include "Game.h"
#include "Player.h"
#include "Background.h"
#include "Level.h"

Game::Game() : currentLevel(0) {
    bg = new Background();
}

Game::~Game() {
    for (int i = 0; i < levels.size(); i++) {
        if (levels[i]) {
            delete levels[i]; levels[i] = nullptr;
        }
    }
    for (int i = 0; i < bgs.size(); i++) {
        if (bgs[i]) {
            delete bgs[i]; bgs[i] = nullptr;
        }
    }
    if (bg) {
        delete bg; bg = nullptr;
    }
}

void Game::Update(float dt, float now, Player* player, std::vector<sf::Event> events) {
    player->Update(dt, now, events);
    
}

void Game::Render(sf::RenderWindow& window, Player* player) {
    //levels[currentLevel]->Render(window);
    bg->Render(window);
    player->Render(window);
}