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
#include "vis/frontend/config.hpp"
#include "vis/frontend/sorter.hpp"

using Container = std::array<int, 200>;
using Iterator = Container::iterator;

Container create_data() {
    Container data;
    std::iota(data.begin(), data.end(), 1);
    std::shuffle(data.begin(), data.end(), std::mt19937 {});
    return data;
}

int main(int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode(vis::frontend::screen_width, vis::frontend::screen_height),
                            "Sorting",
                            sf::Style::Close);

    window.setFramerateLimit(60);

    Container numbers = create_data();
    std::unique_ptr<vis::backend::Sorter<Iterator>> backend;

    vis::frontend::Config config = vis::frontend::parse_args(argc, argv);
    switch (config.sorter_kind) {
    case vis::frontend::SorterKind::BogoSort:
        backend = std::make_unique<vis::backend::BogoSort<Iterator, std::mt19937>>(numbers.begin(), numbers.end(), std::mt19937 {});
        break;
    case vis::frontend::SorterKind::QuickSort:
        backend = std::make_unique<vis::backend::QuickSort<Iterator>>(numbers.begin(), numbers.end());
        break;
    }

    vis::frontend::Sorter<Iterator> frontend {std::move(backend)};

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
