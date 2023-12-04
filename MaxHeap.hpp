
class Heap {
private:
    int *arr;
    int capacity;
    int size;

public:
    Heap(int capacity);
    int parent(int i);
    int left(int i);
    int right(int i);
    int getMax();
    void insert(int k);
    void heapify(int i);
    int extractMax();
    void decreaseKey(int i, int new_val);
    void deleteKey(int i);
    void print();
};