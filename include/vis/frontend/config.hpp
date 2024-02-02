#ifndef VIS_FRONTEND_CONFIG_HPP
#define VIS_FRONTEND_CONFIG_HPP

#include <array>
#include <cstddef>

#include "vis/frontend/sorter.hpp"

namespace vis::frontend {
    enum class SorterKind {
        BogoSort,
        QuickSort,
    };

    struct Config {
        SorterKind sorter_kind;
        std::size_t num_elements;
    };

    Config parse_args(int argc, char **argv);
}

#endif
