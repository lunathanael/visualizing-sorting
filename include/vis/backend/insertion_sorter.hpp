#ifndef VIS_BACKEND_INSERTION_SORTER_HPP
#define VIS_BACKEND_INSERTION_SORTER_HPP

#include "vis/backend/sorter.hpp"

namespace vis::backend {
    template <typename Iterator> class InsertionSorter : public vis::backend::Sorter<Iterator> {
    };
}

#endif
