#pragma once

// contains methods for Linked List operations
template <typename T>
struct Node
{
    T data;
    Node *next, *prev;

    Node()
    {
        this->next = nullptr;
        this->prev = nullptr;
    }

    Node(T data)
    {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

template <typename T>
class LL
{
public:
    Node<T> *head, *tail;

    LL();
    // ~LL();

    void insertAtFront(T data);
    void insertAtEnd(T data);
    void insertAfter(Node<T> *reqNode, T data);
    void insertUnique(T data);
    void deleteFront();
    void deleteTail();
    void deleteNode(T data);
    Node<T> *searchNode(T data);
    void swap(Node<T> *n1, Node<T> *n2);

    // Graph specific methods
    void UpdatePosition(int pos, int data);

    // sort algo
    void bubbleSort();
    void insertionSort();

    // printing
    void printList() const;
};

class Edge
{
public:
    int source, dest;
    int weight;

    Edge()
    {
    }

    Edge(int s, int d, int w)
    {
        this->source = s;
        this->dest = d;
        this->weight = w;
    }

    bool operator==(Edge &edge)
    {
        return this->source == edge.source && this->dest == edge.dest;
    }

    friend std::ostream &operator<<(std::ostream &out, Edge &edge);
};

class Vertex
{
    char type;
    int id, distanceFromSource;
    LL<Edge> neighbours;

public:
    Vertex(int id = -1, int type = '-', int distanceFromSource = 0)
    {
        this->id = id;
        this->type = type;
        this->distanceFromSource = distanceFromSource;
    }

    void AddEdge(Edge edge)
    {
        this->neighbours.insertUnique(edge);
    }

    void PrintNeighbours()
    {
        this->neighbours.printList();
    }

    LL<Edge> getNeighbours()
    {
        return neighbours;
    }

    int GetID()
    {
        return this->id;
    }

    char GetType()
    {
        return this->type;
    }

    bool operator==(Vertex &vertex)
    {
        return this->id == vertex.id;
    }

    bool operator!=(Vertex &vertex)
    {
        return this->id != vertex.id;
    }

    bool operator>(Vertex &vertex)
    {
        return this->distanceFromSource > vertex.distanceFromSource;
    }

    friend std::ostream &operator<<(std::ostream &out, Vertex &vertex);
};
