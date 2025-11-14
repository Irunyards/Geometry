#include <SFML/Graphics.hpp>
#include "geometry.h"

#include <vector>


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 400), "Geometry App");

    std::vector<std::shared_ptr<NGeometry::TBaseFigure>> figures;

    // TTriangle with TFixedVector
    NGeometry::TFixedVector v_tri1_base(NGeometry::TPoint(50, 300), NGeometry::TPoint(250, 300));
    NGeometry::TFixedVector v_tri2_base(NGeometry::TPoint(50, 300), NGeometry::TPoint(150, 100));
    auto triangle = std::make_shared<NGeometry::TTriangle>(v_tri1_base, v_tri2_base);
    figures.push_back(triangle);

    // TCircle with TFixedVector
    NGeometry::TFixedVector v_circ_base(NGeometry::TPoint(400, 200), NGeometry::TPoint(400, 100));
    auto circle = std::make_shared<NGeometry::TCircle>(v_circ_base);
    figures.push_back(circle);

    // TSquare with TFixedVector
    NGeometry::TFixedVector v_sq1_base(NGeometry::TPoint(550, 300), NGeometry::TPoint(750, 300));
    NGeometry::TFixedVector v_sq2_base(NGeometry::TPoint(550, 300), NGeometry::TPoint(550, 100));
    auto square = std::make_shared<NGeometry::TSquare>(v_sq1_base, v_sq2_base);
    figures.push_back(square);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        for (const auto& figure : figures) {
            figure->draw(window);
        }

        window.display();
    }

    return 0;
}
