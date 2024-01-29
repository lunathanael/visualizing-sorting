#include <array>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <iterator>
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
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Sorting");
    window.setFramerateLimit(60);

    Sorter sorter;
    do
    {
        window.clear();
        window.draw(sorter);
        window.display();
    }
    while(1);
    std::cout << "Sorted.\n";
    return 0;
}