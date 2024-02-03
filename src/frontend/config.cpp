#include "vis/frontend/config.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <string>

#include "vis/backend/bubble_sorter.hpp"
#include "vis/backend/quick_sorter.hpp"

namespace vis::frontend {
    static void print_usage_and_exit(const char *program) {
        std::cerr << "Usage: " << program << " [--elements n] [--sorter bogosort|quicksort]\n";
        std::exit(1);
    }

    Config parse_args(int argc, char **argv) {
        std::optional<SorterKind> sorter_kind;
        std::optional<std::size_t> num_elements;

        for (int i = 1; i < argc; ++i) {
            if (std::strcmp(argv[i], "--elements") == 0) {
                if (++i >= argc) {
                    print_usage_and_exit(argv[0]);
                }

                try {
                    num_elements = std::make_optional(std::stol(argv[i]));
                } catch (const std::exception &e) {
                    print_usage_and_exit(argv[0]);
                }
            } else if (std::strcmp(argv[i], "--sorter") == 0) {
                if (++i >= argc) {
                    print_usage_and_exit(argv[0]);
                }

                if (std::strcmp(argv[i], "bogosort") == 0) {
                    sorter_kind = std::make_optional(SorterKind::BogoSort);
                } else if (std::strcmp(argv[i], "quicksort") == 0) {
                    sorter_kind = std::make_optional(SorterKind::QuickSort);
                } else if (std::strcmp(argv[i], "bubblesort") == 0) {
                    sorter_kind = std::make_optional(SorterKind::BubbleSort);
                }
            } else {
                print_usage_and_exit(argv[0]);
            }
        }

        return {sorter_kind.value_or(SorterKind::QuickSort), num_elements.value_or(200)};
    }
}
