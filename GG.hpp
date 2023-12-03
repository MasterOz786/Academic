
#pragma once
#include "LL.hpp"

struct Grid
{
    int rows, cols;
    char **indexes;
};

template <typename T>
class GG
{
public:
    GG();
    GG(int r, int c);
    void PrintAdjacencyList();
    void Print();
    int dijkstra(int source, int dest);
    void simulateCarMovementFromSourceToDest();

private:
    int vertices;
    Grid grid;
    LL<Vertex> adj_list;

    void CreateMatrix(int rows, int cols);
    void GenerateRandomGraph();
    void MakeConnections();
    void PrintVertexConnections(int v);
};
