#ifndef VIS_BACKEND_SORTER_HPP
#define VIS_BACKEND_SORTER_HPP

#include <algorithm>

namespace vis::backend {
    template <typename Iterator> class Sorter {
    public:
        virtual ~Sorter() = default;

        virtual Iterator begin() const = 0;
        virtual Iterator end() const = 0;
        virtual bool is_done() const { return std::is_sorted(begin(), end()); }
        virtual Iterator next() = 0;
    };
}

#endif
