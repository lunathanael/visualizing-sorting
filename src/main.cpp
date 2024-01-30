#include <array>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <iterator>
#include <random>
#include <vector>

#include <SFML/Graphics.hpp>

#include "sorting.hpp"

constexpr int screen_width = 1920;
constexpr int screen_height = 1080;

class Sorter : public sf::Drawable {
private:
    std::vector<int> m_data;
    std::mt19937 gen;
    vis::BogoSort<std::vector<int>::iterator, std::mt19937> *q;

public:
    Sorter()
    {
        m_data.resize(1000);
        std::iota(m_data.begin(), m_data.end(), 0);
        std::shuffle(m_data.begin(), m_data.end(), gen);
        q = new vis::BogoSort{m_data.begin(), m_data.end(), gen};
    }

    inline bool next() {return q->next() == m_data.end(); };

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        // origin = bottom left
        auto itr = q->next();
        for (auto it = m_data.begin(); it != m_data.end(); std::advance(it, 1)) {
            int width = screen_width / m_data.size();
            int height = (screen_height / m_data.size()) * (*it);
            if(it == itr)
            {
                height = screen_height;
            }

            sf::RectangleShape shape(sf::Vector2f(width, height));
            shape.setPosition(std::distance(m_data.begin(), it) * width, screen_height - height);
            target.draw(shape);
        }
        return;
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

        window.clear();
        window.draw(sorter);
        window.display();
    }

    return 0;
}
