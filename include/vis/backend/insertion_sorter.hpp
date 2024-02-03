#ifndef VIS_BACKEND_INSERTION_SORTER_HPP
#define VIS_BACKEND_INSERTION_SORTER_HPP

#include "vis/backend/sorter.hpp"
#include <iterator>

namespace vis::backend {
    template <typename Iter> class InsertionSorter : public vis::backend::Sorter<Iter> {
    private:
        Iter m_begin, m_end, m_position, m_insert_position;

    public:
        InsertionSorter(Iter begin, Iter end)
            : m_begin {begin}
            , m_end {end}
            , m_position {std::next(begin)}
            , m_insert_position {begin}
        {}

        Iter begin() const override {
            return m_begin;
        }

        Iter end() const override { 
            return m_end;
        }

        Iter next() override {
            if (std::distance(m_position, m_end) <= 0) {
                return m_position;
            }
            if (*m_insert_position <= *std::next(m_insert_position)) {
                std::advance(m_position, 1);
                m_insert_position = std::prev(m_position);
            }
            std::swap(*m_insert_position, *std::next(m_insert_position));
            std::advance(m_insert_position, -1);
            return m_insert_position;
        }
    };
}

#endif
