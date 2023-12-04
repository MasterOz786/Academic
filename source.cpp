
#include <iostream>
#include "GG.cpp"
#include "LL.cpp"
using namespace std;

int main()
{
    GG<int> g(10, 10);

    g.Print();
    int sx, sy;
    int ex, ey;

    std::cout << "Enter the start index: ";
    std::cin >> sx >> sy;
    std::cout << "Enter the end index: ";
    std::cin >> ex >> ey;

    // cout << "The shortest path length is: "; g.dijkstra(s, e);
    g.simulateCarMovementFromSourceToDest(sx * 10 + sy, ex * 10 + ey);
    return 0;
}
