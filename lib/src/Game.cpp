#include <SFML/Graphics.hpp>
#include <cmath>

//exaple code of a simple heart in sfml 
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "heart");

    sf::VertexArray heart(sf::TrianglesFan, 102);

    sf::Vector2f center(400, 300);
    float size = 10.0f; 

    heart[0].position = center;
    heart[0].color = sf::Color::Red;

    for (int i = 1; i <= 100; ++i) {
        float angle = 2 * M_PI * (i - 1) / 100; //??
        float x = size * 16 * std::pow(std::sin(angle), 3);
        float y = -size * (13 * std::cos(angle) - 5 * std::cos(2 * angle) - 2 * std::cos(3 * angle) - std::cos(4 * angle));
        heart[i].position = sf::Vector2f(center.x + x, center.y + y);
        heart[i].color = sf::Color::Red;
    }

    heart[101].position = heart[1].position;
    heart[101].color = sf::Color::Red;

    // principal window loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White); 

        // dreaw heart
        window.draw(heart);

        window.display();
    }

    return 0;
}
