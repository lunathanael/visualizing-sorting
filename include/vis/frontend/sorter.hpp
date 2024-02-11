#ifndef VIS_FRONTEND_SORTER_HPP
#define VIS_FRONTEND_SORTER_HPP

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>

#include "vis/backend/sorter.hpp"

namespace vis::frontend {
    constexpr float screen_width = 800;
    constexpr float screen_height = 600;

    // Audio information
    // * bitrate is in samples per second
    // * duration is in milliseconds
    constexpr sf::Uint64 audio_bitrate = 44100;
    constexpr sf::Int16 sound_duration = 10;

    template <typename Iterator> class Sorter : public sf::Drawable {
    private:
        std::unique_ptr<vis::backend::Sorter<Iterator>> m_sorter;
        Iterator m_position;
        int m_largest;

        sf::SoundBuffer m_sound_buffer;
        sf::Sound m_sound;

    public:
        explicit Sorter(std::unique_ptr<vis::backend::Sorter<Iterator>> &&sorter)
            : m_sorter(std::move(sorter))
            , m_largest(*std::max_element(m_sorter->begin(), m_sorter->end())) {
            m_sound.setBuffer(m_sound_buffer);
        }

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

        sf::Int16 generate_wave(float time, float frequency, float volume) {
            return std::numeric_limits<sf::Int16>::max() * volume
                 * std::sin(2 * M_PI * frequency * time / audio_bitrate);
        }

        void play_sound() {
            std::vector<sf::Int16> samples(audio_bitrate * sound_duration / 1000);
            for (std::size_t i = 0; i < samples.size(); ++i) {
                float percentage = *m_position / static_cast<float>(m_largest);
                samples[i] = generate_wave(i, 1318.51 * percentage, 1.0);
            }

            m_sound_buffer.loadFromSamples(samples.data(), samples.size(), 1, audio_bitrate);
            m_sound.play();
        }

        void update() {
            if (!m_sorter->is_done()) {
                m_position = m_sorter->next();
                // Avoids high-pitched noises once the pointer gets to the end of the array
                if (m_position != m_sorter->end()) {
                    play_sound();
                }
            }
        }
    };
}

#endif
