#ifndef VIS_BACKEND_BOGO_SORTER_HPP
#define VIS_BACKEND_BOGO_SORTER_HPP

#include <algorithm>

#include "vis/backend/sorter.hpp"

namespace vis::backend {
    template <typename T, typename RNG> class BogoSort : public vis::backend::Sorter<T> {
    private:
        T itr1;
        T itr2;
        RNG rng;

    public:
        BogoSort(const T begin, const T end, const RNG rng)
            : itr1(begin)
            , itr2(end)
            , rng(rng) {}

        T begin() const override { return itr1; }

        T end() const override { return itr2; }

        bool is_done() const override { return std::is_sorted(itr1, itr2); }

        void next() override { std::shuffle(itr1, itr2); }
    };
}

#endif
