
#include <iostream>
#include "GG.cpp"
#include "LL.cpp"
using namespace std;


int main()
{
    GG<int> g(10, 10);

    g.Print();
    // cout << "The shortest path length is: "; g.dijkstra(s, e);
    g.StartMenu();
    return 0;
}
