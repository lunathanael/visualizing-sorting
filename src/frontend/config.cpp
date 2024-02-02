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
        std::iota(config.data.begin(), config.data.end(), 1);
        std::shuffle(config.data.begin(), config.data.end(), std::mt19937 {});
        
        for (int i = 1; i < argc; ++i) {
            if (std::strcmp(argv[i], "--sorter") == 0) {
                if (i + 1 >= argc) {
                    std::cerr << "Expected sorter type\n";
                    std::exit(1);
                }
                if (std::strcmp(argv[i + 1], "quick") == 0) {
                    config.sorter = std::make_unique<backend::QuickSort<Iterator>>(config.data.begin(), config.data.end());
                }
                got_sorter = true;
            }
        }
    }
}
