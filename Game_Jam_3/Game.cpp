#include "Game.h"
#include "Player.h"
#include "Trap.h"
#include "Background.h"
#include "Level.h"

Game::Game() : currentLevel(0), shouldQuit(false) {
    bg = new Background();

    levels.push_back(new Level("levels/level0.txt", false));
    levels.push_back(new Level("levels/level1.txt", false));
    levels.push_back(new Level("levels/level2.txt", false));
    levels.push_back(new Level("levels/level3.txt", true));

    player = new Player();
    InitSpawn();
}

Game::~Game() {
    for (int i = 0; i < levels.size(); i++) {
        delete levels[i];
    }
    delete bg;
    delete player;
}

void Game::InitSpawn() {
    for (auto* t : levels[currentLevel]->GetTraps()) {
        if (t->GetType() == "Spawn") {
            player->SetSpawn(t->GetPosX(), t->GetPosY());
            player->Respawn(levels[currentLevel]);
            break;
        }
    }
}

void Game::Update(float dt, float now, std::vector<sf::Event> events) {
    player->Update(dt, now, events, levels[currentLevel]->GetTraps(), levels[currentLevel]);
    levels[currentLevel]->Update(now);

    if (levels[currentLevel]->HasActiveEgg()) {

        if (levels[currentLevel]->IsLast()) {
            shouldQuit = true;
            return;
        }

        currentLevel++;
        levels[currentLevel]->Reset();
        InitSpawn();
    }
}

void Game::Render(sf::RenderWindow& window) {
    bg->Render(window);
    levels[currentLevel]->Render(window);
    player->Render(window);
}
