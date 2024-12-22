#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "C�rculo con Aceleraci�n Variable");

    // Crear el c�rculo
    sf::CircleShape circle(50.0f);  // Radio de 50 p�xeles
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(window.getSize().x / 2, window.getSize().y / 2);  // Posicionar el c�rculo en el centro

    // Inicializar variables de movimiento
    sf::Vector2f velocidad(0.0f, 0.0f);
    sf::Vector2f aceleracion(0.0f, 0.0f);
    const float aceleracionMagnitud = 400.0f;  // Magnitud de la aceleraci�n en p�xeles por segundo cuadrado
    const float friccion = 300.0f;  // Magnitud de la fricci�n en p�xeles por segundo cuadrado

    // Reloj para gestionar el tiempo
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Reiniciar la aceleraci�n
        aceleracion = sf::Vector2f(0.0f, 0.0f);

        // Manejar la entrada del teclado para la aceleraci�n
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            aceleracion.x += aceleracionMagnitud;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            aceleracion.x -= aceleracionMagnitud;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            aceleracion.y -= aceleracionMagnitud;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            aceleracion.y += aceleracionMagnitud;
        }

        // Calcular el tiempo transcurrido
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        // Actualizar la velocidad con la aceleraci�n
        velocidad += aceleracion * dt;

        // Aplicar fricci�n para desacelerar
        if (velocidad.x > 0) {
            velocidad.x = std::max(0.0f, velocidad.x - friccion * dt);
        } else if (velocidad.x < 0) {
            velocidad.x = std::min(0.0f, velocidad.x + friccion * dt);
        }

        if (velocidad.y > 0) {
            velocidad.y = std::max(0.0f, velocidad.y - friccion * dt);
        } else if (velocidad.y < 0) {
            velocidad.y = std::min(0.0f, velocidad.y + friccion * dt);
        }

        // Actualizar la posici�n del c�rculo
        circle.move(velocidad * dt);

        // Mantener el c�rculo dentro de la ventana
        sf::Vector2f posicion = circle.getPosition();
        if (posicion.x < 0) posicion.x = 0;
        if (posicion.x + circle.getRadius() * 2 > window.getSize().x) posicion.x = window.getSize().x - circle.getRadius() * 2;
        if (posicion.y < 0) posicion.y = 0;
        if (posicion.y + circle.getRadius() * 2 > window.getSize().y) posicion.y = window.getSize().y - circle.getRadius() * 2;
        circle.setPosition(posicion);

        // Dibujar el c�rculo
        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}
