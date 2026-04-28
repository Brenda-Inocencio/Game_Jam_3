#include "Game.h"
#include "Player.h"
#include "Background.h"
#include "Level.h"

Game::Game() : currentLevel(0) {
    bg = new Background();
    levels.push_back(new Level("levels/level0.txt"));
    player = new Player();
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

void Game::Update(float dt, float now, std::vector<sf::Event> events) {
    player->Update(dt, now, events, levels[currentLevel]->traps);
    levels[currentLevel]->Update();
}

void Game::Render(sf::RenderWindow& window) {
    bg->Render(window);
    levels[currentLevel]->Render(window);
    player->Render(window);
}