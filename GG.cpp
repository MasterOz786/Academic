
#include <iostream>
#include <algorithm>
#include <ctime>
#include "GG.hpp"
#include "Queue.hpp"
#include <Windows.h>
// Graph class implementation3
template <typename T>
GG<T>::GG()
{
    this->vertices = 0;
}

template <typename T>
GG<T>::GG(int r, int c)
{
    this->grid.rows = r;
    this->grid.cols = c;
    this->vertices = r * c;
    CreateMatrix(r, c);
}

template <typename T>
void GG<T>::PrintVertexConnections(int v)
{
    Node<Vertex> *temp = this->adj_list.head;
    for (int i = 0; i < v; i++)
    {
        temp = temp->next;
    }
    temp->data.PrintNeighbours();
}

template <typename T>
void GG<T>::PrintAdjacencyList()
{
    Node<Vertex> *temp = this->adj_list.head;
    for (int i = 0; i < this->grid.rows * this->grid.cols; i++)
    {
        std::cout << temp->data.GetID() << " -> ";
        temp->data.PrintNeighbours();
        temp = temp->next;
    }
}

template <typename T>
void GG<T>::CreateMatrix(int rows, int cols)
{
    // store the adjacency list in a pair matrix
    grid.indexes = new char *[rows];

    // assigning memory
    for (int i = 0; i < rows; i++)
    {
        grid.indexes[i] = new char[cols];
    }

    GenerateRandomGraph();
    MakeConnections();
}

template <typename T>
void GG<T>::GenerateRandomGraph()
{
    srand(time(0));
    // filling the adjacency list
    for (int i = 0; i < this->grid.rows; i++)
        for (int j = 0; j < this->grid.cols; j++)
        {
            // generate obstacles
            if (rand() % 7 == 0)
            {
                int weight = ' ';
                this->grid.indexes[i][j] = weight;
                this->adj_list.insertUnique(Vertex((i * this->grid.cols) + j, weight));
            }
            else
            {
                int weight = '+';
                this->grid.indexes[i][j] = weight;
                this->adj_list.insertUnique(Vertex((i * this->grid.cols) + j, weight));
            }
        }
}

