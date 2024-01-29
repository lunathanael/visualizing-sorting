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

    T pivot = itr1, i = itr1, j = itr1;
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
        QuickSort l{itr1, i};
        std::advance(i, 1);
        QuickSort r{i, itr2};
        return (l.next() || r.next());
    }
    std::iter_swap(i, pivot);
    return false;
}


template <typename T, typename RNG>
bool vis::BogoSort<T, RNG>::next()
{
    std::shuffle(itr1, itr2, rng);
    return std::is_sorted(itr1, itr2);
}

#endif