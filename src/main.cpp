#include <array>
#include <cstddef>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <SFML/Window/Event.hpp>
#include <vector>

#include <SFML/Graphics.hpp>

#include "vis/backend/bogo_sorter.hpp"
#include "vis/backend/bubble_sorter.hpp"
#include "vis/backend/quick_sorter.hpp"
#include "vis/frontend/config.hpp"
#include "vis/frontend/sorter.hpp"

using namespace vis::backend;

using Container = std::vector<int>;
using Iterator = Container::iterator;

static Container create_data(std::size_t num_elements) {
    // Brace initialization can't be used because the std::initializer_list
    // constructor takes priority.
    Container data(num_elements);
    std::iota(data.begin(), data.end(), 1);
    std::shuffle(data.begin(), data.end(), std::mt19937{});
    return data;
}

static std::unique_ptr<Sorter<Iterator>> create_sorter(vis::frontend::SorterKind kind, Container &container) {
    using vis::frontend::SorterKind;
    switch (kind) {
    case SorterKind::BogoSort: return std::make_unique<BogoSort<Iterator>>(container.begin(), container.end());
    case SorterKind::BubbleSort: return std::make_unique<BubbleSort<Iterator>>(container.begin(), container.end());
    case SorterKind::QuickSort: return std::make_unique<QuickSort<Iterator>>(container.begin(), container.end());
    }
}

int main(int argc, char **argv) {
    // This needs to be set up before the window or else the command line args
    // won't be parsed until after the window was already created.
    vis::frontend::Config config = vis::frontend::parse_args(argc, argv);
    Container numbers = create_data(config.num_elements);
    vis::frontend::Sorter<Iterator> frontend{create_sorter(config.sorter_kind, numbers)};

    sf::RenderWindow window(sf::VideoMode(vis::frontend::screen_width, vis::frontend::screen_height),
                            "Sorting",
                            sf::Style::Close);

    window.setFramerateLimit(120);

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