template <typename T>
void GG<T>::Print()
{
    // Setting color control variable
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    std::cout << '\n';
    for (int i = 0; i < grid.rows; i++)
    {
        for (int j = 0; j < grid.cols; j++)
        {
            if (adj_list.searchNode((i * grid.cols) + j)->data.getNeighbours().head)
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            std::cout << grid.indexes[i][j];
            // printing horizontal edges
            if (j < grid.cols - 1)
            {
                Node<Vertex> *temp = adj_list.searchNode((i * grid.cols) + j);
                Node<Edge> *temp2 = temp->data.getNeighbours().head;
                bool inserted = false;
                while (temp2 != nullptr)
                {
                    if (temp2->data.dest == (i * grid.cols) + j + 1)
                    {
                        // Changing text color
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        std::cout << "----";
                        inserted = true;
                        break;
                    }
                    temp2 = temp2->next;
                }
                if (!inserted)
                {
                    std::cout << "    ";
                }
            }
        }
        std::cout << '\n';

        // printing vertical edges
        if (i < grid.rows - 1)
        {
            for (int j = 0; j < grid.cols; j++)
            {
                Node<Vertex> *temp = adj_list.searchNode((i * grid.cols) + j);
                Node<Edge> *temp2 = temp->data.getNeighbours().head;
                bool inserted = false;
                while (temp2 != nullptr)
                {
                    if (temp2->data.dest == ((i + 1) * grid.cols) + j)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        std::cout << "|    ";
                        inserted = true;
                        break;
                    }
                    temp2 = temp2->next;
                }
                if (!inserted)
                {
                    std::cout << "     ";
                }
            }
        }
        std::cout << '\n';
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

template <typename T>
void GG<T>::MakeConnections()
{
    // making connections
    Node<Vertex> *temp = this->adj_list.head;
    for (int i = 0; temp != nullptr; i++)
    {
        int source = temp->data.GetID();
        int weight = '+';

        if (temp->data.GetType() != ' ')
        {
            // make connections on the right
            if (source % grid.cols < grid.cols - 1 && source + 1 < this->vertices)
            {
                Node<Vertex> *vNode = adj_list.searchNode(source + 1);
                if (vNode->data.GetType() != ' ')
                {
                    weight = vNode->data.GetType();
                    temp->data.AddEdge(Edge(source, source + 1, weight));
                }
            }

            // make connections on the left
            if (source % grid.cols > 0 && source - 1 >= 0)
            {
                Node<Vertex> *vNode = adj_list.searchNode(source - 1);
                if (vNode->data.GetType() != ' ')
                {
                    weight = vNode->data.GetType();
                    temp->data.AddEdge(Edge(source, source - 1, weight));
                }
            }

            // make connections on the top
            if (source >= grid.cols)
            {
                Node<Vertex> *vNode = adj_list.searchNode(source - grid.cols);
                if (vNode->data.GetType() != ' ')
                {
                    weight = vNode->data.GetType();
                    temp->data.AddEdge(Edge(source, source - grid.cols, weight));
                }
            }

            // make connections on the bottom
            if (source < this->vertices - grid.cols && source + grid.cols < this->vertices)
            {
                Node<Vertex> *vNode = adj_list.searchNode(source + grid.cols);
                if (vNode->data.GetType() != ' ')
                {
                    weight = vNode->data.GetType();
                    temp->data.AddEdge(Edge(source, source + grid.cols, weight));
                }
            }
        }
        temp = temp->next;
    }
}

// Dijkstra Algorithim for finding shortest path from source to dest
template <typename T>
int* GG<T>::dijkstra(int source, int dest)
{
    // Setting color control variable
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // initializing the distance array
    int *dist = new int[this->vertices];
    for (int i = 0; i < this->vertices; i++)
    {
        dist[i] = 100000;
    }

    // initializing the parent array
    int *parent = new int[this->vertices];
    for (int i = 0; i < this->vertices; i++)
    {
        parent[i] = -1;
    }

    // initializing the visited array
    bool *visited = new bool[this->vertices];
    for (int i = 0; i < this->vertices; i++)
    {
        visited[i] = false;
    }

    // initializing the priority queue
    PriorityQueue<Vertex> pq;

    // setting the source distance to 0
    dist[source] = 0;
    pq.enqueue(adj_list.searchNode(source)->data);

    while (!pq.isEmpty())
    {
        Vertex u = pq.showFront();
        pq.dequeue();
        visited[u.GetID()] = true;

        Node<Edge> *temp = u.getNeighbours().head;
        while (temp != nullptr)
        {
            if (!visited[temp->data.dest])
            {
                int alt = dist[u.GetID()] + temp->data.weight;
                if (alt < dist[temp->data.dest])
                {
                    dist[temp->data.dest] = alt;
                    parent[temp->data.dest] = u.GetID();
                    pq.enqueue(adj_list.searchNode(temp->data.dest)->data);
                }
            }
            temp = temp->next;
        }
    }

    // printing the path
    int cur = dest;
    while (cur != -1)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::cout << cur;
        // remove the ending/trailing arrow
        if (cur != source) std::cout << " <- ";
        cur = parent[cur];
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    // store the shortest path
    return parent;
}

// Function for showing car traveling from one point to the other on the grid and car is represented  by C and Destination is represented by D
template <typename T>
void GG<T>::simulateCarMovementFromSourceToDest(int source, int dest)
{
    std::cout << this->vertices << '\n';
    int* parent = new int[this->vertices];
    parent = dijkstra(source, dest);

    // reversing the path array
    int *path = new int[this->vertices];
    int i = 0;
    int cur = dest;
    while (cur != -1)
    {
        path[i] = cur;
        cur = parent[cur];
        i++;
    }
    std::reverse(path, path + i);

    // resize the path array and delete the parent
    path = (int *)realloc(path, i * sizeof(int));
    delete[] parent;

    // setting the start and end points
    int x = source / this->grid.cols;
    int y = source % this->grid.cols;
    this->grid.indexes[x][y] = 'C';
    x = dest / this->grid.cols;
    y = dest % this->grid.cols;
    this->grid.indexes[x][y] = 'D';

    x = -1, y = -1;
    cur = 0;
    while (i >= 0) {
        if (x != -1 && y != -1) this->grid.indexes[x][y] = '+';
        int index = path[cur];
        x = index / this->grid.cols;
        y = index % this->grid.cols;
        this->grid.indexes[x][y] = 'C';
        Sleep(1000);
        system("cls");
        Print();
        i--;
        cur++;
    }
    Print();
}
