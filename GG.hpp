
#pragma once
#include "LL.hpp"
#include "Player.hpp"

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
    
    void SimulateAutoCarMovement(int source, int dest);
    void SimulatePlayerCarMovement(int source, int dest);
    void StartMenu();
    void ShowLeaderboards();

private:
    int vertices;
    Grid grid;
    LL<Vertex> adj_list;
    Player player;
    PriorityQueue<char> powerUps;
    PriorityQueue<char> obstacles;
    PriorityQueue<char> coins;

    void CreateMatrix(int rows, int cols);
    void FreeMatrix();
    int* Djisktra(int source, int dest);
    void GenerateRandomGraph();
    void MakeConnections();
    void PrintVertexConnections(int v);

    void initializePowerUps();
    void initializeObstacels();
    void initializeCoins();
    bool validateNextPos(int x, int y, int curX, int curY);
    bool validateStartPos(int sourceX, int sourceY, int destX, int destY);
    void ManageScore(char object);
    void SortLeaderboards();
    void UpdateRecords();

    void storeCurrentProgress();
    void restoreCurrentProgress();
};
