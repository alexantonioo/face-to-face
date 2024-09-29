// lib/include/Ring.hpp

#define RING_HPP

#include <SFML/Graphics.hpp>

class Ring {
public:
    // Constructor del ring
    Ring(float width, float height);

    // Método para dibujar el ring en la ventana
    void draw(sf::RenderWindow& window);

    // Método para obtener los límites del ring (usado para colisiones)
    sf::FloatRect getBounds() const;

private:
    // Componentes gráficos del ring
    sf::RectangleShape ringShape;
    sf::RectangleShape topBorder, bottomBorder, leftBorder, rightBorder;
};

