#include <array>
#include <cstddef>
#include <iostream>
#include <numeric>

#include <SFML/Graphics.hpp>
#include <random>

constexpr int screen_width = 800;
constexpr int screen_height = 600;

class Sorter : public sf::Drawable {
private:
    std::array<int, 32> m_data;

public:
    Sorter() {
        std::iota(m_data.begin(), m_data.end(), 1);
        std::mt19937 gen;
        std::shuffle(m_data.begin(), m_data.end(), gen);
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        // origin = bottom left
        for (std::size_t i = 0; i < m_data.size(); ++i) {
            int width = screen_width / m_data.size();
            int height = screen_height * m_data[i] / m_data.size();

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

    constexpr int n = 8;
    std::vector<int> v(n);
    
    std::mt19937 rng;

    std::iota(v.begin(), v.end(), 0);
    std::shuffle(v.begin(), v.end(), rng);

    vis::BogoSort bs{v.begin(), v.end(), rng};

    bool ended = false;
    do
    {
        ended = bs.next();
        for(auto & a : v)
        {
            std::cout << a << ' ';
        }
        window.clear();
        window.draw(sorter);
        window.display();
    }
    while(!ended);
    return 0;
}
