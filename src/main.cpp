#include <array>
#include <cstddef>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

#include <SFML/Graphics.hpp>

#include "vis/backend/quick_sorter.hpp"
#include "vis/backend/bogo_sorter.hpp"
#include "vis/frontend/sorter.hpp"

using Container = std::array<int, 6>;
using Iterator = Container::iterator;
using Sorter = vis::backend::BogoSort<Iterator, std::mt19937>;

Container create_data() {
    Container data;
    std::iota(data.begin(), data.end(), 1);
    std::shuffle(data.begin(), data.end(), std::mt19937 {});
    return data;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(vis::frontend::screen_width, vis::frontend::screen_height),
                            "Sorting",
                            sf::Style::Close);

    window.setFramerateLimit(60);

    Container numbers = create_data();
    std::unique_ptr<Sorter> backend = std::make_unique<Sorter>(numbers.begin(), numbers.end(), std::mt19937());
    vis::frontend::Sorter<Iterator> frontend(std::move(backend));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        frontend.update();

        window.clear();
        window.draw(frontend);
        window.display();
    }

    return 0;
}
