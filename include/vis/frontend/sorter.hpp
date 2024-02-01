#ifndef VIS_FRONTEND_SORTER_HPP
#define VIS_FRONTEND_SORTER_HPP

#include <algorithm>
#include <iterator>
#include <memory>

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
        Iterator m_position;

    public:
        explicit Sorter(std::unique_ptr<vis::backend::Sorter<Iterator>> &&sorter)
            : m_sorter(std::move(sorter)) {}

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            Iterator begin = m_sorter->begin();
            Iterator end = m_sorter->end();
            std::size_t length = std::distance(begin, end); 
            float width = screen_width / length;

            for (Iterator it = begin; it != end; ++it) {
                float height = screen_height * *it / length;
                sf::RectangleShape shape(sf::Vector2f(width, height));
                shape.setPosition(std::distance(m_sorter->begin(), it) * width, screen_height - height);
                target.draw(shape);
            }

            if (!m_sorter->is_done()) {
                draw_marker(width, target);
            }
        }

        void draw_marker(float width, sf::RenderTarget &target) const {
            // This needs to be done to ensure that the marker can still be seen
            // even when the array contains very many elements.
            float marker_width = std::max(width, 1.0f);

            sf::RectangleShape marker(sf::Vector2f(marker_width, screen_height));
            marker.setFillColor(sf::Color(0xff, 0x00, 0x00));
            marker.setPosition(std::distance(m_sorter->begin(), m_position) * width, 0);
            target.draw(marker);
        }

        void update() {
            if (!m_sorter->is_done()) {
                m_position = m_sorter->next();
            }
        }
    };
}

#endif
