
#include <iostream>
#include "GG.cpp"
#include "LL.cpp"
using namespace std;

int main()
{
    GG<int> g(10, 10);
    g.PrintAdjacencyList();
    g.Print();
    int s, e;
    cout << "S & E: ";
    cin >> s >> e;
    cout << "The shortest path length is: " << g.dijkstra(s, e);

    return 0;
}
