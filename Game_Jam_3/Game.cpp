#include "Game.h"
#include "Player.h"
#include "Background.h"
#include "Level.h"

Game::Game() : currentLevel(0) {
    bg = new Background();
    player = new Player();
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
    if (player) {
        delete player; player = nullptr;
    }
}

void Game::Update(float dt, float now, std::vector<sf::Event> events) {
    player->Update(dt, now, events);
    
}

void Game::Render(sf::RenderWindow& window) {
    //levels[currentLevel]->Render(window);
    bg->Render(window);
    player->Render(window);
}