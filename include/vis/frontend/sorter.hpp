#ifndef VIS_FRONTEND_SORTER_HPP
#define VIS_FRONTEND_SORTER_HPP

#include <algorithm>
#include <memory>
#include <iterator>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "vis/backend/sorter.hpp"

namespace vis::frontend {
    constexpr float screen_width = 800;
    constexpr float screen_height = 600;

    template <typename Iterator> class Sorter : public sf::Drawable {
    private:
        std::unique_ptr<vis::backend::Sorter<Iterator>> m_sorter;

    public:
        explicit Sorter(std::unique_ptr<vis::backend::Sorter<Iterator>> &&sorter)
            : m_sorter(std::move(sorter)) {}

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            Iterator begin = m_sorter->begin();
            Iterator end = m_sorter->end();
            std::size_t length = std::distance(begin, end);

            for (Iterator it = begin; it != end; ++it) {
                float width = screen_width / length;
                float height = screen_height * *it / length;
                sf::RectangleShape shape(sf::Vector2f(width, height));
                shape.setPosition(std::distance(m_sorter->begin(), it) * width, screen_height - height);
                target.draw(shape);
            }
        }

        void update() {
            if (!m_sorter->is_done()) {
                m_sorter->next();
            }
        }
    };
}

#endif
