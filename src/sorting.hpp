#ifndef SORTING_HPP
#define SORTING_HPP

#include <random>
#include <algorithm>
#include <iterator>

namespace vis
{

    template <typename T>
    class QuickSort 
    {
    private:
        T itr1;
        T itr2;

    public:
        QuickSort(const T begin, const T end)
            : itr1(begin)
            , itr2(end)
        {};

        bool next();
    };

    template <typename T, typename RNG>
    class BogoSort 
    {
    private:
        T itr1;
        T itr2;
        RNG rng;

    public:
        BogoSort(const T begin, const T end, const RNG rng)
            : itr1(begin)
            , itr2(end)
            , rng(rng)
        {};

        bool next();
    };

};


template <typename T>
bool vis::QuickSort<T>::next()
{
    if(itr1 >= itr2)
    {
        return true;
    }

    T pivot = itr1, i = first, j = first;
    std::advance(j, 1);
    while (j < itr2)
    {
        if((*j) < (*pivot))
        {
            std::advance(i, 1);
            std::iter_swap(i, j);
            ++j;
            return false;
        }
        ++j;
    }
    if(i == pivot)
    {
        return false;
    }
    std::iter_swap(i, pivot);
}

void quick_sort(int* first, int* last, CMP cmp) {
	if (first < last) {
		int pivot = *first;
		int* i = first; int* j = first + 1;
		while (j < last) {
			if (cmp(*j, pivot)) {
				++i;
				int temp = *i;
				*i = *j;
				*j = temp;
			}
			++j;
		}
		int temp = *i;
		*i = *first;
		*first = temp;
		quick_sort(first, i, cmp);
		quick_sort(i + 1, last, cmp);
	}
	return;
}


template <typename T, typename RNG>
bool vis::BogoSort<T, RNG>::next()
{
    std::shuffle(itr1, itr2, rng);
    return std::is_sorted(itr1, itr2);
}

#endif