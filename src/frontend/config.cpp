#include "vis/frontend/config.hpp"
#include "vis/backend/quick_sorter.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>

namespace vis::frontend {
    Config parse_args(int argc, char **argv) {
        Config config;
        bool got_sorter = false;

        for (int i = 1; i < argc; ++i) {
            if (std::strcmp(argv[i], "--sorter") == 0) {
                if (++i >= argc) {
                    std::cerr << "Expected sorter type\n";
                    std::exit(1);
                }

                if (got_sorter) {
                    continue;
                }

                if (std::strcmp(argv[i], "bogosort") == 0) {
                    config.sorter_kind = SorterKind::BogoSort;
                } else if (std::strcmp(argv[i], "quicksort") == 0) {
                    config.sorter_kind = SorterKind::QuickSort;
                }

                got_sorter = true;
            } else {
                std::cerr << "Unexpected argument\n";
                std::exit(1);
            }
        }

        if (!got_sorter) {
            std::cerr << "Expected a sorter to be specified\n";
            std::exit(1);
        }

        return config;
    }
}
