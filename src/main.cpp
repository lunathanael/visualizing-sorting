#include <iostream>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>
#include <src/sorting.hpp>


int main() {

    constexpr int n = 8;
    std::vector<int> v(n);
    
    std::mt19937 rng;

    std::iota(v.begin(), v.end(), 0);
    std::shuffle(v.begin(), v.end(), rng);

    vis::BogoSort bs{v.begin(), v.end(), rng};

    bool ended = false;
    do
    {
        ended = bs.next();
        for(auto & a : v)
        {
            std::cout << a << ' ';
        }
        std::cout << '\n';
    }
    while(!ended);
    return 0;
}
