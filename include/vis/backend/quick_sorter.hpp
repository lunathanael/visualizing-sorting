#ifndef VIS_BACKEND_QUICK_SORTER_HPP
#define VIS_BACKEND_QUICK_SORTER_HPP

#include "vis/backend/sorter.hpp"
#include <algorithm>

namespace vis::backend {
    template <typename T> class QuickSort : public vis::backend::Sorter<T> {
    private:
        T itr1;
        T itr2;

        T pivot, i, j;
        bool pivoted;
        bool sorted;
        QuickSort<T> *l = nullptr;
        QuickSort<T> *r = nullptr;

    public:
        QuickSort(const T begin, const T end)
            : itr1(begin)
            , itr2(end)
            , pivoted(false)
            , sorted(false) {
            pivot = itr1, i = itr1, j = itr1;
        };

        ~QuickSort() override {
            delete l;
            delete r;
        }

        T begin() const override { return itr1; }

        T end() const override { return itr2; }

        bool is_done() const override { return sorted; }

        T next() override {
            if (std::distance(itr1, itr2) < 1) {
                return itr2;
            }

            if (pivoted) {
                j = l->next();
                if (j == i) {
                    j = r->next();
                    if (j == itr2) {
                        sorted = true;
                    }
                }
                return j;
            }

            while (std::distance(j, itr2) > 1) {
                std::advance(j, 1);
                if ((*j) < (*pivot)) {
                    std::advance(i, 1);
                    std::swap(*i, *j);
                    return j;
                }
            }

            std::iter_swap(i, pivot);
            l = new QuickSort{itr1, i};
            r = new QuickSort{std::next(i, 1), itr2};
            pivoted = true;

            return i;
        }
    };
}

#endif
