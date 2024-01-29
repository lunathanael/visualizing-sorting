#include <array>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

#include <SFML/Graphics.hpp>
#include <src/sorting.hpp>
#include <random>

constexpr int screen_width = 800;
constexpr int screen_height = 600;

class Sorter : public sf::Drawable {
private:
    std::vector<int> m_data;
    std::mt19937 gen;
    vis::QuickSort<std::vector<int>::iterator> *q;

public:
    Sorter()
    {
        m_data.resize(500);
        std::iota(m_data.begin(), m_data.end(), 0);
        std::shuffle(m_data.begin(), m_data.end(), gen);
        q = new vis::QuickSort{m_data.begin(), m_data.end()};
    }

    inline bool next() {return q->next(); };

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
    bool progress = false;
    do
    {
        progress = sorter.next();
        window.clear();
        window.draw(sorter);
        window.display();
    }
    while(!progress);
    return 0;
}