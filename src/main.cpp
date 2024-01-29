#include <array>
#include <cstddef>
#include <iostream>
#include <numeric>

#include <SFML/Graphics.hpp>
#include <src/sorting.hpp>
#include <random>

constexpr int screen_width = 800;
constexpr int screen_height = 600;

class Sorter : public sf::Drawable {
private:
    std::array<int, 5> m_data;
    std::mt19937 gen;

public:
    Sorter() {
        std::iota(m_data.begin(), m_data.end(), 0);
    }

    void shuffle() {std::shuffle(m_data.begin(), m_data.end(), gen); };
    bool is_sorted() const {return std::is_sorted(m_data.begin(), m_data.end()); };

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        // origin = bottom left
        for (std::size_t i = 0; i < m_data.size(); ++i) {
            int width = screen_width / m_data.size();
            int height = (screen_height / m_data.size()) * m_data[i];

            sf::RectangleShape shape(sf::Vector2f(width, height));
            shape.setPosition(i * width, screen_height - height);
            target.draw(shape);
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Sorting");
    window.setFramerateLimit(60);

    Sorter sorter;
    do
    {
        sorter.shuffle();
        window.clear();
        window.draw(sorter);
        window.display();
    }
    while(!sorter.is_sorted());
    return 0;
}