
#include "Player.hpp"

class Heap {
private:
    PlayerData* arr;
    int capacity;
    int size;

public:
    Heap(int capacity);
    bool isEmpty();
    int parent(int i);
    int left(int i);
    int right(int i);
    PlayerData getMax();
    void insert(PlayerData k);
    void heapify(int i);
    PlayerData extractMax();
    void decreaseKey(int i, PlayerData new_val);
    void deleteKey(int i);
    void print();
};