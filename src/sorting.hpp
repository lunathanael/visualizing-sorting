#ifndef SORTING_HPP
#define SORTING_HPP

#include <random>
#include <algorithm>
#include <iterator>
#include<iostream>
namespace vis
{

    template <typename T>
    class QuickSort 
    {
    private:
        T itr1;
        T itr2;

        T pivot, i, j;
        bool pivoted;
        bool sorted;
        QuickSort<T>* l;
        QuickSort<T>* r;

    public:
        QuickSort(const T begin, const T end)
            : itr1(begin)
            , itr2(end)
            , pivoted(false)
            , sorted(false)
        {
            pivot = itr1, i = itr1, j = itr1;
        };

        T next();
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
T vis::QuickSort<T>::next()
{
    if(std::distance(itr1, itr2) < 1)
    {
        return itr2;
    }

    if(pivoted)
    {
        j = l->next();
        if(j == i)
        {
            j = r->next();
            if(j == itr2)
            {
                sorted = true;
            }
        }
        return j;
    }

    while (std::distance(j, itr2) > 1)
    {
        std::advance(j,1);
        if((*j) < (*pivot))
        {
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


template <typename T, typename RNG>
bool vis::BogoSort<T, RNG>::next()
{
    std::shuffle(itr1, itr2, rng);
    return std::is_sorted(itr1, itr2);
}

#endif