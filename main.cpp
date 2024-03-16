#include <iostream>

#include "ForwardList.h"

int main() {
    ForwardList<int> t1;
    ForwardList<int> t2(5);
    ForwardList<int> t3(10, 7);
    ForwardList<int> t4 {1, 2, 3};
    ForwardList<int> t5 (t4);
    ForwardList<int> t6(std::move(t3));
    ForwardList<int> t7{100};
    ForwardList<int> t8{50};
    t7 = t5;
    t8 = std::move(t6);

    for (auto it = t4.begin(); it != t4.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for (auto el : t4)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    auto tail = t4.split_when([] (const int& val){return val == 2; });
}
