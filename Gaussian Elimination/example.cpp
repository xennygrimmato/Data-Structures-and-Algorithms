#include <iostream>
#include <vector>

#include "gauss.cpp"

using namespace std;

int example()
{
    std::vector<std::vector<double>> a3 = {{12, -12, 4},
                                           {2, 3, 44},
                                           {12, 3, -1}};

    std::vector<double> b3 = {-1, 2, 3};
    std::vector<double> result = Gauss(Array2D(a3), b3);

    for (auto &element : result)
        cout << element << endl;

    getchar();
    return 0;
}
