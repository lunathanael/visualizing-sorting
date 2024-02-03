#ifndef VIS_BACKEND_BUBBLE_SORTER_HPP
#define VIS_BACKEND_BUBBLE_SORTER_HPP

#include <algorithm>

#include "vis/backend/sorter.hpp"

namespace vis::backend {
    template <typename T> class BubbleSort : public vis::backend::Sorter<T> {
    private:
        T itr1;
        T itr2;

        T curr;
        bool swapped;

    public:
        BubbleSort(const T begin, const T end)
            : itr1(begin)
            , itr2(end)
            , curr(begin) {}

        inline T begin() const override { return itr1; }

        inline T end() const override { return itr2; }

        T next() override {
            if (std::distance(itr1, itr2) < 1) {
                return itr2;
            }

            while (swapped || std::distance(curr, itr2) > 0) {
                if (std::distance(curr, itr2) == 1 && swapped) {
                    swapped = false;
                    curr = itr1;
                }
                std::advance(curr, 1);
                if ((*std::next(curr, -1)) > (*curr)) {
                    std::swap((*curr), (*std::prev(curr, 1)));
                    swapped = true;
                    return curr;
                }
            }

            return itr2;
        }
    };
}

#endif
