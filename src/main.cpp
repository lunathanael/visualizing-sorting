#include <array>
#include <cstddef>
#include <iostream>
#include <numeric>

#include <SFML/Graphics.hpp>
#include <src/sorting.hpp>
#include <random>

constexpr float screen_width = 800;
constexpr float screen_height = 600;

class Sorter : public sf::Drawable {
private:
    std::array<int, 500> m_data;
    std::mt19937 gen;
    vis::QuickSort<decltype(m_data)::iterator> m_sorter;

public:
    Sorter() : m_sorter(m_data.begin(), m_data.end())
    {
        std::iota(m_data.begin(), m_data.end(), 1);
        std::shuffle(m_data.begin(), m_data.end(), gen);
    }

    inline bool next() { return m_sorter.next(); };

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        // origin = bottom left
        for (std::size_t i = 0; i < m_data.size(); ++i) {
            float width = screen_width / m_data.size();
            float height = (screen_height / m_data.size()) * m_data[i];

            sf::RectangleShape shape(sf::Vector2f(width, height));
            shape.setPosition(i * width, screen_height - height);
            target.draw(shape);
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Sorting", sf::Style::Close);
    window.setFramerateLimit(60);

    Sorter sorter;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sorter.next();

        window.clear();
        window.draw(sorter);
        window.display();
    }

    return 0;
}
