#include <array>
#include <cstddef>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

#include <SFML/Graphics.hpp>

#include "sorting.hpp"
#include "vis/frontend/sorter.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(vis::frontend::screen_width, vis::frontend::screen_height),
                            "Sorting",
                            sf::Style::Close);

    window.setFramerateLimit(60);

    constexpr std::size_t n = 200;

    std::vector<int> numbers(n);
    std::mt19937 random;

    std::iota(numbers.begin(), numbers.end(), 1);
    std::shuffle(numbers.begin(), numbers.end(), random);

    auto bs = std::make_unique<vis::QuickSort<std::vector<int>::iterator>>(numbers.begin(), numbers.end());
    vis::frontend::Sorter<std::vector<int>::iterator> sorter(std::move(bs));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sorter.update();

        window.clear();
        window.draw(sorter);
        window.display();
    }

    return 0;
}
