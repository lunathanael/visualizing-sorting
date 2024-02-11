#ifndef VIS_BACKEND_BOGO_SORTER_HPP
#define VIS_BACKEND_BOGO_SORTER_HPP

#include <algorithm>
#include <random>

#include "vis/backend/sorter.hpp"

namespace vis::backend {
    template <typename T, typename RNG = std::mt19937> class BogoSort : public vis::backend::Sorter<T> {
    private:
        T itr1;
        T itr2;
        RNG rng;

    public:
        BogoSort(T begin, T end)
            : itr1(begin)
            , itr2(end) {}

        T begin() const override { return itr1; }

        T end() const override { return itr2; }

        T next() override {
            std::shuffle(itr1, itr2, rng);
            return itr2;
        }
    };
}

#endif
