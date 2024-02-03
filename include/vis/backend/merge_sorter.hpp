#ifndef VIS_BACKEND_MERGE_SORTER_HPP
#define VIS_BACKEND_MERGE_SORTER_HPP

#include "vis/backend/sorter.hpp"
#include <algorithm>
#include <stack>
#include <utility>

namespace vis::backend {
    template <typename T> class QuickSort : public vis::backend::Sorter<T> {
    private:
        T itr1;
        T itr2;
        bool sorted;

        T l, r, i, j;
        std::stack<std::pair<T, T>> st;

        void merge_intervals(const T l1, const T r1, const T l2, const T r2)
        {
            
        }

    public:
        QuickSort(const T begin, const T end)
            : itr1(begin)
            , itr2(end)
            , sorted(false)
            
            , l(begin)
            , r(end)
            , i(begin)
            , j(begin)
        {};

        ~QuickSort() override {};

        T begin() const override { return itr1; }

        T end() const override { return itr2; }

        bool is_done() const override { return sorted; }

        T next() override {
            if (sorted)
            {
                return itr2;
            }

            if (j == r)
            {
                std::iter_swap(i, l);   
                if (std::distance(std::next(i, 1), r) > 1)
                {
                    st.push(std::make_pair(std::next(i, 1), r));
                }
                if (std::distance(l, i) > 1)
                {
                    st.push(std::make_pair(l, i));
                }
                
                if (st.empty())
                {
                    sorted = true;
                    return itr2;
                }
                l = st.top().first;
                r = st.top().second;
                i = l;
                j = l;
                st.pop();   
            }

            if ((*j) < (*l))
            {
                std::advance(i, 1);
                std::iter_swap(i, j);
            }
            std::advance(j, 1);

            return j;
        }
    };
}

#endif
