#ifndef VIS_FRONTEND_CONFIG_HPP
#define VIS_FRONTEND_CONFIG_HPP

#include <array>

#include "vis/frontend/sorter.hpp"

namespace vis::frontend {
    enum class SorterKind {
        QuickSort,
    };

    struct Config {
        SorterKind sorter_kind;
    };

    std::vector<std::string> create_args(int argc, char **argv);
    Config parse_args(const std::vector<std::string> &args);
}

#endif
