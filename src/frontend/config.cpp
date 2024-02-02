#include "vis/frontend/config.hpp"
#include "vis/backend/quick_sorter.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <numeric>
#include <optional>
#include <random>

namespace vis::frontend {
    Config parse_args(int argc, char **argv) {
        std::optional<SorterKind> sorter_kind;

        for (int i = 1; i < argc; ++i) {
            if (std::strcmp(argv[i], "--sorter") == 0) {
                if (++i >= argc) {
                    std::cerr << "Expected sorter type\n";
                    std::exit(1);
                }

                if (std::strcmp(argv[i], "bogosort") == 0) {
                    sorter_kind = std::make_optional(SorterKind::BogoSort);
                } else if (std::strcmp(argv[i], "quicksort") == 0) {
                    sorter_kind = std::make_optional(SorterKind::QuickSort);
                }
            } else {
                std::cerr << "Unexpected argument\n";
                std::exit(1);
            }
        }

        // If no sorter was specified on the command line, use quicksort by
        // default.
        if (!sorter_kind.has_value()) {
            sorter_kind = std::make_optional(SorterKind::QuickSort);
        }

        return {sorter_kind.value()};
    }
}
