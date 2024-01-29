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
        QuickSort<T>* l;
        QuickSort<T>* r;

    public:
        QuickSort(const T begin, const T end)
            : itr1(begin)
            , itr2(end)
            , pivoted(false)
        {
            pivot = itr1, i = itr1, j = std::next(itr1, 1);
        };

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
    if(std::distance(itr1, itr2) < 1)
    {
        return true;
    }

    if(pivoted)
    {
        return (l->next() && r->next());
    }

    while (std::distance(j, itr2) > 0)
    {
        if((*j) < (*pivot))
        {
            std::advance(i, 1);
            std::swap(*i, *j);
            std::advance(j,1);
            return false;
        }
        std::advance(j, 1);
    }
    std::iter_swap(i, pivot);
    l = new QuickSort{itr1, i};
    r = new QuickSort{std::next(i, 1), itr2};
    pivoted = true;

    return false;
}


template <typename T, typename RNG>
bool vis::BogoSort<T, RNG>::next()
{
    std::shuffle(itr1, itr2, rng);
    return std::is_sorted(itr1, itr2);
}

#endif