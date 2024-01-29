#ifndef SORTING_HPP
#define SORTING_HPP

#include <random>
#include <algorithm>

namespace vis
{

    template <typename T>
    class QuickSort 
    {
    private:
        T itr1;
        T itr2;

    private:
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

    private:
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
    return false;   
}

template <typename T, typename RNG>
bool vis::BogoSort<T, RNG>::next()
{
    std::shuffle(itr1, itr2, rng);
    return std::is_sorted(itr1, itr2);
}

#endif