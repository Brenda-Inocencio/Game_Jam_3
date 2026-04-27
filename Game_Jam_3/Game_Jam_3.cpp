#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>



int main() {
    // Récupère la résolution native de l'écran
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    // Création de la fenêtre en plein écran
    sf::RenderWindow window(desktopMode, "Plein écran SFML", sf::Style::Default);

    // Limite le framerate pour éviter une utilisation CPU/GPU excessive
    window.setFramerateLimit(60);

    //Setting* setting = new Setting();

    sf::Clock clock;
    float now = 0.0f;
    float gameTime = 0.0f;
    float dt = 0.0f;
    std::vector<sf::Event> events;

    // Boucle principale
    while (window.isOpen()) {
        dt = clock.restart().asSeconds();
        now += dt;
        // Process events
        events.clear();
        while (const auto event = window.pollEvent()) {

            // Close window: exit
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            events.push_back(event);
        }

        // Efface l'écran avec une couleur
        window.clear(sf::Color::Black);


        // Draw the sprite


        // Update the window
        window.display();
    }

    events.clear();


    return 0;
}